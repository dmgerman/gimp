begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpcolorprofilecombobox.c  * Copyright (C) 2007  Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
file|"gimpwidgetstypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorprofilechooserdialog.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorprofilecombobox.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorprofilestore.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorprofilestore-private.h"
end_include

begin_comment
comment|/**  * SECTION: gimpcolorprofilecombobox  * @title: GimpColorProfileComboBox  * @short_description: A combo box for selecting color profiles.  *  * A combo box for selecting color profiles.  **/
end_comment

begin_enum
enum|enum
DECL|enum|__anon2ba7a7ec0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_DIALOG
name|PROP_DIALOG
block|,
DECL|enumerator|PROP_MODEL
name|PROP_MODEL
block|}
enum|;
end_enum

begin_struct
DECL|struct|_GimpColorProfileComboBoxPrivate
struct|struct
name|_GimpColorProfileComboBoxPrivate
block|{
DECL|member|dialog
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
DECL|member|last_path
name|GtkTreePath
modifier|*
name|last_path
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GET_PRIVATE (obj)
define|#
directive|define
name|GET_PRIVATE
parameter_list|(
name|obj
parameter_list|)
value|(((GimpColorProfileComboBox *) (obj))->priv)
end_define

begin_function_decl
specifier|static
name|void
name|gimp_color_profile_combo_box_finalize
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
name|gimp_color_profile_combo_box_set_property
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
name|gimp_color_profile_combo_box_get_property
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
name|gimp_color_profile_combo_box_changed
parameter_list|(
name|GtkComboBox
modifier|*
name|combo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_color_profile_row_separator_func
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

begin_function_decl
specifier|static
name|void
name|gimp_color_profile_combo_dialog_response
parameter_list|(
name|GimpColorProfileChooserDialog
modifier|*
name|dialog
parameter_list|,
name|gint
name|response
parameter_list|,
name|GimpColorProfileComboBox
modifier|*
name|combo
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_PRIVATE (GimpColorProfileComboBox,gimp_color_profile_combo_box,GTK_TYPE_COMBO_BOX)
name|G_DEFINE_TYPE_WITH_PRIVATE
argument_list|(
argument|GimpColorProfileComboBox
argument_list|,
argument|gimp_color_profile_combo_box
argument_list|,
argument|GTK_TYPE_COMBO_BOX
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_color_profile_combo_box_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_color_profile_combo_box_class_init
parameter_list|(
name|GimpColorProfileComboBoxClass
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
name|GtkComboBoxClass
modifier|*
name|combo_class
init|=
name|GTK_COMBO_BOX_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_color_profile_combo_box_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_color_profile_combo_box_get_property
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_color_profile_combo_box_finalize
expr_stmt|;
name|combo_class
operator|->
name|changed
operator|=
name|gimp_color_profile_combo_box_changed
expr_stmt|;
comment|/**    * GimpColorProfileComboBox:dialog:    *    * #GtkDialog to present when the user selects the    * "Select color profile from disk..." item.    *    * Since: 2.4    */
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_DIALOG
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"dialog"
argument_list|,
literal|"Dialog"
argument_list|,
literal|"The dialog to present when selecting profiles from disk"
argument_list|,
name|GTK_TYPE_DIALOG
argument_list|,
name|G_PARAM_CONSTRUCT_ONLY
operator||
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
comment|/**    * GimpColorProfileComboBox:model:    *    * Overrides the "model" property of the #GtkComboBox class.    * #GimpColorProfileComboBox requires the model to be a    * #GimpColorProfileStore.    *    * Since: 2.4    */
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
literal|"The profile store used for this combo box"
argument_list|,
name|GIMP_TYPE_COLOR_PROFILE_STORE
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
DECL|function|gimp_color_profile_combo_box_init (GimpColorProfileComboBox * combo_box)
name|gimp_color_profile_combo_box_init
parameter_list|(
name|GimpColorProfileComboBox
modifier|*
name|combo_box
parameter_list|)
block|{
name|GtkCellRenderer
modifier|*
name|cell
decl_stmt|;
name|combo_box
operator|->
name|priv
operator|=
name|gimp_color_profile_combo_box_get_instance_private
argument_list|(
name|combo_box
argument_list|)
expr_stmt|;
name|cell
operator|=
name|gtk_cell_renderer_text_new
argument_list|()
expr_stmt|;
name|g_object_set
argument_list|(
name|cell
argument_list|,
literal|"width-chars"
argument_list|,
literal|42
argument_list|,
literal|"ellipsize"
argument_list|,
name|PANGO_ELLIPSIZE_END
argument_list|,
name|NULL
argument_list|)
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
name|GIMP_COLOR_PROFILE_STORE_LABEL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_combo_box_set_row_separator_func
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|combo_box
argument_list|)
argument_list|,
name|gimp_color_profile_row_separator_func
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_profile_combo_box_finalize (GObject * object)
name|gimp_color_profile_combo_box_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpColorProfileComboBoxPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|private
operator|->
name|dialog
condition|)
block|{
if|if
condition|(
name|GIMP_IS_COLOR_PROFILE_CHOOSER_DIALOG
argument_list|(
name|private
operator|->
name|dialog
argument_list|)
condition|)
name|gtk_widget_destroy
argument_list|(
name|private
operator|->
name|dialog
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|private
operator|->
name|dialog
argument_list|)
expr_stmt|;
name|private
operator|->
name|dialog
operator|=
name|NULL
expr_stmt|;
block|}
name|g_clear_pointer
argument_list|(
operator|&
name|private
operator|->
name|last_path
argument_list|,
name|gtk_tree_path_free
argument_list|)
expr_stmt|;
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
DECL|function|gimp_color_profile_combo_box_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_color_profile_combo_box_set_property
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
name|GimpColorProfileComboBoxPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
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
name|PROP_DIALOG
case|:
name|g_return_if_fail
argument_list|(
name|private
operator|->
name|dialog
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|private
operator|->
name|dialog
operator|=
name|g_value_dup_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_COLOR_PROFILE_CHOOSER_DIALOG
argument_list|(
name|private
operator|->
name|dialog
argument_list|)
condition|)
name|g_signal_connect
argument_list|(
name|private
operator|->
name|dialog
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_color_profile_combo_dialog_response
argument_list|)
argument_list|,
name|object
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MODEL
case|:
name|gtk_combo_box_set_model
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|object
argument_list|)
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
DECL|function|gimp_color_profile_combo_box_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_color_profile_combo_box_get_property
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
name|GimpColorProfileComboBoxPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
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
name|PROP_DIALOG
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|dialog
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_MODEL
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|gtk_combo_box_get_model
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|object
argument_list|)
argument_list|)
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
DECL|function|gimp_color_profile_combo_box_changed (GtkComboBox * combo)
name|gimp_color_profile_combo_box_changed
parameter_list|(
name|GtkComboBox
modifier|*
name|combo
parameter_list|)
block|{
name|GimpColorProfileComboBoxPrivate
modifier|*
name|priv
init|=
name|GET_PRIVATE
argument_list|(
name|combo
argument_list|)
decl_stmt|;
name|GtkTreeModel
modifier|*
name|model
init|=
name|gtk_combo_box_get_model
argument_list|(
name|combo
argument_list|)
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|gint
name|type
decl_stmt|;
if|if
condition|(
operator|!
name|gtk_combo_box_get_active_iter
argument_list|(
name|combo
argument_list|,
operator|&
name|iter
argument_list|)
condition|)
return|return;
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|,
name|GIMP_COLOR_PROFILE_STORE_ITEM_TYPE
argument_list|,
operator|&
name|type
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|type
condition|)
block|{
case|case
name|GIMP_COLOR_PROFILE_STORE_ITEM_DIALOG
case|:
block|{
name|GtkWidget
modifier|*
name|parent
init|=
name|gtk_widget_get_toplevel
argument_list|(
name|GTK_WIDGET
argument_list|(
name|combo
argument_list|)
argument_list|)
decl_stmt|;
if|if
condition|(
name|GTK_IS_WINDOW
argument_list|(
name|parent
argument_list|)
condition|)
name|gtk_window_set_transient_for
argument_list|(
name|GTK_WINDOW
argument_list|(
name|priv
operator|->
name|dialog
argument_list|)
argument_list|,
name|GTK_WINDOW
argument_list|(
name|parent
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|priv
operator|->
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|priv
operator|->
name|last_path
operator|&&
name|gtk_tree_model_get_iter
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|,
name|priv
operator|->
name|last_path
argument_list|)
condition|)
block|{
name|gtk_combo_box_set_active_iter
argument_list|(
name|combo
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
block|}
block|}
break|break;
case|case
name|GIMP_COLOR_PROFILE_STORE_ITEM_FILE
case|:
if|if
condition|(
name|priv
operator|->
name|last_path
condition|)
name|gtk_tree_path_free
argument_list|(
name|priv
operator|->
name|last_path
argument_list|)
expr_stmt|;
name|priv
operator|->
name|last_path
operator|=
name|gtk_tree_model_get_path
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
name|_gimp_color_profile_store_history_reorder
argument_list|(
name|GIMP_COLOR_PROFILE_STORE
argument_list|(
name|model
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_color_profile_combo_box_new:  * @dialog:  a #GtkDialog to present when the user selects the  *           "Select color profile from disk..." item  * @history: filename of the profilerc (or %NULL for no history)  *  * Create a combo-box widget for selecting color profiles. The combo-box  * is populated from the file specified as @history. This filename is  * typically created using the following code snippet:  *<informalexample><programlisting>  *  gchar *history = gimp_personal_rc_file ("profilerc");  *</programlisting></informalexample>  *  * The recommended @dialog type to use is a #GimpColorProfileChooserDialog.  * If a #GimpColorProfileChooserDialog is passed, #GimpColorProfileComboBox  * will take complete control over the dialog, which means connecting  * a GtkDialog::response() callback by itself, and take care of destroying  * the dialog when the combo box is destroyed.  *  * If another type of @dialog is passed, this has to be implemented  * separately.  *  * See also gimp_color_profile_combo_box_new_with_model().  *  * Return value: a new #GimpColorProfileComboBox.  *  * Since: 2.4  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_color_profile_combo_box_new (GtkWidget * dialog,const gchar * history)
name|gimp_color_profile_combo_box_new
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
specifier|const
name|gchar
modifier|*
name|history
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
name|g_return_val_if_fail
argument_list|(
name|GTK_IS_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|store
operator|=
name|gimp_color_profile_store_new
argument_list|(
name|history
argument_list|)
expr_stmt|;
name|combo
operator|=
name|gimp_color_profile_combo_box_new_with_model
argument_list|(
name|dialog
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
return|return
name|combo
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_color_profile_combo_box_new_with_model:  * @dialog: a #GtkDialog to present when the user selects the  *          "Select color profile from disk..." item  * @model:  a #GimpColorProfileStore object  *  * This constructor is useful when you want to create several  * combo-boxes for profile selection that all share the same  * #GimpColorProfileStore. This is for example done in the  * GIMP Preferences dialog.  *  * See also gimp_color_profile_combo_box_new().  *  * Return value: a new #GimpColorProfileComboBox.  *  * Since: 2.4  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_color_profile_combo_box_new_with_model (GtkWidget * dialog,GtkTreeModel * model)
name|gimp_color_profile_combo_box_new_with_model
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|GtkTreeModel
modifier|*
name|model
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GTK_IS_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_COLOR_PROFILE_STORE
argument_list|(
name|model
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_COLOR_PROFILE_COMBO_BOX
argument_list|,
literal|"dialog"
argument_list|,
name|dialog
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

begin_comment
comment|/**  * gimp_color_profile_combo_box_add_file:  * @combo: a #GimpColorProfileComboBox  * @file:  file of the profile to add (or %NULL)  * @label: label to use for the profile  *         (may only be %NULL if @file is %NULL)  *  * This function delegates to the underlying  * #GimpColorProfileStore. Please refer to the documentation of  * gimp_color_profile_store_add_file() for details.  *  * Since: 2.10  **/
end_comment

begin_function
name|void
DECL|function|gimp_color_profile_combo_box_add_file (GimpColorProfileComboBox * combo,GFile * file,const gchar * label)
name|gimp_color_profile_combo_box_add_file
parameter_list|(
name|GimpColorProfileComboBox
modifier|*
name|combo
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|,
specifier|const
name|gchar
modifier|*
name|label
parameter_list|)
block|{
name|GtkTreeModel
modifier|*
name|model
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_PROFILE_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|label
operator|!=
name|NULL
operator|||
name|file
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|file
operator|==
name|NULL
operator|||
name|G_IS_FILE
argument_list|(
name|file
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
name|gimp_color_profile_store_add_file
argument_list|(
name|GIMP_COLOR_PROFILE_STORE
argument_list|(
name|model
argument_list|)
argument_list|,
name|file
argument_list|,
name|label
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_color_profile_combo_box_set_active_file:  * @combo: a #GimpColorProfileComboBox  * @file:  file of the profile to select  * @label: label to use when adding a new entry (can be %NULL)  *  * Selects a color profile from the @combo and makes it the active  * item.  If the profile is not listed in the @combo, then it is added  * with the given @label (or @file in case that @label is %NULL).  *  * Since: 2.10  **/
end_comment

begin_function
name|void
DECL|function|gimp_color_profile_combo_box_set_active_file (GimpColorProfileComboBox * combo,GFile * file,const gchar * label)
name|gimp_color_profile_combo_box_set_active_file
parameter_list|(
name|GimpColorProfileComboBox
modifier|*
name|combo
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|,
specifier|const
name|gchar
modifier|*
name|label
parameter_list|)
block|{
name|GimpColorProfile
modifier|*
name|profile
init|=
name|NULL
decl_stmt|;
name|GtkTreeModel
modifier|*
name|model
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_PROFILE_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|file
operator|==
name|NULL
operator|||
name|G_IS_FILE
argument_list|(
name|file
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
if|if
condition|(
name|file
operator|&&
operator|!
operator|(
name|label
operator|&&
operator|*
name|label
operator|)
condition|)
block|{
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|profile
operator|=
name|gimp_color_profile_new_from_file
argument_list|(
name|file
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|profile
condition|)
block|{
name|g_message
argument_list|(
literal|"%s"
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|label
operator|=
name|gimp_color_profile_get_label
argument_list|(
name|profile
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|_gimp_color_profile_store_history_add
argument_list|(
name|GIMP_COLOR_PROFILE_STORE
argument_list|(
name|model
argument_list|)
argument_list|,
name|file
argument_list|,
name|label
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
block|}
if|if
condition|(
name|profile
condition|)
name|g_object_unref
argument_list|(
name|profile
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_color_profile_combo_box_get_active_file:  * @combo: a #GimpColorProfileComboBox  *  * Return value: (transfer none): The file of the currently selected  *               color profile, release using g_object_unref() when it  *               is not any longer needed.  *  * Since: 2.10  **/
end_comment

begin_function
name|GFile
modifier|*
DECL|function|gimp_color_profile_combo_box_get_active_file (GimpColorProfileComboBox * combo)
name|gimp_color_profile_combo_box_get_active_file
parameter_list|(
name|GimpColorProfileComboBox
modifier|*
name|combo
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
name|GIMP_IS_COLOR_PROFILE_COMBO_BOX
argument_list|(
name|combo
argument_list|)
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
name|combo
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
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
block|{
name|GFile
modifier|*
name|file
decl_stmt|;
name|gint
name|type
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|,
name|GIMP_COLOR_PROFILE_STORE_ITEM_TYPE
argument_list|,
operator|&
name|type
argument_list|,
name|GIMP_COLOR_PROFILE_STORE_FILE
argument_list|,
operator|&
name|file
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|type
operator|==
name|GIMP_COLOR_PROFILE_STORE_ITEM_FILE
condition|)
return|return
name|file
return|;
if|if
condition|(
name|file
condition|)
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_color_profile_row_separator_func (GtkTreeModel * model,GtkTreeIter * iter,gpointer data)
name|gimp_color_profile_row_separator_func
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
name|type
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
name|iter
argument_list|,
name|GIMP_COLOR_PROFILE_STORE_ITEM_TYPE
argument_list|,
operator|&
name|type
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|type
condition|)
block|{
case|case
name|GIMP_COLOR_PROFILE_STORE_ITEM_SEPARATOR_TOP
case|:
case|case
name|GIMP_COLOR_PROFILE_STORE_ITEM_SEPARATOR_BOTTOM
case|:
return|return
name|TRUE
return|;
default|default:
return|return
name|FALSE
return|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_profile_combo_dialog_response (GimpColorProfileChooserDialog * dialog,gint response,GimpColorProfileComboBox * combo)
name|gimp_color_profile_combo_dialog_response
parameter_list|(
name|GimpColorProfileChooserDialog
modifier|*
name|dialog
parameter_list|,
name|gint
name|response
parameter_list|,
name|GimpColorProfileComboBox
modifier|*
name|combo
parameter_list|)
block|{
if|if
condition|(
name|response
operator|==
name|GTK_RESPONSE_ACCEPT
condition|)
block|{
name|GFile
modifier|*
name|file
decl_stmt|;
name|file
operator|=
name|gtk_file_chooser_get_file
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|file
condition|)
block|{
name|gimp_color_profile_combo_box_set_active_file
argument_list|(
name|combo
argument_list|,
name|file
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
block|}
block|}
name|gtk_widget_hide
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

