begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
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
file|"gimpwidgets-constructors.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|gboolean
name|gimp_paint_mode_menu_separator_func
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

begin_comment
comment|/*  public functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_enum_store_insert_value_after (GimpEnumStore * store,gint after,gint insert_value)
name|gimp_enum_store_insert_value_after
parameter_list|(
name|GimpEnumStore
modifier|*
name|store
parameter_list|,
name|gint
name|after
parameter_list|,
name|gint
name|insert_value
parameter_list|)
block|{
name|GtkTreeIter
name|iter
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ENUM_STORE
argument_list|(
name|store
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_int_store_lookup_by_value
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|store
argument_list|)
argument_list|,
name|after
argument_list|,
operator|&
name|iter
argument_list|)
condition|)
block|{
name|GEnumValue
modifier|*
name|enum_value
decl_stmt|;
name|enum_value
operator|=
name|g_enum_get_value
argument_list|(
name|store
operator|->
name|enum_class
argument_list|,
name|insert_value
argument_list|)
expr_stmt|;
if|if
condition|(
name|enum_value
condition|)
block|{
name|GtkTreeIter
name|value_iter
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|desc
decl_stmt|;
name|gtk_list_store_insert_after
argument_list|(
name|GTK_LIST_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
operator|&
name|value_iter
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
name|desc
operator|=
name|gimp_enum_value_get_desc
argument_list|(
name|store
operator|->
name|enum_class
argument_list|,
name|enum_value
argument_list|)
expr_stmt|;
name|gtk_list_store_set
argument_list|(
name|GTK_LIST_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
operator|&
name|value_iter
argument_list|,
name|GIMP_INT_STORE_VALUE
argument_list|,
name|enum_value
operator|->
name|value
argument_list|,
name|GIMP_INT_STORE_LABEL
argument_list|,
name|desc
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_int_store_insert_separator_after (GimpIntStore * store,gint after,gint separator_value)
name|gimp_int_store_insert_separator_after
parameter_list|(
name|GimpIntStore
modifier|*
name|store
parameter_list|,
name|gint
name|after
parameter_list|,
name|gint
name|separator_value
parameter_list|)
block|{
name|GtkTreeIter
name|iter
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_INT_STORE
argument_list|(
name|store
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_int_store_lookup_by_value
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|store
argument_list|)
argument_list|,
name|after
argument_list|,
operator|&
name|iter
argument_list|)
condition|)
block|{
name|GtkTreeIter
name|sep_iter
decl_stmt|;
name|gtk_list_store_insert_after
argument_list|(
name|GTK_LIST_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
operator|&
name|sep_iter
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
name|gtk_list_store_set
argument_list|(
name|GTK_LIST_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
operator|&
name|sep_iter
argument_list|,
name|GIMP_INT_STORE_VALUE
argument_list|,
name|separator_value
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_paint_mode_menu_new (gboolean with_behind_mode,gboolean with_replace_modes)
name|gimp_paint_mode_menu_new
parameter_list|(
name|gboolean
name|with_behind_mode
parameter_list|,
name|gboolean
name|with_replace_modes
parameter_list|)
block|{
name|GtkListStore
modifier|*
name|store
decl_stmt|;
name|GtkWidget
modifier|*
name|combo
decl_stmt|;
name|store
operator|=
name|gimp_enum_store_new_with_values
argument_list|(
name|GIMP_TYPE_LAYER_MODE
argument_list|,
literal|45
argument_list|,
name|GIMP_LAYER_MODE_NORMAL
argument_list|,
name|GIMP_LAYER_MODE_NORMAL_NON_LINEAR
argument_list|,
name|GIMP_LAYER_MODE_DISSOLVE
argument_list|,
name|GIMP_LAYER_MODE_LIGHTEN_ONLY
argument_list|,
name|GIMP_LAYER_MODE_LIGHTEN_ONLY_LEGACY
argument_list|,
name|GIMP_LAYER_MODE_SCREEN
argument_list|,
name|GIMP_LAYER_MODE_SCREEN_LEGACY
argument_list|,
name|GIMP_LAYER_MODE_DODGE
argument_list|,
name|GIMP_LAYER_MODE_DODGE_LEGACY
argument_list|,
name|GIMP_LAYER_MODE_ADDITION
argument_list|,
name|GIMP_LAYER_MODE_ADDITION_LEGACY
argument_list|,
name|GIMP_LAYER_MODE_DARKEN_ONLY
argument_list|,
name|GIMP_LAYER_MODE_DARKEN_ONLY_LEGACY
argument_list|,
name|GIMP_LAYER_MODE_MULTIPLY
argument_list|,
name|GIMP_LAYER_MODE_MULTIPLY_LINEAR
argument_list|,
name|GIMP_LAYER_MODE_MULTIPLY_LEGACY
argument_list|,
name|GIMP_LAYER_MODE_BURN
argument_list|,
name|GIMP_LAYER_MODE_BURN_LEGACY
argument_list|,
name|GIMP_LAYER_MODE_OVERLAY
argument_list|,
name|GIMP_LAYER_MODE_SOFTLIGHT
argument_list|,
name|GIMP_LAYER_MODE_SOFTLIGHT_LEGACY
argument_list|,
name|GIMP_LAYER_MODE_HARDLIGHT
argument_list|,
name|GIMP_LAYER_MODE_HARDLIGHT_LEGACY
argument_list|,
name|GIMP_LAYER_MODE_DIFFERENCE
argument_list|,
name|GIMP_LAYER_MODE_DIFFERENCE_LEGACY
argument_list|,
name|GIMP_LAYER_MODE_SUBTRACT
argument_list|,
name|GIMP_LAYER_MODE_SUBTRACT_LEGACY
argument_list|,
name|GIMP_LAYER_MODE_GRAIN_EXTRACT
argument_list|,
name|GIMP_LAYER_MODE_GRAIN_EXTRACT_LEGACY
argument_list|,
name|GIMP_LAYER_MODE_GRAIN_MERGE
argument_list|,
name|GIMP_LAYER_MODE_GRAIN_MERGE_LEGACY
argument_list|,
name|GIMP_LAYER_MODE_DIVIDE
argument_list|,
name|GIMP_LAYER_MODE_DIVIDE_LEGACY
argument_list|,
name|GIMP_LAYER_MODE_HSV_HUE
argument_list|,
name|GIMP_LAYER_MODE_HSV_SATURATION
argument_list|,
name|GIMP_LAYER_MODE_HSV_COLOR
argument_list|,
name|GIMP_LAYER_MODE_HSV_VALUE
argument_list|,
name|GIMP_LAYER_MODE_HSV_HUE_LEGACY
argument_list|,
name|GIMP_LAYER_MODE_HSV_SATURATION_LEGACY
argument_list|,
name|GIMP_LAYER_MODE_HSV_COLOR_LEGACY
argument_list|,
name|GIMP_LAYER_MODE_HSV_VALUE_LEGACY
argument_list|,
name|GIMP_LAYER_MODE_LCH_HUE
argument_list|,
name|GIMP_LAYER_MODE_LCH_CHROMA
argument_list|,
name|GIMP_LAYER_MODE_LCH_COLOR
argument_list|,
name|GIMP_LAYER_MODE_LCH_LIGHTNESS
argument_list|)
expr_stmt|;
name|gimp_int_store_insert_separator_after
argument_list|(
name|GIMP_INT_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
name|GIMP_LAYER_MODE_DISSOLVE
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_int_store_insert_separator_after
argument_list|(
name|GIMP_INT_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
name|GIMP_LAYER_MODE_ADDITION_LEGACY
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_int_store_insert_separator_after
argument_list|(
name|GIMP_INT_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
name|GIMP_LAYER_MODE_BURN_LEGACY
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_int_store_insert_separator_after
argument_list|(
name|GIMP_INT_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
name|GIMP_LAYER_MODE_HARDLIGHT_LEGACY
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_int_store_insert_separator_after
argument_list|(
name|GIMP_INT_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
name|GIMP_LAYER_MODE_DIVIDE_LEGACY
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_int_store_insert_separator_after
argument_list|(
name|GIMP_INT_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
name|GIMP_LAYER_MODE_HSV_VALUE_LEGACY
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|with_behind_mode
condition|)
block|{
name|gimp_enum_store_insert_value_after
argument_list|(
name|GIMP_ENUM_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
name|GIMP_LAYER_MODE_DISSOLVE
argument_list|,
name|GIMP_LAYER_MODE_BEHIND
argument_list|)
expr_stmt|;
name|gimp_enum_store_insert_value_after
argument_list|(
name|GIMP_ENUM_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
name|GIMP_LAYER_MODE_BEHIND
argument_list|,
name|GIMP_LAYER_MODE_COLOR_ERASE
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|with_replace_modes
condition|)
block|{
name|gimp_enum_store_insert_value_after
argument_list|(
name|GIMP_ENUM_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
name|GIMP_LAYER_MODE_NORMAL_NON_LINEAR
argument_list|,
name|GIMP_LAYER_MODE_REPLACE
argument_list|)
expr_stmt|;
name|gimp_enum_store_insert_value_after
argument_list|(
name|GIMP_ENUM_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
name|GIMP_LAYER_MODE_COLOR_ERASE
argument_list|,
name|GIMP_LAYER_MODE_ERASE
argument_list|)
expr_stmt|;
name|gimp_enum_store_insert_value_after
argument_list|(
name|GIMP_ENUM_STORE
argument_list|(
name|store
argument_list|)
argument_list|,
name|GIMP_LAYER_MODE_ERASE
argument_list|,
name|GIMP_LAYER_MODE_ANTI_ERASE
argument_list|)
expr_stmt|;
block|}
name|combo
operator|=
name|gimp_enum_combo_box_new_with_model
argument_list|(
name|GIMP_ENUM_STORE
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
name|combo
argument_list|)
argument_list|,
name|gimp_paint_mode_menu_separator_func
argument_list|,
name|GINT_TO_POINTER
argument_list|(
operator|-
literal|1
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|combo
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_icon_button_new (const gchar * icon_name,const gchar * label)
name|gimp_icon_button_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|icon_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|label
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|image
decl_stmt|;
name|button
operator|=
name|gtk_button_new
argument_list|()
expr_stmt|;
if|if
condition|(
name|label
condition|)
block|{
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|lab
decl_stmt|;
name|hbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|button
argument_list|)
argument_list|,
name|hbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|image
operator|=
name|gtk_image_new_from_icon_name
argument_list|(
name|icon_name
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|image
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|lab
operator|=
name|gtk_label_new_with_mnemonic
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|gtk_label_set_mnemonic_widget
argument_list|(
name|GTK_LABEL
argument_list|(
name|lab
argument_list|)
argument_list|,
name|button
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|lab
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|lab
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|image
operator|=
name|gtk_image_new_from_icon_name
argument_list|(
name|icon_name
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|button
argument_list|)
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
return|return
name|button
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_color_profile_label_new (GimpColorProfile * profile)
name|gimp_color_profile_label_new
parameter_list|(
name|GimpColorProfile
modifier|*
name|profile
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|expander
decl_stmt|;
name|GtkWidget
modifier|*
name|view
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|label
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|profile
operator|==
name|NULL
operator|||
name|GIMP_IS_COLOR_PROFILE
argument_list|(
name|profile
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|profile
condition|)
name|label
operator|=
name|gimp_color_profile_get_label
argument_list|(
name|profile
argument_list|)
expr_stmt|;
else|else
name|label
operator|=
name|C_
argument_list|(
literal|"profile"
argument_list|,
literal|"None"
argument_list|)
expr_stmt|;
name|expander
operator|=
name|gtk_expander_new
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|view
operator|=
name|gimp_color_profile_view_new
argument_list|()
expr_stmt|;
if|if
condition|(
name|profile
condition|)
name|gimp_color_profile_view_set_profile
argument_list|(
name|GIMP_COLOR_PROFILE_VIEW
argument_list|(
name|view
argument_list|)
argument_list|,
name|profile
argument_list|)
expr_stmt|;
else|else
name|gimp_color_profile_view_set_error
argument_list|(
name|GIMP_COLOR_PROFILE_VIEW
argument_list|(
name|view
argument_list|)
argument_list|,
name|C_
argument_list|(
literal|"profile"
argument_list|,
literal|"None"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|expander
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|view
argument_list|)
expr_stmt|;
return|return
name|expander
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|gimp_paint_mode_menu_separator_func (GtkTreeModel * model,GtkTreeIter * iter,gpointer data)
name|gimp_paint_mode_menu_separator_func
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
name|gint
name|value
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
return|return
name|value
operator|==
name|GPOINTER_TO_INT
argument_list|(
name|data
argument_list|)
return|;
block|}
end_function

end_unit

