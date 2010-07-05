begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpintcombobox.c  * Copyright (C) 2004  Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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

begin_comment
comment|/**  * SECTION: gimpintcombobox  * @title: GimpIntComboBox  * @short_description: A widget providing a popup menu of integer  *                     values (e.g. enums).  *  * A widget providing a popup menu of integer values (e.g. enums).  **/
end_comment

begin_enum
enum|enum
DECL|enum|__anon296de2bc0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_ELLIPSIZE
name|PROP_ELLIPSIZE
block|}
enum|;
end_enum

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon296de2bc0208
block|{
DECL|member|pixbuf_renderer
name|GtkCellRenderer
modifier|*
name|pixbuf_renderer
decl_stmt|;
DECL|member|text_renderer
name|GtkCellRenderer
modifier|*
name|text_renderer
decl_stmt|;
DECL|member|sensitivity_func
name|GimpIntSensitivityFunc
name|sensitivity_func
decl_stmt|;
DECL|member|sensitivity_data
name|gpointer
name|sensitivity_data
decl_stmt|;
DECL|member|sensitivity_destroy
name|GDestroyNotify
name|sensitivity_destroy
decl_stmt|;
DECL|typedef|GimpIntComboBoxPrivate
block|}
name|GimpIntComboBoxPrivate
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_INT_COMBO_BOX_GET_PRIVATE (obj)
define|#
directive|define
name|GIMP_INT_COMBO_BOX_GET_PRIVATE
parameter_list|(
name|obj
parameter_list|)
define|\
value|((GimpIntComboBoxPrivate *) ((GimpIntComboBox *) (obj))->priv)
end_define

begin_function_decl
specifier|static
name|void
name|gimp_int_combo_box_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_int_combo_box_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_int_combo_box_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_int_combo_box_data_func
parameter_list|(
name|GtkCellLayout
modifier|*
name|layout
parameter_list|,
name|GtkCellRenderer
modifier|*
name|cell
parameter_list|,
name|GtkTreeModel
modifier|*
name|model
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpIntComboBox,gimp_int_combo_box,GTK_TYPE_COMBO_BOX)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpIntComboBox
argument_list|,
argument|gimp_int_combo_box
argument_list|,
argument|GTK_TYPE_COMBO_BOX
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_int_combo_box_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_int_combo_box_class_init
parameter_list|(
name|GimpIntComboBoxClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_int_combo_box_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_int_combo_box_get_property
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_int_combo_box_finalize
expr_stmt|;
comment|/**    * GimpIntComboBox:ellipsize:    *    * Specifies the preferred place to ellipsize text in the combo-box,    * if the cell renderer does not have enough room to display the    * entire string.    *    * Since: GIMP 2.4    */
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_ELLIPSIZE
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"ellipsize"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|PANGO_TYPE_ELLIPSIZE_MODE
argument_list|,
name|PANGO_ELLIPSIZE_NONE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|object_class
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpIntComboBoxPrivate
argument_list|)
argument_list|)
expr_stmt|;
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
name|GimpIntComboBoxPrivate
modifier|*
name|priv
decl_stmt|;
name|GtkListStore
modifier|*
name|store
decl_stmt|;
name|GtkCellRenderer
modifier|*
name|cell
decl_stmt|;
name|combo_box
operator|->
name|priv
operator|=
name|G_TYPE_INSTANCE_GET_PRIVATE
argument_list|(
name|combo_box
argument_list|,
name|GIMP_TYPE_INT_COMBO_BOX
argument_list|,
name|GimpIntComboBoxPrivate
argument_list|)
expr_stmt|;
name|priv
operator|=
name|GIMP_INT_COMBO_BOX_GET_PRIVATE
argument_list|(
name|combo_box
argument_list|)
expr_stmt|;
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
name|priv
operator|=
name|GIMP_INT_COMBO_BOX_GET_PRIVATE
argument_list|(
name|combo_box
argument_list|)
expr_stmt|;
name|priv
operator|->
name|pixbuf_renderer
operator|=
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
literal|"stock-id"
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
name|priv
operator|->
name|text_renderer
operator|=
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

begin_function
specifier|static
name|void
DECL|function|gimp_int_combo_box_finalize (GObject * object)
name|gimp_int_combo_box_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpIntComboBoxPrivate
modifier|*
name|priv
init|=
name|GIMP_INT_COMBO_BOX_GET_PRIVATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|priv
operator|->
name|sensitivity_destroy
condition|)
block|{
name|GDestroyNotify
name|d
init|=
name|priv
operator|->
name|sensitivity_destroy
decl_stmt|;
name|priv
operator|->
name|sensitivity_destroy
operator|=
name|NULL
expr_stmt|;
name|d
argument_list|(
name|priv
operator|->
name|sensitivity_data
argument_list|)
expr_stmt|;
block|}
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

begin_function
specifier|static
name|void
DECL|function|gimp_int_combo_box_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_int_combo_box_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpIntComboBoxPrivate
modifier|*
name|priv
init|=
name|GIMP_INT_COMBO_BOX_GET_PRIVATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_ELLIPSIZE
case|:
name|g_object_set_property
argument_list|(
name|G_OBJECT
argument_list|(
name|priv
operator|->
name|text_renderer
argument_list|)
argument_list|,
name|pspec
operator|->
name|name
argument_list|,
name|value
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_int_combo_box_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_int_combo_box_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpIntComboBoxPrivate
modifier|*
name|priv
init|=
name|GIMP_INT_COMBO_BOX_GET_PRIVATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_ELLIPSIZE
case|:
name|g_object_get_property
argument_list|(
name|G_OBJECT
argument_list|(
name|priv
operator|->
name|text_renderer
argument_list|)
argument_list|,
name|pspec
operator|->
name|name
argument_list|,
name|value
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_int_combo_box_new:  * @first_label: the label of the first item  * @first_value: the value of the first item  * @...: a %NULL terminated list of more label, value pairs  *  * Creates a GtkComboBox that has integer values associated with each  * item. The items to fill the combo box with are specified as a %NULL  * terminated list of label/value pairs.  *  * If you need to construct an empty #GimpIntComboBox, it's best to use  * g_object_new (GIMP_TYPE_INT_COMBO_BOX, NULL).  *  * Return value: a new #GimpIntComboBox.  *  * Since: GIMP 2.2  **/
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
name|combo_box
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_INT_COMBO_BOX
argument_list|,
name|NULL
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
operator|>=
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
operator|||
name|n_values
operator|==
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|combo_box
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_INT_COMBO_BOX
argument_list|,
name|NULL
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
comment|/**  * gimp_int_combo_box_prepend:  * @combo_box: a #GimpIntComboBox  * @...:       pairs of column number and value, terminated with -1  *  * This function provides a convenient way to prepend items to a  * #GimpIntComboBox. It prepends a row to the @combo_box's list store  * and calls gtk_list_store_set() for you.  *  * The column number must be taken from the enum #GimpIntStoreColumns.  *  * Since: GIMP 2.2  **/
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
comment|/**  * gimp_int_combo_box_append:  * @combo_box: a #GimpIntComboBox  * @...:       pairs of column number and value, terminated with -1  *  * This function provides a convenient way to append items to a  * #GimpIntComboBox. It appends a row to the @combo_box's list store  * and calls gtk_list_store_set() for you.  *  * The column number must be taken from the enum #GimpIntStoreColumns.  *  * Since: GIMP 2.2  **/
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

begin_comment
comment|/**  * gimp_int_combo_box_connect:  * @combo_box: a #GimpIntComboBox  * @value:     the value to set  * @callback:  a callback to connect to the @combo_box's "changed" signal  * @data:      a pointer passed as data to g_signal_connect()  *  * A convenience function that sets the inital @value of a  * #GimpIntComboBox and connects @callback to the "changed"  * signal.  *  * This function also calls the @callback once after setting the  * initial @value. This is often convenient when working with combo  * boxes that select a default active item, like for example  * gimp_drawable_combo_box_new(). If you pass an invalid initial  * @value, the @callback will be called with the default item active.  *  * Return value: the signal handler ID as returned by g_signal_connect()  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|gulong
DECL|function|gimp_int_combo_box_connect (GimpIntComboBox * combo_box,gint value,GCallback callback,gpointer data)
name|gimp_int_combo_box_connect
parameter_list|(
name|GimpIntComboBox
modifier|*
name|combo_box
parameter_list|,
name|gint
name|value
parameter_list|,
name|GCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gulong
name|handler
init|=
literal|0
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_INT_COMBO_BOX
argument_list|(
name|combo_box
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|callback
condition|)
name|handler
operator|=
name|g_signal_connect
argument_list|(
name|combo_box
argument_list|,
literal|"changed"
argument_list|,
name|callback
argument_list|,
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_int_combo_box_set_active
argument_list|(
name|combo_box
argument_list|,
name|value
argument_list|)
condition|)
name|g_signal_emit_by_name
argument_list|(
name|combo_box
argument_list|,
literal|"changed"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|handler
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_int_combo_box_set_sensitivity:  * @combo_box: a #GimpIntComboBox  * @func: a function that returns a boolean value, or %NULL to unset  * @data: data to pass to @func  * @destroy: destroy notification for @data  *  * Sets a function that is used to decide about the sensitivity of  * rows in the @combo_box. Use this if you want to set certain rows  * insensitive.  *  * Calling gtk_widget_queue_draw() on the @combo_box will cause the  * sensitivity to be updated.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|void
DECL|function|gimp_int_combo_box_set_sensitivity (GimpIntComboBox * combo_box,GimpIntSensitivityFunc func,gpointer data,GDestroyNotify destroy)
name|gimp_int_combo_box_set_sensitivity
parameter_list|(
name|GimpIntComboBox
modifier|*
name|combo_box
parameter_list|,
name|GimpIntSensitivityFunc
name|func
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|GDestroyNotify
name|destroy
parameter_list|)
block|{
name|GimpIntComboBoxPrivate
modifier|*
name|priv
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_INT_COMBO_BOX
argument_list|(
name|combo_box
argument_list|)
argument_list|)
expr_stmt|;
name|priv
operator|=
name|GIMP_INT_COMBO_BOX_GET_PRIVATE
argument_list|(
name|combo_box
argument_list|)
expr_stmt|;
if|if
condition|(
name|priv
operator|->
name|sensitivity_destroy
condition|)
block|{
name|GDestroyNotify
name|d
init|=
name|priv
operator|->
name|sensitivity_destroy
decl_stmt|;
name|priv
operator|->
name|sensitivity_destroy
operator|=
name|NULL
expr_stmt|;
name|d
argument_list|(
name|priv
operator|->
name|sensitivity_data
argument_list|)
expr_stmt|;
block|}
name|priv
operator|->
name|sensitivity_func
operator|=
name|func
expr_stmt|;
name|priv
operator|->
name|sensitivity_data
operator|=
name|data
expr_stmt|;
name|priv
operator|->
name|sensitivity_destroy
operator|=
name|destroy
expr_stmt|;
name|gtk_cell_layout_set_cell_data_func
argument_list|(
name|GTK_CELL_LAYOUT
argument_list|(
name|combo_box
argument_list|)
argument_list|,
name|priv
operator|->
name|pixbuf_renderer
argument_list|,
name|func
condition|?
name|gimp_int_combo_box_data_func
else|:
name|NULL
argument_list|,
name|priv
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_cell_layout_set_cell_data_func
argument_list|(
name|GTK_CELL_LAYOUT
argument_list|(
name|combo_box
argument_list|)
argument_list|,
name|priv
operator|->
name|text_renderer
argument_list|,
name|func
condition|?
name|gimp_int_combo_box_data_func
else|:
name|NULL
argument_list|,
name|priv
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_int_combo_box_data_func (GtkCellLayout * layout,GtkCellRenderer * cell,GtkTreeModel * model,GtkTreeIter * iter,gpointer data)
name|gimp_int_combo_box_data_func
parameter_list|(
name|GtkCellLayout
modifier|*
name|layout
parameter_list|,
name|GtkCellRenderer
modifier|*
name|cell
parameter_list|,
name|GtkTreeModel
modifier|*
name|model
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpIntComboBoxPrivate
modifier|*
name|priv
init|=
name|data
decl_stmt|;
if|if
condition|(
name|priv
operator|->
name|sensitivity_func
condition|)
block|{
name|gint
name|value
decl_stmt|;
name|gboolean
name|sensitive
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
name|iter
argument_list|,
name|GIMP_INT_STORE_VALUE
argument_list|,
operator|&
name|value
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|sensitive
operator|=
name|priv
operator|->
name|sensitivity_func
argument_list|(
name|value
argument_list|,
name|priv
operator|->
name|sensitivity_data
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|cell
argument_list|,
literal|"sensitive"
argument_list|,
name|sensitive
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

