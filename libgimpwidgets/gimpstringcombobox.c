begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpstringcombobox.c  * Copyright (C) 2007  Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
file|"gimpstringcombobox.h"
end_include

begin_comment
comment|/**  * SECTION: gimpstringcombobox  * @title: GimpStringComboBox  * @short_description: A #GtkComboBox subclass to select strings.  *  * A #GtkComboBox subclass to select strings.  **/
end_comment

begin_enum
enum|enum
DECL|enum|__anon29c47e1b0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_ID_COLUMN
name|PROP_ID_COLUMN
block|,
DECL|enumerator|PROP_LABEL_COLUMN
name|PROP_LABEL_COLUMN
block|,
DECL|enumerator|PROP_ELLIPSIZE
name|PROP_ELLIPSIZE
block|}
enum|;
end_enum

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon29c47e1b0208
block|{
DECL|member|id_column
name|gint
name|id_column
decl_stmt|;
DECL|member|label_column
name|gint
name|label_column
decl_stmt|;
DECL|member|text_renderer
name|GtkCellRenderer
modifier|*
name|text_renderer
decl_stmt|;
DECL|typedef|GimpStringComboBoxPrivate
block|}
name|GimpStringComboBoxPrivate
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_STRING_COMBO_BOX_GET_PRIVATE (obj)
define|#
directive|define
name|GIMP_STRING_COMBO_BOX_GET_PRIVATE
parameter_list|(
name|obj
parameter_list|)
define|\
value|((GimpStringComboBoxPrivate *) ((GimpStringComboBox *) (obj))->priv)
end_define

begin_function_decl
specifier|static
name|void
name|gimp_string_combo_box_constructed
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
name|gimp_string_combo_box_set_property
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
name|gimp_string_combo_box_get_property
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

begin_macro
DECL|function|G_DEFINE_TYPE (GimpStringComboBox,gimp_string_combo_box,GTK_TYPE_COMBO_BOX)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpStringComboBox
argument_list|,
argument|gimp_string_combo_box
argument_list|,
argument|GTK_TYPE_COMBO_BOX
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_string_combo_box_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_string_combo_box_class_init
parameter_list|(
name|GimpStringComboBoxClass
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
name|constructed
operator|=
name|gimp_string_combo_box_constructed
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_string_combo_box_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_string_combo_box_get_property
expr_stmt|;
comment|/**    * GimpStringComboBox:id-column:    *    * The column in the associated GtkTreeModel that holds unique    * string IDs.    *    * Since: 2.4    */
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_ID_COLUMN
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"id-column"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|G_MAXINT
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
comment|/**    * GimpStringComboBox:id-column:    *    * The column in the associated GtkTreeModel that holds strings to    * be used as labels in the combo-box.    *    * Since: 2.4    */
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_LABEL_COLUMN
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"label-column"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|G_MAXINT
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
comment|/**    * GimpStringComboBox:ellipsize:    *    * Specifies the preferred place to ellipsize text in the combo-box,    * if the cell renderer does not have enough room to display the    * entire string.    *    * Since: 2.4    */
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
name|GimpStringComboBoxPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_string_combo_box_init (GimpStringComboBox * combo_box)
name|gimp_string_combo_box_init
parameter_list|(
name|GimpStringComboBox
modifier|*
name|combo_box
parameter_list|)
block|{
name|combo_box
operator|->
name|priv
operator|=
name|G_TYPE_INSTANCE_GET_PRIVATE
argument_list|(
name|combo_box
argument_list|,
name|GIMP_TYPE_STRING_COMBO_BOX
argument_list|,
name|GimpStringComboBoxPrivate
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_string_combo_box_constructed (GObject * object)
name|gimp_string_combo_box_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpStringComboBoxPrivate
modifier|*
name|priv
init|=
name|GIMP_STRING_COMBO_BOX_GET_PRIVATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GtkCellRenderer
modifier|*
name|cell
decl_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructed
argument_list|(
name|object
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
name|object
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
name|object
argument_list|)
argument_list|,
name|cell
argument_list|,
literal|"text"
argument_list|,
name|priv
operator|->
name|label_column
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_string_combo_box_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_string_combo_box_set_property
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
name|GimpStringComboBoxPrivate
modifier|*
name|priv
init|=
name|GIMP_STRING_COMBO_BOX_GET_PRIVATE
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
name|PROP_ID_COLUMN
case|:
name|priv
operator|->
name|id_column
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_LABEL_COLUMN
case|:
name|priv
operator|->
name|label_column
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
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
DECL|function|gimp_string_combo_box_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_string_combo_box_get_property
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
name|GimpStringComboBoxPrivate
modifier|*
name|priv
init|=
name|GIMP_STRING_COMBO_BOX_GET_PRIVATE
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
name|PROP_ID_COLUMN
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|priv
operator|->
name|id_column
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_LABEL_COLUMN
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|priv
operator|->
name|label_column
argument_list|)
expr_stmt|;
break|break;
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

begin_function
specifier|static
name|gboolean
DECL|function|gimp_string_model_lookup (GtkTreeModel * model,gint column,const gchar * id,GtkTreeIter * iter)
name|gimp_string_model_lookup
parameter_list|(
name|GtkTreeModel
modifier|*
name|model
parameter_list|,
name|gint
name|column
parameter_list|,
specifier|const
name|gchar
modifier|*
name|id
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|)
block|{
name|GValue
name|value
init|=
name|G_VALUE_INIT
decl_stmt|;
name|gboolean
name|iter_valid
decl_stmt|;
comment|/*  This lookup could be backed up by a hash table or some other    *  data structure instead of doing a list traversal. But since this    *  is a GtkComboBox, there shouldn't be many entries anyway...    */
for|for
control|(
name|iter_valid
operator|=
name|gtk_tree_model_get_iter_first
argument_list|(
name|model
argument_list|,
name|iter
argument_list|)
init|;
name|iter_valid
condition|;
name|iter_valid
operator|=
name|gtk_tree_model_iter_next
argument_list|(
name|model
argument_list|,
name|iter
argument_list|)
control|)
block|{
specifier|const
name|gchar
modifier|*
name|str
decl_stmt|;
name|gtk_tree_model_get_value
argument_list|(
name|model
argument_list|,
name|iter
argument_list|,
name|column
argument_list|,
operator|&
name|value
argument_list|)
expr_stmt|;
name|str
operator|=
name|g_value_get_string
argument_list|(
operator|&
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|str
operator|&&
name|strcmp
argument_list|(
name|str
argument_list|,
name|id
argument_list|)
operator|==
literal|0
condition|)
block|{
name|g_value_unset
argument_list|(
operator|&
name|value
argument_list|)
expr_stmt|;
break|break;
block|}
name|g_value_unset
argument_list|(
operator|&
name|value
argument_list|)
expr_stmt|;
block|}
return|return
name|iter_valid
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_string_combo_box_new:  * @model:        a #GtkTreeModel  * @id_column:    the model column of the ID  * @label_column: the modl column of the label  *  * Return value: a new #GimpStringComboBox.  *  * Since: 2.4  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_string_combo_box_new (GtkTreeModel * model,gint id_column,gint label_column)
name|gimp_string_combo_box_new
parameter_list|(
name|GtkTreeModel
modifier|*
name|model
parameter_list|,
name|gint
name|id_column
parameter_list|,
name|gint
name|label_column
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GTK_IS_TREE_MODEL
argument_list|(
name|model
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gtk_tree_model_get_column_type
argument_list|(
name|model
argument_list|,
name|id_column
argument_list|)
operator|==
name|G_TYPE_STRING
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gtk_tree_model_get_column_type
argument_list|(
name|model
argument_list|,
name|label_column
argument_list|)
operator|==
name|G_TYPE_STRING
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_STRING_COMBO_BOX
argument_list|,
literal|"model"
argument_list|,
name|model
argument_list|,
literal|"id-column"
argument_list|,
name|id_column
argument_list|,
literal|"label-column"
argument_list|,
name|label_column
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_string_combo_box_set_active:  * @combo_box: a #GimpStringComboBox  * @id:        the ID of the item to select  *  * Looks up the item that belongs to the given @id and makes it the  * selected item in the @combo_box.  *  * Return value: %TRUE on success or %FALSE if there was no item for  *               this value.  *  * Since: 2.4  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_string_combo_box_set_active (GimpStringComboBox * combo_box,const gchar * id)
name|gimp_string_combo_box_set_active
parameter_list|(
name|GimpStringComboBox
modifier|*
name|combo_box
parameter_list|,
specifier|const
name|gchar
modifier|*
name|id
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_STRING_COMBO_BOX
argument_list|(
name|combo_box
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|id
condition|)
block|{
name|GtkTreeModel
modifier|*
name|model
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|gint
name|column
decl_stmt|;
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
name|column
operator|=
name|GIMP_STRING_COMBO_BOX_GET_PRIVATE
argument_list|(
name|combo_box
argument_list|)
operator|->
name|id_column
expr_stmt|;
if|if
condition|(
name|gimp_string_model_lookup
argument_list|(
name|model
argument_list|,
name|column
argument_list|,
name|id
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
else|else
block|{
name|gtk_combo_box_set_active
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|combo_box
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_string_combo_box_get_active:  * @combo_box: a #GimpStringComboBox  *  * Retrieves the value of the selected (active) item in the @combo_box.  *  * Return value: newly allocated ID string or %NULL if nothing was selected  *  * Since: 2.4  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_string_combo_box_get_active (GimpStringComboBox * combo_box)
name|gimp_string_combo_box_get_active
parameter_list|(
name|GimpStringComboBox
modifier|*
name|combo_box
parameter_list|)
block|{
name|GtkTreeIter
name|iter
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_STRING_COMBO_BOX
argument_list|(
name|combo_box
argument_list|)
argument_list|,
name|NULL
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
name|GtkTreeModel
modifier|*
name|model
init|=
name|gtk_combo_box_get_model
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|combo_box
argument_list|)
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|value
decl_stmt|;
name|gint
name|column
decl_stmt|;
name|column
operator|=
name|GIMP_STRING_COMBO_BOX_GET_PRIVATE
argument_list|(
name|combo_box
argument_list|)
operator|->
name|id_column
expr_stmt|;
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|,
name|column
argument_list|,
operator|&
name|value
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
return|return
name|value
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

end_unit

