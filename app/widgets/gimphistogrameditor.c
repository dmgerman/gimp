begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"base/gimphistogram.h"
end_include

begin_include
include|#
directive|include
file|"base/pixel-region.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpbaseconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpdocked.h"
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
file|"gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"gimphistogrambox.h"
end_include

begin_include
include|#
directive|include
file|"gimphistogrameditor.h"
end_include

begin_include
include|#
directive|include
file|"gimphistogramview.h"
end_include

begin_include
include|#
directive|include
file|"gimppropwidgets.h"
end_include

begin_include
include|#
directive|include
file|"gimpsessioninfo.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_histogram_editor_class_init
parameter_list|(
name|GimpHistogramEditorClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_histogram_editor_init
parameter_list|(
name|GimpHistogramEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_histogram_editor_docked_iface_init
parameter_list|(
name|GimpDockedInterface
modifier|*
name|docked_iface
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_histogram_editor_set_aux_info
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|GList
modifier|*
name|aux_info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GList
modifier|*
name|gimp_histogram_editor_get_aux_info
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_histogram_editor_set_image
parameter_list|(
name|GimpImageEditor
modifier|*
name|editor
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_histogram_editor_layer_changed
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpHistogramEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_histogram_editor_update
parameter_list|(
name|GimpHistogramEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_histogram_editor_idle_update
parameter_list|(
name|GimpHistogramEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_histogram_editor_item_visible
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
name|gimp_histogram_editor_menu_update
parameter_list|(
name|GimpHistogramEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_histogram_editor_info_update
parameter_list|(
name|GimpHistogramEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpImageEditorClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parent_docked_iface
specifier|static
name|GimpDockedInterface
modifier|*
name|parent_docked_iface
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_histogram_editor_get_type (void)
name|gimp_histogram_editor_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|editor_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|editor_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|editor_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpHistogramEditorClass
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|NULL
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_histogram_editor_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpHistogramEditor
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_histogram_editor_init
block|,       }
decl_stmt|;
specifier|static
specifier|const
name|GInterfaceInfo
name|docked_iface_info
init|=
block|{
operator|(
name|GInterfaceInitFunc
operator|)
name|gimp_histogram_editor_docked_iface_init
block|,
name|NULL
block|,
comment|/* iface_finalize */
name|NULL
comment|/* iface_data     */
block|}
decl_stmt|;
name|editor_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_IMAGE_EDITOR
argument_list|,
literal|"GimpHistogramEditor"
argument_list|,
operator|&
name|editor_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_type_add_interface_static
argument_list|(
name|editor_type
argument_list|,
name|GIMP_TYPE_DOCKED
argument_list|,
operator|&
name|docked_iface_info
argument_list|)
expr_stmt|;
block|}
return|return
name|editor_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_histogram_editor_class_init (GimpHistogramEditorClass * klass)
name|gimp_histogram_editor_class_init
parameter_list|(
name|GimpHistogramEditorClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpImageEditorClass
modifier|*
name|image_editor_class
init|=
name|GIMP_IMAGE_EDITOR_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|image_editor_class
operator|->
name|set_image
operator|=
name|gimp_histogram_editor_set_image
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_histogram_editor_init (GimpHistogramEditor * editor)
name|gimp_histogram_editor_init
parameter_list|(
name|GimpHistogramEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpHistogramView
modifier|*
name|view
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|menu
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|gint
name|i
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|gimp_histogram_editor_labels
index|[]
init|=
block|{
name|N_
argument_list|(
literal|"Mean:"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Std Dev:"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Median:"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Pixels:"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Count:"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Percentile:"
argument_list|)
block|}
decl_stmt|;
name|editor
operator|->
name|drawable
operator|=
name|NULL
expr_stmt|;
name|editor
operator|->
name|histogram
operator|=
name|NULL
expr_stmt|;
name|editor
operator|->
name|idle_id
operator|=
literal|0
expr_stmt|;
name|editor
operator|->
name|box
operator|=
name|gimp_histogram_box_new
argument_list|()
expr_stmt|;
name|editor
operator|->
name|name
operator|=
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"(None)"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gimp_label_set_attributes
argument_list|(
name|GTK_LABEL
argument_list|(
name|editor
operator|->
name|name
argument_list|)
argument_list|,
name|PANGO_ATTR_STYLE
argument_list|,
name|PANGO_STYLE_ITALIC
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|editor
argument_list|)
argument_list|,
name|label
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
name|label
argument_list|)
expr_stmt|;
name|view
operator|=
name|GIMP_HISTOGRAM_BOX
argument_list|(
name|editor
operator|->
name|box
argument_list|)
operator|->
name|view
expr_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|editor
argument_list|)
argument_list|,
name|hbox
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
name|hbox
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Channel:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|label
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
name|label
argument_list|)
expr_stmt|;
name|editor
operator|->
name|menu
operator|=
name|menu
operator|=
name|gimp_prop_enum_combo_box_new
argument_list|(
name|G_OBJECT
argument_list|(
name|view
argument_list|)
argument_list|,
literal|"histogram-channel"
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_enum_combo_box_set_stock_prefix
argument_list|(
name|GIMP_ENUM_COMBO_BOX
argument_list|(
name|menu
argument_list|)
argument_list|,
literal|"gimp-channel"
argument_list|)
expr_stmt|;
name|gimp_enum_combo_box_set_visible
argument_list|(
name|GIMP_ENUM_COMBO_BOX
argument_list|(
name|editor
operator|->
name|menu
argument_list|)
argument_list|,
name|gimp_histogram_editor_item_visible
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|gimp_int_combo_box_set_active
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|editor
operator|->
name|menu
argument_list|)
argument_list|,
name|view
operator|->
name|channel
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|menu
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
name|menu
argument_list|)
expr_stmt|;
name|menu
operator|=
name|gimp_prop_enum_stock_box_new
argument_list|(
name|G_OBJECT
argument_list|(
name|view
argument_list|)
argument_list|,
literal|"histogram-scale"
argument_list|,
literal|"gimp-histogram"
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|menu
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
name|menu
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|editor
argument_list|)
argument_list|,
name|editor
operator|->
name|box
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
name|GTK_WIDGET
argument_list|(
name|editor
operator|->
name|box
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|view
argument_list|,
literal|"range_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_histogram_editor_info_update
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|view
argument_list|,
literal|"notify::histogram-channel"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_histogram_editor_info_update
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|3
argument_list|,
literal|4
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|editor
argument_list|)
argument_list|,
name|table
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
name|table
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
literal|6
condition|;
name|i
operator|++
control|)
block|{
name|gint
name|x
init|=
operator|(
name|i
operator|/
literal|3
operator|)
operator|*
literal|2
decl_stmt|;
name|gint
name|y
init|=
operator|(
name|i
operator|%
literal|3
operator|)
decl_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|gettext
argument_list|(
name|gimp_histogram_editor_labels
index|[
name|i
index|]
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|label
argument_list|,
name|x
argument_list|,
name|x
operator|+
literal|1
argument_list|,
name|y
argument_list|,
name|y
operator|+
literal|1
argument_list|,
name|GTK_FILL
argument_list|,
name|GTK_FILL
argument_list|,
literal|2
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|editor
operator|->
name|labels
index|[
name|i
index|]
operator|=
name|label
operator|=
name|gtk_label_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|label
argument_list|,
name|x
operator|+
literal|1
argument_list|,
name|x
operator|+
literal|2
argument_list|,
name|y
argument_list|,
name|y
operator|+
literal|1
argument_list|,
name|GTK_FILL
argument_list|,
name|GTK_FILL
argument_list|,
literal|2
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_histogram_editor_docked_iface_init (GimpDockedInterface * docked_iface)
name|gimp_histogram_editor_docked_iface_init
parameter_list|(
name|GimpDockedInterface
modifier|*
name|docked_iface
parameter_list|)
block|{
name|parent_docked_iface
operator|=
name|g_type_interface_peek_parent
argument_list|(
name|docked_iface
argument_list|)
expr_stmt|;
name|docked_iface
operator|->
name|set_aux_info
operator|=
name|gimp_histogram_editor_set_aux_info
expr_stmt|;
name|docked_iface
operator|->
name|get_aux_info
operator|=
name|gimp_histogram_editor_get_aux_info
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_histogram_editor_set_aux_info (GimpDocked * docked,GList * aux_info)
name|gimp_histogram_editor_set_aux_info
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|GList
modifier|*
name|aux_info
parameter_list|)
block|{
name|GimpHistogramEditor
modifier|*
name|editor
init|=
name|GIMP_HISTOGRAM_EDITOR
argument_list|(
name|docked
argument_list|)
decl_stmt|;
name|GimpHistogramView
modifier|*
name|view
init|=
name|GIMP_HISTOGRAM_BOX
argument_list|(
name|editor
operator|->
name|box
argument_list|)
operator|->
name|view
decl_stmt|;
if|if
condition|(
name|parent_docked_iface
operator|->
name|set_aux_info
condition|)
name|parent_docked_iface
operator|->
name|set_aux_info
argument_list|(
name|docked
argument_list|,
name|aux_info
argument_list|)
expr_stmt|;
name|gimp_session_info_aux_set_props
argument_list|(
name|G_OBJECT
argument_list|(
name|view
argument_list|)
argument_list|,
name|aux_info
argument_list|,
literal|"histogram-channel"
argument_list|,
literal|"histogram-scale"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GList
modifier|*
DECL|function|gimp_histogram_editor_get_aux_info (GimpDocked * docked)
name|gimp_histogram_editor_get_aux_info
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|)
block|{
name|GimpHistogramEditor
modifier|*
name|editor
init|=
name|GIMP_HISTOGRAM_EDITOR
argument_list|(
name|docked
argument_list|)
decl_stmt|;
name|GimpHistogramView
modifier|*
name|view
init|=
name|GIMP_HISTOGRAM_BOX
argument_list|(
name|editor
operator|->
name|box
argument_list|)
operator|->
name|view
decl_stmt|;
name|GList
modifier|*
name|aux_info
decl_stmt|;
name|aux_info
operator|=
name|gimp_session_info_aux_new_from_props
argument_list|(
name|G_OBJECT
argument_list|(
name|view
argument_list|)
argument_list|,
literal|"histogram-channel"
argument_list|,
literal|"histogram-scale"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|parent_docked_iface
operator|->
name|get_aux_info
condition|)
return|return
name|g_list_concat
argument_list|(
name|parent_docked_iface
operator|->
name|get_aux_info
argument_list|(
name|docked
argument_list|)
argument_list|,
name|aux_info
argument_list|)
return|;
else|else
return|return
name|aux_info
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_histogram_editor_set_image (GimpImageEditor * image_editor,GimpImage * gimage)
name|gimp_histogram_editor_set_image
parameter_list|(
name|GimpImageEditor
modifier|*
name|image_editor
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|GimpHistogramEditor
modifier|*
name|editor
init|=
name|GIMP_HISTOGRAM_EDITOR
argument_list|(
name|image_editor
argument_list|)
decl_stmt|;
name|GimpHistogramView
modifier|*
name|view
init|=
name|GIMP_HISTOGRAM_BOX
argument_list|(
name|editor
operator|->
name|box
argument_list|)
operator|->
name|view
decl_stmt|;
if|if
condition|(
name|image_editor
operator|->
name|gimage
condition|)
block|{
if|if
condition|(
name|editor
operator|->
name|idle_id
condition|)
block|{
name|g_source_remove
argument_list|(
name|editor
operator|->
name|idle_id
argument_list|)
expr_stmt|;
name|editor
operator|->
name|idle_id
operator|=
literal|0
expr_stmt|;
block|}
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|image_editor
operator|->
name|gimage
argument_list|,
name|gimp_histogram_editor_layer_changed
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|image_editor
operator|->
name|gimage
argument_list|,
name|gimp_histogram_editor_menu_update
argument_list|,
name|editor
argument_list|)
expr_stmt|;
if|if
condition|(
name|editor
operator|->
name|histogram
condition|)
block|{
name|gimp_histogram_free
argument_list|(
name|editor
operator|->
name|histogram
argument_list|)
expr_stmt|;
name|editor
operator|->
name|histogram
operator|=
name|NULL
expr_stmt|;
block|}
name|gimp_histogram_view_set_histogram
argument_list|(
name|view
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|GIMP_IMAGE_EDITOR_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|set_image
argument_list|(
name|image_editor
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimage
condition|)
block|{
name|editor
operator|->
name|histogram
operator|=
name|gimp_histogram_new
argument_list|(
name|GIMP_BASE_CONFIG
argument_list|(
name|gimage
operator|->
name|gimp
operator|->
name|config
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_histogram_view_set_histogram
argument_list|(
name|view
argument_list|,
name|editor
operator|->
name|histogram
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|gimage
argument_list|,
literal|"mode_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_histogram_editor_menu_update
argument_list|)
argument_list|,
name|editor
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|gimage
argument_list|,
literal|"active_layer_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_histogram_editor_layer_changed
argument_list|)
argument_list|,
name|editor
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
name|gimp_histogram_editor_layer_changed
argument_list|(
name|gimage
argument_list|,
name|editor
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_histogram_editor_new (GimpImage * gimage)
name|gimp_histogram_editor_new
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|GimpImageEditor
modifier|*
name|editor
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gimage
operator|==
name|NULL
operator|||
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|editor
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_HISTOGRAM_EDITOR
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimage
condition|)
name|gimp_image_editor_set_image
argument_list|(
name|editor
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_histogram_editor_layer_changed (GimpImage * gimage,GimpHistogramEditor * editor)
name|gimp_histogram_editor_layer_changed
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpHistogramEditor
modifier|*
name|editor
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
if|if
condition|(
name|editor
operator|->
name|drawable
condition|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|editor
operator|->
name|drawable
argument_list|,
name|gimp_histogram_editor_menu_update
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|editor
operator|->
name|drawable
argument_list|,
name|gimp_histogram_editor_update
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|editor
operator|->
name|drawable
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|gimage
condition|)
name|editor
operator|->
name|drawable
operator|=
operator|(
name|GimpDrawable
operator|*
operator|)
name|gimp_image_get_active_layer
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|gimp_histogram_editor_menu_update
argument_list|(
name|editor
argument_list|)
expr_stmt|;
if|if
condition|(
name|editor
operator|->
name|drawable
condition|)
block|{
name|name
operator|=
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|editor
operator|->
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|editor
operator|->
name|drawable
argument_list|,
literal|"invalidate_preview"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_histogram_editor_update
argument_list|)
argument_list|,
name|editor
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|editor
operator|->
name|drawable
argument_list|,
literal|"alpha_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_histogram_editor_menu_update
argument_list|)
argument_list|,
name|editor
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
name|gimp_histogram_editor_update
argument_list|(
name|editor
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|name
operator|=
name|_
argument_list|(
literal|"(None)"
argument_list|)
expr_stmt|;
if|if
condition|(
name|editor
operator|->
name|histogram
condition|)
block|{
name|gimp_histogram_calculate
argument_list|(
name|editor
operator|->
name|histogram
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_queue_draw
name|GTK_WIDGET
argument_list|(
name|editor
operator|->
name|box
argument_list|)
decl_stmt|;
name|gimp_histogram_editor_info_update
argument_list|(
name|editor
argument_list|)
expr_stmt|;
block|}
block|}
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|editor
operator|->
name|name
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_histogram_editor_update (GimpHistogramEditor * editor)
name|gimp_histogram_editor_update
parameter_list|(
name|GimpHistogramEditor
modifier|*
name|editor
parameter_list|)
block|{
if|if
condition|(
name|editor
operator|->
name|idle_id
condition|)
name|g_source_remove
argument_list|(
name|editor
operator|->
name|idle_id
argument_list|)
expr_stmt|;
name|editor
operator|->
name|idle_id
operator|=
name|g_idle_add_full
argument_list|(
name|G_PRIORITY_LOW
argument_list|,
operator|(
name|GSourceFunc
operator|)
name|gimp_histogram_editor_idle_update
argument_list|,
name|editor
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_histogram_editor_idle_update (GimpHistogramEditor * editor)
name|gimp_histogram_editor_idle_update
parameter_list|(
name|GimpHistogramEditor
modifier|*
name|editor
parameter_list|)
block|{
name|editor
operator|->
name|idle_id
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|editor
operator|->
name|drawable
operator|&&
name|editor
operator|->
name|histogram
condition|)
block|{
name|PixelRegion
name|region
decl_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|region
argument_list|,
name|gimp_drawable_data
argument_list|(
name|editor
operator|->
name|drawable
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|gimp_item_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|editor
operator|->
name|drawable
argument_list|)
argument_list|)
argument_list|,
name|gimp_item_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|editor
operator|->
name|drawable
argument_list|)
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_histogram_calculate
argument_list|(
name|editor
operator|->
name|histogram
argument_list|,
operator|&
name|region
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_queue_draw
name|GTK_WIDGET
argument_list|(
name|editor
operator|->
name|box
argument_list|)
decl_stmt|;
name|gimp_histogram_editor_info_update
argument_list|(
name|editor
argument_list|)
expr_stmt|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_histogram_editor_item_visible (GtkTreeModel * model,GtkTreeIter * iter,gpointer data)
name|gimp_histogram_editor_item_visible
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
name|GimpHistogramEditor
modifier|*
name|editor
init|=
name|GIMP_HISTOGRAM_EDITOR
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpHistogramChannel
name|channel
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
name|channel
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|channel
condition|)
block|{
case|case
name|GIMP_HISTOGRAM_VALUE
case|:
return|return
name|TRUE
return|;
case|case
name|GIMP_HISTOGRAM_RED
case|:
case|case
name|GIMP_HISTOGRAM_GREEN
case|:
case|case
name|GIMP_HISTOGRAM_BLUE
case|:
case|case
name|GIMP_HISTOGRAM_RGB
case|:
return|return
name|editor
operator|->
name|drawable
operator|&&
name|gimp_drawable_is_rgb
argument_list|(
name|editor
operator|->
name|drawable
argument_list|)
return|;
case|case
name|GIMP_HISTOGRAM_ALPHA
case|:
return|return
name|editor
operator|->
name|drawable
operator|&&
name|gimp_drawable_has_alpha
argument_list|(
name|editor
operator|->
name|drawable
argument_list|)
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_histogram_editor_menu_update (GimpHistogramEditor * editor)
name|gimp_histogram_editor_menu_update
parameter_list|(
name|GimpHistogramEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpHistogramView
modifier|*
name|view
init|=
name|GIMP_HISTOGRAM_BOX
argument_list|(
name|editor
operator|->
name|box
argument_list|)
operator|->
name|view
decl_stmt|;
name|GtkTreeModel
modifier|*
name|model
decl_stmt|;
name|model
operator|=
name|gtk_combo_box_get_model
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|editor
operator|->
name|menu
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_tree_model_filter_refilter
argument_list|(
name|GTK_TREE_MODEL_FILTER
argument_list|(
name|model
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_int_combo_box_set_active
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|editor
operator|->
name|menu
argument_list|)
argument_list|,
name|gimp_histogram_view_get_channel
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_histogram_editor_info_update (GimpHistogramEditor * editor)
name|gimp_histogram_editor_info_update
parameter_list|(
name|GimpHistogramEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpHistogramView
modifier|*
name|view
init|=
name|GIMP_HISTOGRAM_BOX
argument_list|(
name|editor
operator|->
name|box
argument_list|)
operator|->
name|view
decl_stmt|;
name|GimpHistogram
modifier|*
name|hist
init|=
name|editor
operator|->
name|histogram
decl_stmt|;
if|if
condition|(
name|hist
condition|)
block|{
name|gdouble
name|pixels
decl_stmt|;
name|gdouble
name|count
decl_stmt|;
name|gchar
name|text
index|[
literal|12
index|]
decl_stmt|;
name|pixels
operator|=
name|gimp_histogram_get_count
argument_list|(
name|hist
argument_list|,
name|view
operator|->
name|channel
argument_list|,
literal|0
argument_list|,
literal|255
argument_list|)
expr_stmt|;
name|count
operator|=
name|gimp_histogram_get_count
argument_list|(
name|hist
argument_list|,
name|view
operator|->
name|channel
argument_list|,
name|view
operator|->
name|start
argument_list|,
name|view
operator|->
name|end
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|text
argument_list|,
sizeof|sizeof
argument_list|(
name|text
argument_list|)
argument_list|,
literal|"%3.1f"
argument_list|,
name|gimp_histogram_get_mean
argument_list|(
name|hist
argument_list|,
name|view
operator|->
name|channel
argument_list|,
name|view
operator|->
name|start
argument_list|,
name|view
operator|->
name|end
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|editor
operator|->
name|labels
index|[
literal|0
index|]
argument_list|)
argument_list|,
name|text
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|text
argument_list|,
sizeof|sizeof
argument_list|(
name|text
argument_list|)
argument_list|,
literal|"%3.1f"
argument_list|,
name|gimp_histogram_get_std_dev
argument_list|(
name|hist
argument_list|,
name|view
operator|->
name|channel
argument_list|,
name|view
operator|->
name|start
argument_list|,
name|view
operator|->
name|end
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|editor
operator|->
name|labels
index|[
literal|1
index|]
argument_list|)
argument_list|,
name|text
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|text
argument_list|,
sizeof|sizeof
argument_list|(
name|text
argument_list|)
argument_list|,
literal|"%3.1f"
argument_list|,
operator|(
name|gdouble
operator|)
name|gimp_histogram_get_median
argument_list|(
name|hist
argument_list|,
name|view
operator|->
name|channel
argument_list|,
name|view
operator|->
name|start
argument_list|,
name|view
operator|->
name|end
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|editor
operator|->
name|labels
index|[
literal|2
index|]
argument_list|)
argument_list|,
name|text
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|text
argument_list|,
sizeof|sizeof
argument_list|(
name|text
argument_list|)
argument_list|,
literal|"%8d"
argument_list|,
operator|(
name|gint
operator|)
name|pixels
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|editor
operator|->
name|labels
index|[
literal|3
index|]
argument_list|)
argument_list|,
name|text
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|text
argument_list|,
sizeof|sizeof
argument_list|(
name|text
argument_list|)
argument_list|,
literal|"%8d"
argument_list|,
operator|(
name|gint
operator|)
name|count
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|editor
operator|->
name|labels
index|[
literal|4
index|]
argument_list|)
argument_list|,
name|text
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|text
argument_list|,
sizeof|sizeof
argument_list|(
name|text
argument_list|)
argument_list|,
literal|"%4.1f"
argument_list|,
operator|(
name|pixels
operator|>
literal|0
condition|?
operator|(
literal|100.0
operator|*
name|count
operator|/
name|pixels
operator|)
else|:
literal|0.0
operator|)
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|editor
operator|->
name|labels
index|[
literal|5
index|]
argument_list|)
argument_list|,
name|text
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|6
condition|;
name|i
operator|++
control|)
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|editor
operator|->
name|labels
index|[
name|i
index|]
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

