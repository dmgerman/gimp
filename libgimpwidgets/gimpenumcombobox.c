begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpenumcombobox.c  * Copyright (C) 2004  Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
file|"gimpwidgetstypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpenumcombobox.h"
end_include

begin_include
include|#
directive|include
file|"gimpenumstore.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/libgimp-intl.h"
end_include

begin_comment
comment|/**  * SECTION: gimpenumcombobox  * @title: GimpEnumComboBox  * @short_description: A #GimpIntComboBox subclass for selecting an enum value.  *  * A #GtkComboBox subclass for selecting an enum value.  **/
end_comment

begin_enum
enum|enum
DECL|enum|__anon2ba4890b0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_MODEL
name|PROP_MODEL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_enum_combo_box_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|prop_id
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
name|gimp_enum_combo_box_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|prop_id
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
name|GimpIntComboBoxLayout
name|gimp_enum_combo_box_layout_from_store
parameter_list|(
name|GimpEnumStore
modifier|*
name|enum_store
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpEnumComboBox,gimp_enum_combo_box,GIMP_TYPE_INT_COMBO_BOX)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpEnumComboBox
argument_list|,
argument|gimp_enum_combo_box
argument_list|,
argument|GIMP_TYPE_INT_COMBO_BOX
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_enum_combo_box_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_enum_combo_box_class_init
parameter_list|(
name|GimpEnumComboBoxClass
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
name|gimp_enum_combo_box_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_enum_combo_box_get_property
expr_stmt|;
comment|/*  override the "model" property of GtkComboBox  */
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_MODEL
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"model"
argument_list|,
literal|"Model"
argument_list|,
literal|"The enum store used by this combo box"
argument_list|,
name|GIMP_TYPE_ENUM_STORE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_enum_combo_box_init (GimpEnumComboBox * combo_box)
name|gimp_enum_combo_box_init
parameter_list|(
name|GimpEnumComboBox
modifier|*
name|combo_box
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_enum_combo_box_set_property (GObject * object,guint prop_id,const GValue * value,GParamSpec * pspec)
name|gimp_enum_combo_box_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|prop_id
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
name|GtkComboBox
modifier|*
name|combo_box
init|=
name|GTK_COMBO_BOX
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|prop_id
condition|)
block|{
case|case
name|PROP_MODEL
case|:
name|gtk_combo_box_set_model
argument_list|(
name|combo_box
argument_list|,
name|g_value_get_object
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|prop_id
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
DECL|function|gimp_enum_combo_box_get_property (GObject * object,guint prop_id,GValue * value,GParamSpec * pspec)
name|gimp_enum_combo_box_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|prop_id
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
name|GtkComboBox
modifier|*
name|combo_box
init|=
name|GTK_COMBO_BOX
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|prop_id
condition|)
block|{
case|case
name|PROP_MODEL
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|gtk_combo_box_get_model
argument_list|(
name|combo_box
argument_list|)
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|prop_id
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
name|GimpIntComboBoxLayout
DECL|function|gimp_enum_combo_box_layout_from_store (GimpEnumStore * enum_store)
name|gimp_enum_combo_box_layout_from_store
parameter_list|(
name|GimpEnumStore
modifier|*
name|enum_store
parameter_list|)
block|{
name|GtkTreeModel
modifier|*
name|model
init|=
name|GTK_TREE_MODEL
argument_list|(
name|enum_store
argument_list|)
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|gboolean
name|iter_valid
decl_stmt|;
name|gboolean
name|has_abbrev
init|=
name|FALSE
decl_stmt|;
for|for
control|(
name|iter_valid
operator|=
name|gtk_tree_model_get_iter_first
argument_list|(
name|model
argument_list|,
operator|&
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
operator|&
name|iter
argument_list|)
control|)
block|{
name|gchar
modifier|*
name|abbrev
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|,
name|GIMP_INT_STORE_ABBREV
argument_list|,
operator|&
name|abbrev
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|abbrev
condition|)
block|{
name|has_abbrev
operator|=
name|TRUE
expr_stmt|;
name|g_free
argument_list|(
name|abbrev
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
if|if
condition|(
name|has_abbrev
condition|)
return|return
name|GIMP_INT_COMBO_BOX_LAYOUT_ABBREVIATED
return|;
else|else
return|return
name|GIMP_INT_COMBO_BOX_LAYOUT_FULL
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_enum_combo_box_new:  * @enum_type: the #GType of an enum.  *  * Creates a #GtkComboBox readily filled with all enum values from a  * given @enum_type. The enum needs to be registered to the type  * system. It should also have %GimpEnumDesc descriptions registered  * that contain translatable value names. This is the case for the  * enums used in the GIMP PDB functions.  *  * This is just a convenience function. If you need more control over  * the enum values that appear in the combo_box, you can create your  * own #GimpEnumStore and use gimp_enum_combo_box_new_with_model().  *  * Return value: a new #GimpEnumComboBox.  *  * Since: 2.4  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_enum_combo_box_new (GType enum_type)
name|gimp_enum_combo_box_new
parameter_list|(
name|GType
name|enum_type
parameter_list|)
block|{
name|GtkListStore
modifier|*
name|store
decl_stmt|;
name|GtkWidget
modifier|*
name|combo_box
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
name|store
operator|=
name|gimp_enum_store_new
argument_list|(
name|enum_type
argument_list|)
expr_stmt|;
name|combo_box
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_ENUM_COMBO_BOX
argument_list|,
literal|"model"
argument_list|,
name|store
argument_list|,
literal|"layout"
argument_list|,
name|gimp_enum_combo_box_layout_from_store
argument_list|(
name|GIMP_ENUM_STORE
argument_list|(
name|store
argument_list|)
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|store
argument_list|)
expr_stmt|;
return|return
name|combo_box
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_enum_combo_box_new_with_model  * @enum_store: a #GimpEnumStore to use as the model  *  * Creates a #GtkComboBox for the given @enum_store.  *  * Return value: a new #GimpEnumComboBox.  *  * Since: 2.4  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_enum_combo_box_new_with_model (GimpEnumStore * enum_store)
name|gimp_enum_combo_box_new_with_model
parameter_list|(
name|GimpEnumStore
modifier|*
name|enum_store
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_ENUM_STORE
argument_list|(
name|enum_store
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_ENUM_COMBO_BOX
argument_list|,
literal|"model"
argument_list|,
name|enum_store
argument_list|,
literal|"layout"
argument_list|,
name|gimp_enum_combo_box_layout_from_store
argument_list|(
name|enum_store
argument_list|)
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_enum_combo_box_set_stock_prefix:  * @combo_box:    a #GimpEnumComboBox  * @stock_prefix: a prefix to create icon stock ID from enum values  *  * Attempts to create stock icons for all items in the @combo_box. See  * gimp_enum_store_set_stock_prefix() to find out what to use as  * @stock_prefix.  *  * Since: 2.4  *  * Deprecated: GIMP 2.10  **/
end_comment

begin_function
name|void
DECL|function|gimp_enum_combo_box_set_stock_prefix (GimpEnumComboBox * combo_box,const gchar * stock_prefix)
name|gimp_enum_combo_box_set_stock_prefix
parameter_list|(
name|GimpEnumComboBox
modifier|*
name|combo_box
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_prefix
parameter_list|)
block|{
name|gimp_enum_combo_box_set_icon_prefix
argument_list|(
name|combo_box
argument_list|,
name|stock_prefix
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_enum_combo_box_set_icon_prefix:  * @combo_box:   a #GimpEnumComboBox  * @icon_prefix: a prefix to create icon names from enum values  *  * Attempts to create icons for all items in the @combo_box. See  * gimp_enum_store_set_icon_prefix() to find out what to use as  * @icon_prefix.  *  * Since: 2.10  **/
end_comment

begin_function
name|void
DECL|function|gimp_enum_combo_box_set_icon_prefix (GimpEnumComboBox * combo_box,const gchar * icon_prefix)
name|gimp_enum_combo_box_set_icon_prefix
parameter_list|(
name|GimpEnumComboBox
modifier|*
name|combo_box
parameter_list|,
specifier|const
name|gchar
modifier|*
name|icon_prefix
parameter_list|)
block|{
name|GtkTreeModel
modifier|*
name|model
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ENUM_COMBO_BOX
argument_list|(
name|combo_box
argument_list|)
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
name|gimp_enum_store_set_icon_prefix
argument_list|(
name|GIMP_ENUM_STORE
argument_list|(
name|model
argument_list|)
argument_list|,
name|icon_prefix
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

