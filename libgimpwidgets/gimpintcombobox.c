begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpintcombobox.c  * Copyright (C) 2004  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<libintl.h>
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
file|"gimpintcombobox.h"
end_include

begin_include
include|#
directive|include
file|"gimpintstore.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_int_combo_box_init
parameter_list|(
name|GimpIntComboBox
modifier|*
name|combo_box
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|GType
DECL|function|gimp_int_combo_box_get_type (void)
name|gimp_int_combo_box_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|box_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|box_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|box_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpIntComboBoxClass
argument_list|)
block|,
name|NULL
block|,
comment|/* base_init      */
name|NULL
block|,
comment|/* base_finalize  */
name|NULL
block|,
comment|/* class_init     */
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpIntComboBox
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_int_combo_box_init
block|}
decl_stmt|;
name|box_type
operator|=
name|g_type_register_static
argument_list|(
name|GTK_TYPE_COMBO_BOX
argument_list|,
literal|"GimpIntComboBox"
argument_list|,
operator|&
name|box_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|box_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_int_combo_box_init (GimpIntComboBox * combo_box)
name|gimp_int_combo_box_init
parameter_list|(
name|GimpIntComboBox
modifier|*
name|combo_box
parameter_list|)
block|{
name|GtkListStore
modifier|*
name|store
decl_stmt|;
name|GtkCellRenderer
modifier|*
name|cell
decl_stmt|;
name|store
operator|=
name|gimp_int_store_new
argument_list|()
expr_stmt|;
name|gtk_combo_box_set_model
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|combo_box
argument_list|)
argument_list|,
name|GTK_TREE_MODEL
argument_list|(
name|store
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|store
argument_list|)
expr_stmt|;
name|cell
operator|=
name|gtk_cell_renderer_pixbuf_new
argument_list|()
expr_stmt|;
name|gtk_cell_layout_pack_start
argument_list|(
name|GTK_CELL_LAYOUT
argument_list|(
name|combo_box
argument_list|)
argument_list|,
name|cell
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_cell_layout_set_attributes
argument_list|(
name|GTK_CELL_LAYOUT
argument_list|(
name|combo_box
argument_list|)
argument_list|,
name|cell
argument_list|,
literal|"stock_id"
argument_list|,
name|GIMP_INT_STORE_STOCK_ID
argument_list|,
literal|"pixbuf"
argument_list|,
name|GIMP_INT_STORE_PIXBUF
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|cell
operator|=
name|gtk_cell_renderer_text_new
argument_list|()
expr_stmt|;
name|gtk_cell_layout_pack_start
argument_list|(
name|GTK_CELL_LAYOUT
argument_list|(
name|combo_box
argument_list|)
argument_list|,
name|cell
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_cell_layout_set_attributes
argument_list|(
name|GTK_CELL_LAYOUT
argument_list|(
name|combo_box
argument_list|)
argument_list|,
name|cell
argument_list|,
literal|"text"
argument_list|,
name|GIMP_INT_STORE_LABEL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_int_combo_box_new:  * @first_label: the label of the first item  * @first_value: the value of the first item  * @...: a %NULL terminated list of more label, value pairs  *  * Creates a GtkComboBox that has integer values associated with each  * item. The items to fill the combo box with are specified as a %NULL  * terminated list of label/value pairs.  *  * Return value: a new #GimpIntComboBox.  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_int_combo_box_new (const gchar * first_label,gint first_value,...)
name|gimp_int_combo_box_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|first_label
parameter_list|,
name|gint
name|first_value
parameter_list|,
modifier|...
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|combo_box
decl_stmt|;
name|va_list
name|args
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|first_label
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|first_value
argument_list|)
expr_stmt|;
name|combo_box
operator|=
name|gimp_int_combo_box_new_valist
argument_list|(
name|first_label
argument_list|,
name|first_value
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
name|combo_box
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_int_combo_box_new_valist:  * @first_label: the label of the first item  * @first_value: the value of the first item  * @values: a va_list with more values  *  * A variant of gimp_int_combo_box_new() that takes a va_list of  * label/value pairs. Probably only useful for language bindings.  *  * Return value: a new #GimpIntComboBox.  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_int_combo_box_new_valist (const gchar * first_label,gint first_value,va_list values)
name|gimp_int_combo_box_new_valist
parameter_list|(
specifier|const
name|gchar
modifier|*
name|first_label
parameter_list|,
name|gint
name|first_value
parameter_list|,
name|va_list
name|values
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|combo_box
decl_stmt|;
name|GtkListStore
modifier|*
name|store
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|label
decl_stmt|;
name|gint
name|value
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|first_label
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|store
operator|=
name|gimp_int_store_new
argument_list|()
expr_stmt|;
name|combo_box
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_INT_COMBO_BOX
argument_list|,
literal|"model"
argument_list|,
name|store
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|store
argument_list|)
expr_stmt|;
for|for
control|(
name|label
operator|=
name|first_label
operator|,
name|value
operator|=
name|first_value
init|;
name|label
condition|;
name|label
operator|=
name|va_arg
argument_list|(
name|values
argument_list|,
specifier|const
name|gchar
operator|*
argument_list|)
operator|,
name|value
operator|=
name|va_arg
argument_list|(
name|values
argument_list|,
name|gint
argument_list|)
control|)
block|{
name|GtkTreeIter
name|iter
decl_stmt|;
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
name|value
argument_list|,
name|GIMP_INT_STORE_LABEL
argument_list|,
name|label
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
return|return
name|combo_box
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_int_combo_box_new_array:  * @n_values: the number of values  * @labels:   an array of labels (array length must be @n_values)  *  * A variant of gimp_int_combo_box_new() that takes an array of labels.  * The array indices are used as values.  *  * Return value: a new #GimpIntComboBox.  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_int_combo_box_new_array (gint n_values,const gchar * labels[])
name|gimp_int_combo_box_new_array
parameter_list|(
name|gint
name|n_values
parameter_list|,
specifier|const
name|gchar
modifier|*
name|labels
index|[]
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|combo_box
decl_stmt|;
name|GtkListStore
modifier|*
name|store
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|n_values
operator|>
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|labels
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|store
operator|=
name|gimp_int_store_new
argument_list|()
expr_stmt|;
name|combo_box
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_INT_COMBO_BOX
argument_list|,
literal|"model"
argument_list|,
name|store
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|store
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
name|GtkTreeIter
name|iter
decl_stmt|;
if|if
condition|(
name|labels
index|[
name|i
index|]
condition|)
block|{
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
name|i
argument_list|,
name|GIMP_INT_STORE_LABEL
argument_list|,
name|gettext
argument_list|(
name|labels
index|[
name|i
index|]
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|combo_box
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_int_combo_box_prepend:  * @combo_box: a #GimpIntComboBox  * @...:       pairs of column number and value, terminated with -1  *  * This function provides a convenient way to prepend items to a  * #GimpIntComboBox. It prepends a row to the @combo_box's list store  * and calls gtk_list_store_set() for you.  *  * The column number must be taken from the enum #GimpIntStoreColumns.  **/
end_comment

begin_function
name|void
DECL|function|gimp_int_combo_box_prepend (GimpIntComboBox * combo_box,...)
name|gimp_int_combo_box_prepend
parameter_list|(
name|GimpIntComboBox
modifier|*
name|combo_box
parameter_list|,
modifier|...
parameter_list|)
block|{
name|GtkListStore
modifier|*
name|store
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|va_list
name|args
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_INT_COMBO_BOX
argument_list|(
name|combo_box
argument_list|)
argument_list|)
expr_stmt|;
name|store
operator|=
name|GTK_LIST_STORE
argument_list|(
name|gtk_combo_box_get_model
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|combo_box
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|combo_box
argument_list|)
expr_stmt|;
name|gtk_list_store_prepend
argument_list|(
name|store
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
name|gtk_list_store_set_valist
argument_list|(
name|store
argument_list|,
operator|&
name|iter
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_int_combo_box_append:  * @combo_box: a #GimpIntComboBox  * @...:       pairs of column number and value, terminated with -1  *  * This function provides a convenient way to append items to a  * #GimpIntComboBox. It appends a row to the @combo_box's list store  * and calls gtk_list_store_set() for you.  *  * The column number must be taken from the enum #GimpIntStoreColumns.  **/
end_comment

begin_function
name|void
DECL|function|gimp_int_combo_box_append (GimpIntComboBox * combo_box,...)
name|gimp_int_combo_box_append
parameter_list|(
name|GimpIntComboBox
modifier|*
name|combo_box
parameter_list|,
modifier|...
parameter_list|)
block|{
name|GtkListStore
modifier|*
name|store
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|va_list
name|args
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_INT_COMBO_BOX
argument_list|(
name|combo_box
argument_list|)
argument_list|)
expr_stmt|;
name|store
operator|=
name|GTK_LIST_STORE
argument_list|(
name|gtk_combo_box_get_model
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|combo_box
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|combo_box
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
name|gtk_list_store_set_valist
argument_list|(
name|store
argument_list|,
operator|&
name|iter
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_int_combo_box_set_active:  * @combo_box: a #GimpIntComboBox  * @value:     an integer value  *  * Looks up the item that belongs to the given @value and makes it the  * selected item in the @combo_box.  *  * Return value: %TRUE on success or %FALSE if there was no item for  *               this value.  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_int_combo_box_set_active (GimpIntComboBox * combo_box,gint value)
name|gimp_int_combo_box_set_active
parameter_list|(
name|GimpIntComboBox
modifier|*
name|combo_box
parameter_list|,
name|gint
name|value
parameter_list|)
block|{
name|GtkTreeModel
modifier|*
name|model
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_INT_COMBO_BOX
argument_list|(
name|combo_box
argument_list|)
argument_list|,
name|FALSE
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
if|if
condition|(
name|gimp_int_store_lookup_by_value
argument_list|(
name|model
argument_list|,
name|value
argument_list|,
operator|&
name|iter
argument_list|)
condition|)
block|{
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
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_int_combo_box_get_active:  * @combo_box: a #GimpIntComboBox  * @value:     return location for the integer value  *  * Retrieves the value of the selected (active) item in the @combo_box.  *  * Return value: %TRUE if @value has been set or %FALSE if no item was  *               active.  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_int_combo_box_get_active (GimpIntComboBox * combo_box,gint * value)
name|gimp_int_combo_box_get_active
parameter_list|(
name|GimpIntComboBox
modifier|*
name|combo_box
parameter_list|,
name|gint
modifier|*
name|value
parameter_list|)
block|{
name|GtkTreeIter
name|iter
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_INT_COMBO_BOX
argument_list|(
name|combo_box
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|value
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|gtk_combo_box_get_active_iter
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|combo_box
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|)
condition|)
block|{
name|gtk_tree_model_get
argument_list|(
name|gtk_combo_box_get_model
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|combo_box
argument_list|)
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|,
name|GIMP_INT_STORE_VALUE
argument_list|,
name|value
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

end_unit

