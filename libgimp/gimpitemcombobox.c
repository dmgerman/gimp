begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpdrawablecombobox.c  * Copyright (C) 2004 Sven Neumann<sven@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawablecombobox.h"
end_include

begin_include
include|#
directive|include
file|"gimppixbuf.h"
end_include

begin_define
DECL|macro|MENU_THUMBNAIL_SIZE
define|#
directive|define
name|MENU_THUMBNAIL_SIZE
value|24
end_define

begin_function_decl
specifier|static
name|gint
name|gimp_drawable_combo_box_model_add
parameter_list|(
name|GtkListStore
modifier|*
name|store
parameter_list|,
name|gint32
name|image
parameter_list|,
name|gint
name|num_drawables
parameter_list|,
name|gint32
modifier|*
name|drawables
parameter_list|,
name|GimpDrawableConstraintFunc
name|constraint
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/**  * gimp_drawable_combo_box_new:  * @constraint: a #GimpDrawableConstraintFunc or %NULL  * @data:       a pointer that is passed to @constraint  *  * Creates a new #GimpIntComboBox filled with all currently opened  * drawables. If a @constraint function is specified, it is called for  * each drawable and only if the function returns %TRUE, the drawable  * is added to the combobox.  *  * You should use gimp_int_combo_box_connect() to initialize and connect  * the combo.  Use gimp_int_combo_box_set_active() to get the active  * drawable ID and gimp_int_combo_box_get_active() to retrieve the ID  * of the selected drawable.  *  * Return value: a new #GimpIntComboBox.  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_drawable_combo_box_new (GimpDrawableConstraintFunc constraint,gpointer data)
name|gimp_drawable_combo_box_new
parameter_list|(
name|GimpDrawableConstraintFunc
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
name|gint
name|i
decl_stmt|;
name|combo_box
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_INT_COMBO_BOX
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
name|gint32
modifier|*
name|drawables
decl_stmt|;
name|gint
name|num_drawables
decl_stmt|;
name|drawables
operator|=
name|gimp_image_get_layers
argument_list|(
name|images
index|[
name|i
index|]
argument_list|,
operator|&
name|num_drawables
argument_list|)
expr_stmt|;
name|gimp_drawable_combo_box_model_add
argument_list|(
name|GTK_LIST_STORE
argument_list|(
name|model
argument_list|)
argument_list|,
name|images
index|[
name|i
index|]
argument_list|,
name|num_drawables
argument_list|,
name|drawables
argument_list|,
name|constraint
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|drawables
argument_list|)
expr_stmt|;
name|drawables
operator|=
name|gimp_image_get_channels
argument_list|(
name|images
index|[
name|i
index|]
argument_list|,
operator|&
name|num_drawables
argument_list|)
expr_stmt|;
name|gimp_drawable_combo_box_model_add
argument_list|(
name|GTK_LIST_STORE
argument_list|(
name|model
argument_list|)
argument_list|,
name|images
index|[
name|i
index|]
argument_list|,
name|num_drawables
argument_list|,
name|drawables
argument_list|,
name|constraint
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|drawables
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
return|return
name|combo_box
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_channel_combo_box_new:  * @constraint: a #GimpDrawableConstraintFunc or %NULL  * @data:       a pointer that is passed to @constraint  *  * Creates a new #GimpIntComboBox filled with all currently opened  * channels. See gimp_drawable_combo_box() for more info.  *  * Return value: a new #GimpIntComboBox.  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_channel_combo_box_new (GimpDrawableConstraintFunc constraint,gpointer data)
name|gimp_channel_combo_box_new
parameter_list|(
name|GimpDrawableConstraintFunc
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
name|gint
name|i
decl_stmt|;
name|combo_box
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_INT_COMBO_BOX
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
name|gint32
modifier|*
name|drawables
decl_stmt|;
name|gint
name|num_drawables
decl_stmt|;
name|drawables
operator|=
name|gimp_image_get_channels
argument_list|(
name|images
index|[
name|i
index|]
argument_list|,
operator|&
name|num_drawables
argument_list|)
expr_stmt|;
name|gimp_drawable_combo_box_model_add
argument_list|(
name|GTK_LIST_STORE
argument_list|(
name|model
argument_list|)
argument_list|,
name|images
index|[
name|i
index|]
argument_list|,
name|num_drawables
argument_list|,
name|drawables
argument_list|,
name|constraint
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|drawables
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
return|return
name|combo_box
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_layer_combo_box_new:  * @constraint: a #GimpDrawableConstraintFunc or %NULL  * @data:       a pointer that is passed to @constraint  *  * Creates a new #GimpIntComboBox filled with all currently opened  * layers. See gimp_drawable_combo_box() for more info.  *  * Return value: a new #GimpIntComboBox.  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_layer_combo_box_new (GimpDrawableConstraintFunc constraint,gpointer data)
name|gimp_layer_combo_box_new
parameter_list|(
name|GimpDrawableConstraintFunc
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
name|gint
name|i
decl_stmt|;
name|combo_box
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_INT_COMBO_BOX
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
name|gint32
modifier|*
name|drawables
decl_stmt|;
name|gint
name|num_drawables
decl_stmt|;
name|drawables
operator|=
name|gimp_image_get_layers
argument_list|(
name|images
index|[
name|i
index|]
argument_list|,
operator|&
name|num_drawables
argument_list|)
expr_stmt|;
name|gimp_drawable_combo_box_model_add
argument_list|(
name|GTK_LIST_STORE
argument_list|(
name|model
argument_list|)
argument_list|,
name|images
index|[
name|i
index|]
argument_list|,
name|num_drawables
argument_list|,
name|drawables
argument_list|,
name|constraint
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|drawables
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
return|return
name|combo_box
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|gimp_drawable_combo_box_model_add (GtkListStore * store,gint32 image,gint num_drawables,gint32 * drawables,GimpDrawableConstraintFunc constraint,gpointer data)
name|gimp_drawable_combo_box_model_add
parameter_list|(
name|GtkListStore
modifier|*
name|store
parameter_list|,
name|gint32
name|image
parameter_list|,
name|gint
name|num_drawables
parameter_list|,
name|gint32
modifier|*
name|drawables
parameter_list|,
name|GimpDrawableConstraintFunc
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
name|added
init|=
literal|0
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
name|num_drawables
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
name|image
argument_list|,
name|drawables
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
name|image
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|drawable_name
init|=
name|gimp_drawable_get_name
argument_list|(
name|drawables
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
literal|"%s-%d/%s-%d"
argument_list|,
name|image_name
argument_list|,
name|image
argument_list|,
name|drawable_name
argument_list|,
name|drawables
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|drawable_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|image_name
argument_list|)
expr_stmt|;
name|thumb
operator|=
name|gimp_drawable_get_thumbnail
argument_list|(
name|drawables
index|[
name|i
index|]
argument_list|,
name|MENU_THUMBNAIL_SIZE
argument_list|,
name|MENU_THUMBNAIL_SIZE
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
name|drawables
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
name|added
operator|++
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
return|return
name|added
return|;
block|}
end_function

end_unit

