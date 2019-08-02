begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1999 Peter Mattis and Spencer Kimball  *  * gimpunitcombobox.c  * Copyright (C) 2004, 2008  Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
file|"gimpunitcombobox.h"
end_include

begin_include
include|#
directive|include
file|"gimpunitstore.h"
end_include

begin_comment
comment|/**  * SECTION: gimpunitcombobox  * @title: GimpUnitComboBox  * @short_description: A #GtkComboBox to select a #GimpUnit.  * @see_also: #GimpUnit, #GimpUnitStore  *  * #GimpUnitComboBox selects units stored in a #GimpUnitStore.  **/
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_unit_combo_box_style_updated
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_unit_combo_box_popup_shown
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpUnitComboBox,gimp_unit_combo_box,GTK_TYPE_COMBO_BOX)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpUnitComboBox
argument_list|,
argument|gimp_unit_combo_box
argument_list|,
argument|GTK_TYPE_COMBO_BOX
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_unit_combo_box_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_unit_combo_box_class_init
parameter_list|(
name|GimpUnitComboBoxClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkWidgetClass
modifier|*
name|widget_class
init|=
name|GTK_WIDGET_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|widget_class
operator|->
name|style_updated
operator|=
name|gimp_unit_combo_box_style_updated
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_unit_combo_box_init (GimpUnitComboBox * combo)
name|gimp_unit_combo_box_init
parameter_list|(
name|GimpUnitComboBox
modifier|*
name|combo
parameter_list|)
block|{
name|GtkCellLayout
modifier|*
name|layout
init|=
name|GTK_CELL_LAYOUT
argument_list|(
name|combo
argument_list|)
decl_stmt|;
name|GtkCellRenderer
modifier|*
name|cell
decl_stmt|;
name|cell
operator|=
name|gtk_cell_renderer_text_new
argument_list|()
expr_stmt|;
name|gtk_cell_layout_pack_start
argument_list|(
name|layout
argument_list|,
name|cell
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_cell_layout_set_attributes
argument_list|(
name|layout
argument_list|,
name|cell
argument_list|,
literal|"text"
argument_list|,
name|GIMP_UNIT_STORE_UNIT_LONG_FORMAT
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|combo
argument_list|,
literal|"notify::popup-shown"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_unit_combo_box_popup_shown
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_unit_combo_box_style_updated (GtkWidget * widget)
name|gimp_unit_combo_box_style_updated
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|GtkCellLayout
modifier|*
name|layout
decl_stmt|;
name|GtkCellRenderer
modifier|*
name|cell
decl_stmt|;
comment|/*  hackedehack ...  */
name|layout
operator|=
name|GTK_CELL_LAYOUT
argument_list|(
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|widget
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_cell_layout_clear
argument_list|(
name|layout
argument_list|)
expr_stmt|;
name|cell
operator|=
name|gtk_cell_renderer_text_new
argument_list|()
expr_stmt|;
name|gtk_cell_layout_pack_start
argument_list|(
name|layout
argument_list|,
name|cell
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_cell_layout_set_attributes
argument_list|(
name|layout
argument_list|,
name|cell
argument_list|,
literal|"text"
argument_list|,
name|GIMP_UNIT_STORE_UNIT_SHORT_FORMAT
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|style_updated
argument_list|(
name|widget
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_unit_combo_box_popup_shown (GtkWidget * widget,const GParamSpec * pspec)
name|gimp_unit_combo_box_popup_shown
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpUnitStore
modifier|*
name|store
decl_stmt|;
name|gboolean
name|shown
decl_stmt|;
name|g_object_get
argument_list|(
name|widget
argument_list|,
literal|"model"
argument_list|,
operator|&
name|store
argument_list|,
literal|"popup-shown"
argument_list|,
operator|&
name|shown
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|store
condition|)
block|{
if|if
condition|(
name|shown
condition|)
name|_gimp_unit_store_sync_units
argument_list|(
name|store
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|store
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_unit_combo_box_new:  *  * Returns: a new #GimpUnitComboBox.  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_unit_combo_box_new (void)
name|gimp_unit_combo_box_new
parameter_list|(
name|void
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|combo_box
decl_stmt|;
name|GimpUnitStore
modifier|*
name|store
decl_stmt|;
name|store
operator|=
name|gimp_unit_store_new
argument_list|(
literal|0
argument_list|)
expr_stmt|;
name|combo_box
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_UNIT_COMBO_BOX
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
comment|/**  * gimp_unit_combo_box_new_with_model:  * @model: a GimpUnitStore  *  * Returns: a new #GimpUnitComboBox.  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_unit_combo_box_new_with_model (GimpUnitStore * model)
name|gimp_unit_combo_box_new_with_model
parameter_list|(
name|GimpUnitStore
modifier|*
name|model
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_UNIT_COMBO_BOX
argument_list|,
literal|"model"
argument_list|,
name|model
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpUnit
DECL|function|gimp_unit_combo_box_get_active (GimpUnitComboBox * combo)
name|gimp_unit_combo_box_get_active
parameter_list|(
name|GimpUnitComboBox
modifier|*
name|combo
parameter_list|)
block|{
name|GtkTreeIter
name|iter
decl_stmt|;
name|gint
name|unit
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_UNIT_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_combo_box_get_active_iter
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
name|gtk_tree_model_get
argument_list|(
name|gtk_combo_box_get_model
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|,
name|GIMP_UNIT_STORE_UNIT
argument_list|,
operator|&
name|unit
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
return|return
operator|(
name|GimpUnit
operator|)
name|unit
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_unit_combo_box_set_active (GimpUnitComboBox * combo,GimpUnit unit)
name|gimp_unit_combo_box_set_active
parameter_list|(
name|GimpUnitComboBox
modifier|*
name|combo
parameter_list|,
name|GimpUnit
name|unit
parameter_list|)
block|{
name|GtkTreeModel
modifier|*
name|model
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|gboolean
name|iter_valid
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_UNIT_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|)
expr_stmt|;
name|model
operator|=
name|gtk_combo_box_get_model
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|)
expr_stmt|;
name|_gimp_unit_store_sync_units
argument_list|(
name|GIMP_UNIT_STORE
argument_list|(
name|model
argument_list|)
argument_list|)
expr_stmt|;
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
name|gint
name|iter_unit
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|,
name|GIMP_UNIT_STORE_UNIT
argument_list|,
operator|&
name|iter_unit
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|unit
operator|==
operator|(
name|GimpUnit
operator|)
name|iter_unit
condition|)
block|{
name|gtk_combo_box_set_active_iter
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
block|}
end_function

end_unit

