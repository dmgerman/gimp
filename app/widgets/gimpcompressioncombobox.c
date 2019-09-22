begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcompressioncombobox.c  * Copyright (C) 2004, 2008  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"stdlib.h"
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
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpcompressioncombobox.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2b15207a0103
block|{
DECL|enumerator|COLUMN_ID
name|COLUMN_ID
block|,
DECL|enumerator|COLUMN_LABEL
name|COLUMN_LABEL
block|,
DECL|enumerator|N_COLUMNS
name|N_COLUMNS
block|}
enum|;
end_enum

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_compression_combo_box_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_compression_combo_box_separator_func
parameter_list|(
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
DECL|function|G_DEFINE_TYPE (GimpCompressionComboBox,gimp_compression_combo_box,GIMP_TYPE_STRING_COMBO_BOX)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpCompressionComboBox
argument_list|,
argument|gimp_compression_combo_box
argument_list|,
argument|GIMP_TYPE_STRING_COMBO_BOX
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_compression_combo_box_parent_class
end_define

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
name|gimp_compression_combo_box_class_init
parameter_list|(
name|GimpCompressionComboBoxClass
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
name|gimp_compression_combo_box_constructed
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_compression_combo_box_init (GimpCompressionComboBox * combo_box)
name|gimp_compression_combo_box_init
parameter_list|(
name|GimpCompressionComboBox
modifier|*
name|combo_box
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_compression_combo_box_constructed (GObject * object)
name|gimp_compression_combo_box_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpCompressionComboBox
modifier|*
name|combo_box
init|=
name|GIMP_COMPRESSION_COMBO_BOX
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GtkCellLayout
modifier|*
name|layout
decl_stmt|;
name|GtkCellRenderer
modifier|*
name|cell
decl_stmt|;
name|GtkListStore
modifier|*
name|store
decl_stmt|;
name|GtkTreeIter
name|iter
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
name|store
operator|=
name|gtk_list_store_new
argument_list|(
name|N_COLUMNS
argument_list|,
name|G_TYPE_STRING
argument_list|,
comment|/* ID    */
name|G_TYPE_STRING
argument_list|)
expr_stmt|;
comment|/* LABEL */
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
name|gtk_combo_box_set_row_separator_func
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|combo_box
argument_list|)
argument_list|,
name|gimp_compression_combo_box_separator_func
argument_list|,
name|NULL
argument_list|,
name|NULL
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
name|COLUMN_ID
argument_list|,
literal|"none"
argument_list|,
name|COLUMN_LABEL
argument_list|,
name|C_
argument_list|(
literal|"compression"
argument_list|,
literal|"None"
argument_list|)
argument_list|,
operator|-
literal|1
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
name|COLUMN_ID
argument_list|,
name|NULL
argument_list|,
name|COLUMN_LABEL
argument_list|,
name|NULL
argument_list|,
operator|-
literal|1
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
name|COLUMN_ID
argument_list|,
literal|"fast"
argument_list|,
name|COLUMN_LABEL
argument_list|,
name|C_
argument_list|(
literal|"compression"
argument_list|,
literal|"Best performance"
argument_list|)
argument_list|,
operator|-
literal|1
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
name|COLUMN_ID
argument_list|,
literal|"balanced"
argument_list|,
name|COLUMN_LABEL
argument_list|,
name|C_
argument_list|(
literal|"compression"
argument_list|,
literal|"Balanced"
argument_list|)
argument_list|,
operator|-
literal|1
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
name|COLUMN_ID
argument_list|,
literal|"best"
argument_list|,
name|COLUMN_LABEL
argument_list|,
name|C_
argument_list|(
literal|"compression"
argument_list|,
literal|"Best compression"
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_combo_box_set_entry_text_column
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|combo_box
argument_list|)
argument_list|,
name|COLUMN_LABEL
argument_list|)
expr_stmt|;
name|layout
operator|=
name|GTK_CELL_LAYOUT
argument_list|(
name|combo_box
argument_list|)
expr_stmt|;
name|cell
operator|=
name|gtk_cell_renderer_text_new
argument_list|()
expr_stmt|;
name|gtk_cell_layout_clear
argument_list|(
name|layout
argument_list|)
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
name|COLUMN_LABEL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_compression_combo_box_separator_func (GtkTreeModel * model,GtkTreeIter * iter,gpointer data)
name|gimp_compression_combo_box_separator_func
parameter_list|(
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
name|gchar
modifier|*
name|value
decl_stmt|;
name|gboolean
name|result
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
name|iter
argument_list|,
name|COLUMN_ID
argument_list|,
operator|&
name|value
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|result
operator|=
operator|!
name|value
expr_stmt|;
name|g_free
argument_list|(
name|value
argument_list|)
expr_stmt|;
return|return
name|result
return|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_compression_combo_box_new (void)
name|gimp_compression_combo_box_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_COMPRESSION_COMBO_BOX
argument_list|,
literal|"has-entry"
argument_list|,
name|TRUE
argument_list|,
literal|"id-column"
argument_list|,
name|COLUMN_ID
argument_list|,
literal|"label-column"
argument_list|,
name|COLUMN_LABEL
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_compression_combo_box_set_compression (GimpCompressionComboBox * combo_box,const gchar * compression)
name|gimp_compression_combo_box_set_compression
parameter_list|(
name|GimpCompressionComboBox
modifier|*
name|combo_box
parameter_list|,
specifier|const
name|gchar
modifier|*
name|compression
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COMPRESSION_COMBO_BOX
argument_list|(
name|combo_box
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|compression
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_string_combo_box_set_active
argument_list|(
name|GIMP_STRING_COMBO_BOX
argument_list|(
name|combo_box
argument_list|)
argument_list|,
name|compression
argument_list|)
condition|)
block|{
name|GtkWidget
modifier|*
name|entry
decl_stmt|;
name|entry
operator|=
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|combo_box
argument_list|)
argument_list|)
expr_stmt|;
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
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
name|compression
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|gimp_compression_combo_box_get_compression (GimpCompressionComboBox * combo_box)
name|gimp_compression_combo_box_get_compression
parameter_list|(
name|GimpCompressionComboBox
modifier|*
name|combo_box
parameter_list|)
block|{
name|gchar
modifier|*
name|result
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_COMPRESSION_COMBO_BOX
argument_list|(
name|combo_box
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|result
operator|=
name|gimp_string_combo_box_get_active
argument_list|(
name|GIMP_STRING_COMBO_BOX
argument_list|(
name|combo_box
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|result
condition|)
block|{
name|GtkWidget
modifier|*
name|entry
decl_stmt|;
name|entry
operator|=
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|combo_box
argument_list|)
argument_list|)
expr_stmt|;
name|result
operator|=
name|g_strdup
argument_list|(
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
return|return
name|result
return|;
block|}
end_function

end_unit

