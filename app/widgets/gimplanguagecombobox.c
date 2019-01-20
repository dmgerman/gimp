begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimplanguagecombobox.c  * Copyright (C) 2009  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/* GimpLanguageComboBox is a combo-box widget to select the user  * interface language.  */
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
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"gimplanguagecombobox.h"
end_include

begin_include
include|#
directive|include
file|"gimptranslationstore.h"
end_include

begin_struct
DECL|struct|_GimpLanguageComboBox
struct|struct
name|_GimpLanguageComboBox
block|{
DECL|member|parent_instance
name|GtkComboBox
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_macro
DECL|function|G_DEFINE_TYPE (GimpLanguageComboBox,gimp_language_combo_box,GTK_TYPE_COMBO_BOX)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpLanguageComboBox
argument_list|,
argument|gimp_language_combo_box
argument_list|,
argument|GTK_TYPE_COMBO_BOX
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_language_combo_box_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_language_combo_box_class_init
parameter_list|(
name|GimpLanguageComboBoxClass
modifier|*
name|klass
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_language_combo_box_init (GimpLanguageComboBox * combo)
name|gimp_language_combo_box_init
parameter_list|(
name|GimpLanguageComboBox
modifier|*
name|combo
parameter_list|)
block|{
name|GtkCellRenderer
modifier|*
name|renderer
decl_stmt|;
name|renderer
operator|=
name|gtk_cell_renderer_text_new
argument_list|()
expr_stmt|;
name|gtk_cell_layout_pack_start
argument_list|(
name|GTK_CELL_LAYOUT
argument_list|(
name|combo
argument_list|)
argument_list|,
name|renderer
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_cell_layout_set_attributes
argument_list|(
name|GTK_CELL_LAYOUT
argument_list|(
name|combo
argument_list|)
argument_list|,
name|renderer
argument_list|,
literal|"text"
argument_list|,
name|GIMP_LANGUAGE_STORE_LABEL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* See issues #2828 and #2642. */
name|gtk_combo_box_set_wrap_width
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|,
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_language_combo_box_new:  * @manual_l18n: get only the sublist of manual languages.  * @empty_label: the label for empty language code.  *  * Returns a combo box containing all GUI localization languages if  * @manual_l18n is #FALSE, or all manual localization languages  * otherwise. If @empty_label is not #NULL, an entry with this label  * will be created for the language code "", otherwise if @empty_label  * is #NULL and @manual_l18n is #FALSE, the entry will be "System  * Language" localized in itself (not in the GUI language).  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_language_combo_box_new (gboolean manual_l18n,const gchar * empty_label)
name|gimp_language_combo_box_new
parameter_list|(
name|gboolean
name|manual_l18n
parameter_list|,
specifier|const
name|gchar
modifier|*
name|empty_label
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|combo
decl_stmt|;
name|GtkListStore
modifier|*
name|store
decl_stmt|;
name|store
operator|=
name|gimp_translation_store_new
argument_list|(
name|manual_l18n
argument_list|,
name|empty_label
argument_list|)
expr_stmt|;
name|combo
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_LANGUAGE_COMBO_BOX
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
name|combo
return|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|gimp_language_combo_box_get_code (GimpLanguageComboBox * combo)
name|gimp_language_combo_box_get_code
parameter_list|(
name|GimpLanguageComboBox
modifier|*
name|combo
parameter_list|)
block|{
name|GtkTreeIter
name|iter
decl_stmt|;
name|gchar
modifier|*
name|code
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_LANGUAGE_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
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
condition|)
return|return
name|NULL
return|;
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
name|GIMP_LANGUAGE_STORE_CODE
argument_list|,
operator|&
name|code
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
return|return
name|code
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_language_combo_box_set_code (GimpLanguageComboBox * combo,const gchar * code)
name|gimp_language_combo_box_set_code
parameter_list|(
name|GimpLanguageComboBox
modifier|*
name|combo
parameter_list|,
specifier|const
name|gchar
modifier|*
name|code
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
name|GIMP_IS_LANGUAGE_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|code
operator|||
operator|!
name|strlen
argument_list|(
name|code
argument_list|)
condition|)
block|{
name|gtk_combo_box_set_active
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
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
if|if
condition|(
name|gimp_language_store_lookup
argument_list|(
name|GIMP_LANGUAGE_STORE
argument_list|(
name|model
argument_list|)
argument_list|,
name|code
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
name|combo
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

end_unit

