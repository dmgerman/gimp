begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpenumcombobox.c  * Copyright (C) 2004  Sven Neumann<sven@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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

begin_function
name|GType
DECL|function|gimp_enum_combo_box_get_type (void)
name|gimp_enum_combo_box_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|enum_combo_box_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|enum_combo_box_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|enum_combo_box_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpEnumComboBoxClass
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
name|GimpEnumComboBox
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
name|NULL
comment|/* instance_init  */
block|}
decl_stmt|;
name|enum_combo_box_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_INT_COMBO_BOX
argument_list|,
literal|"GimpEnumComboBox"
argument_list|,
operator|&
name|enum_combo_box_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|enum_combo_box_type
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_enum_combo_box_new:  * @enum_type: the #GType of an enum.  *  * Creates a #GtkComboBox readily filled with all enum values from a  * given @enum_type. The enum needs to be registered to the type  * system. It should also have %GimpEnumDesc descriptions registered  * that contain translatable value names. This is the case for the  * enums used in the GIMP PDB functions.  *  * This is just a convenience function. If you need more control over  * the enum values that appear in the combo_box, you can create your  * own #GimpEnumStore and use gimp_enum_combo_box_new_with_model().  *  * Return value: a new #GimpEnumComboBox.  *  * Since: GIMP 2.4  **/
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
comment|/**  * gimp_enum_combo_box_set_stock_prefix:  * @combo_box:    a #GimpEnumComboBox  * @stock_prefix: a prefix to create icon stock ID from enum values  *  * Attempts to create stock icons for all items in the @combo_box. See  * gimp_enum_store_set_icons() to find out what to use for  * @stock_prefix.  *  * Since: GIMP 2.4  **/
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
name|gimp_enum_store_set_stock_prefix
argument_list|(
name|GIMP_ENUM_STORE
argument_list|(
name|model
argument_list|)
argument_list|,
name|stock_prefix
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

