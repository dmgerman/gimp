begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"dialogs-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer-filter.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdatafactory.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplist.h"
end_include

begin_include
include|#
directive|include
file|"core/gimppalette.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpviewablebox.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpviewabledialog.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"convert-indexed-dialog.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_typedef
DECL|typedef|IndexedDialog
typedef|typedef
name|struct
name|_IndexedDialog
name|IndexedDialog
typedef|;
end_typedef

begin_struct
DECL|struct|_IndexedDialog
struct|struct
name|_IndexedDialog
block|{
DECL|member|image
name|GimpImage
modifier|*
name|image
decl_stmt|;
DECL|member|palette_type
name|GimpConvertPaletteType
name|palette_type
decl_stmt|;
DECL|member|max_colors
name|gint
name|max_colors
decl_stmt|;
DECL|member|remove_duplicates
name|gboolean
name|remove_duplicates
decl_stmt|;
DECL|member|dither_type
name|GimpConvertDitherType
name|dither_type
decl_stmt|;
DECL|member|dither_alpha
name|gboolean
name|dither_alpha
decl_stmt|;
DECL|member|dither_text_layers
name|gboolean
name|dither_text_layers
decl_stmt|;
DECL|member|custom_palette
name|GimpPalette
modifier|*
name|custom_palette
decl_stmt|;
DECL|member|callback
name|GimpConvertIndexedCallback
name|callback
decl_stmt|;
DECL|member|user_data
name|gpointer
name|user_data
decl_stmt|;
DECL|member|dialog
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
DECL|member|context
name|GimpContext
modifier|*
name|context
decl_stmt|;
DECL|member|container
name|GimpContainer
modifier|*
name|container
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|convert_dialog_free
parameter_list|(
name|IndexedDialog
modifier|*
name|private
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|convert_dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|IndexedDialog
modifier|*
name|private
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|convert_dialog_palette_box
parameter_list|(
name|IndexedDialog
modifier|*
name|private
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|convert_dialog_palette_filter
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|convert_dialog_palette_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpPalette
modifier|*
name|palette
parameter_list|,
name|IndexedDialog
modifier|*
name|private
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|convert_indexed_dialog_new (GimpImage * image,GimpContext * context,GtkWidget * parent,GimpConvertPaletteType palette_type,gint max_colors,gboolean remove_duplicates,GimpConvertDitherType dither_type,gboolean dither_alpha,gboolean dither_text_layers,GimpPalette * custom_palette,GimpConvertIndexedCallback callback,gpointer user_data)
name|convert_indexed_dialog_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|,
name|GimpConvertPaletteType
name|palette_type
parameter_list|,
name|gint
name|max_colors
parameter_list|,
name|gboolean
name|remove_duplicates
parameter_list|,
name|GimpConvertDitherType
name|dither_type
parameter_list|,
name|gboolean
name|dither_alpha
parameter_list|,
name|gboolean
name|dither_text_layers
parameter_list|,
name|GimpPalette
modifier|*
name|custom_palette
parameter_list|,
name|GimpConvertIndexedCallback
name|callback
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|IndexedDialog
modifier|*
name|private
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|main_vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkAdjustment
modifier|*
name|adjustment
decl_stmt|;
name|GtkWidget
modifier|*
name|spinbutton
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|toggle
decl_stmt|;
name|GtkWidget
modifier|*
name|palette_box
decl_stmt|;
name|GtkWidget
modifier|*
name|combo
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GTK_IS_WIDGET
argument_list|(
name|parent
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|custom_palette
operator|==
name|NULL
operator|||
name|GIMP_IS_PALETTE
argument_list|(
name|custom_palette
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|callback
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|private
operator|=
name|g_slice_new0
argument_list|(
name|IndexedDialog
argument_list|)
expr_stmt|;
name|private
operator|->
name|image
operator|=
name|image
expr_stmt|;
name|private
operator|->
name|palette_type
operator|=
name|palette_type
expr_stmt|;
name|private
operator|->
name|max_colors
operator|=
name|max_colors
expr_stmt|;
name|private
operator|->
name|remove_duplicates
operator|=
name|remove_duplicates
expr_stmt|;
name|private
operator|->
name|dither_type
operator|=
name|dither_type
expr_stmt|;
name|private
operator|->
name|dither_alpha
operator|=
name|dither_alpha
expr_stmt|;
name|private
operator|->
name|dither_text_layers
operator|=
name|dither_text_layers
expr_stmt|;
name|private
operator|->
name|custom_palette
operator|=
name|custom_palette
expr_stmt|;
name|private
operator|->
name|callback
operator|=
name|callback
expr_stmt|;
name|private
operator|->
name|user_data
operator|=
name|user_data
expr_stmt|;
name|private
operator|->
name|dialog
operator|=
name|dialog
operator|=
name|gimp_viewable_dialog_new
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|image
argument_list|)
argument_list|,
name|context
argument_list|,
name|_
argument_list|(
literal|"Indexed Color Conversion"
argument_list|)
argument_list|,
literal|"gimp-image-convert-indexed"
argument_list|,
name|GIMP_ICON_CONVERT_INDEXED
argument_list|,
name|_
argument_list|(
literal|"Convert Image to Indexed Colors"
argument_list|)
argument_list|,
name|parent
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_IMAGE_CONVERT_INDEXED
argument_list|,
name|_
argument_list|(
literal|"_Cancel"
argument_list|)
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|_
argument_list|(
literal|"C_onvert"
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_dialog_set_alternative_button_order
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_window_set_resizable
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_object_weak_ref
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
operator|(
name|GWeakNotify
operator|)
name|convert_dialog_free
argument_list|,
name|private
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|convert_dialog_response
argument_list|)
argument_list|,
name|private
argument_list|)
expr_stmt|;
name|palette_box
operator|=
name|convert_dialog_palette_box
argument_list|(
name|private
argument_list|)
expr_stmt|;
name|main_vbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|gtk_dialog_get_content_area
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
argument_list|)
argument_list|,
name|main_vbox
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
name|main_vbox
argument_list|)
expr_stmt|;
comment|/*  palette  */
name|frame
operator|=
name|gimp_enum_radio_frame_new_with_range
argument_list|(
name|GIMP_TYPE_CONVERT_PALETTE_TYPE
argument_list|,
name|GIMP_CONVERT_PALETTE_GENERATE
argument_list|,
operator|(
name|palette_box
condition|?
name|GIMP_CONVERT_PALETTE_CUSTOM
else|:
name|GIMP_CONVERT_PALETTE_MONO
operator|)
argument_list|,
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Colormap"
argument_list|)
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_radio_button_update
argument_list|)
argument_list|,
operator|&
name|private
operator|->
name|palette_type
argument_list|,
operator|&
name|button
argument_list|)
expr_stmt|;
name|gimp_int_radio_group_set_active
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|private
operator|->
name|palette_type
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|frame
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
name|frame
argument_list|)
expr_stmt|;
comment|/*  max n_colors  */
name|hbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gimp_enum_radio_frame_add
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|hbox
argument_list|,
name|GIMP_CONVERT_PALETTE_GENERATE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Maximum number of colors:"
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
if|if
condition|(
name|private
operator|->
name|max_colors
operator|==
literal|256
operator|&&
name|gimp_image_has_alpha
argument_list|(
name|image
argument_list|)
condition|)
name|private
operator|->
name|max_colors
operator|=
literal|255
expr_stmt|;
name|adjustment
operator|=
operator|(
name|GtkAdjustment
operator|*
operator|)
name|gtk_adjustment_new
argument_list|(
name|private
operator|->
name|max_colors
argument_list|,
literal|2
argument_list|,
literal|256
argument_list|,
literal|1
argument_list|,
literal|8
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|spinbutton
operator|=
name|gtk_spin_button_new
argument_list|(
name|adjustment
argument_list|,
literal|1.0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_spin_button_set_numeric
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|spinbutton
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_label_set_mnemonic_widget
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|spinbutton
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|spinbutton
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
name|spinbutton
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|adjustment
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_int_adjustment_update
argument_list|)
argument_list|,
operator|&
name|private
operator|->
name|max_colors
argument_list|)
expr_stmt|;
comment|/*  custom palette  */
if|if
condition|(
name|palette_box
condition|)
block|{
name|gimp_enum_radio_frame_add
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|palette_box
argument_list|,
name|GIMP_CONVERT_PALETTE_CUSTOM
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|palette_box
argument_list|)
expr_stmt|;
block|}
name|vbox
operator|=
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|frame
argument_list|)
argument_list|)
expr_stmt|;
name|toggle
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Remove unused and duplicate "
literal|"colors from colormap"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|,
name|private
operator|->
name|remove_duplicates
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|toggle
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|toggle
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|toggle
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_toggle_button_update
argument_list|)
argument_list|,
operator|&
name|private
operator|->
name|remove_duplicates
argument_list|)
expr_stmt|;
name|g_object_bind_property
argument_list|(
name|button
argument_list|,
literal|"active"
argument_list|,
name|toggle
argument_list|,
literal|"sensitive"
argument_list|,
name|G_BINDING_SYNC_CREATE
operator||
name|G_BINDING_INVERT_BOOLEAN
argument_list|)
expr_stmt|;
comment|/*  dithering  */
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Dithering"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|frame
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
name|frame
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
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
name|gtk_label_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"Color _dithering:"
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
name|combo
operator|=
name|gimp_enum_combo_box_new
argument_list|(
name|GIMP_TYPE_CONVERT_DITHER_TYPE
argument_list|)
expr_stmt|;
name|gtk_label_set_mnemonic_widget
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|combo
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|combo
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
name|combo
argument_list|)
expr_stmt|;
name|gimp_int_combo_box_connect
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|,
name|private
operator|->
name|dither_type
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_int_combo_box_get_active
argument_list|)
argument_list|,
operator|&
name|private
operator|->
name|dither_type
argument_list|)
expr_stmt|;
name|toggle
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"Enable dithering of _transparency"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|,
name|private
operator|->
name|dither_alpha
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|toggle
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
name|toggle
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|toggle
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_toggle_button_update
argument_list|)
argument_list|,
operator|&
name|private
operator|->
name|dither_alpha
argument_list|)
expr_stmt|;
name|toggle
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"Enable dithering of text layers"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|,
name|private
operator|->
name|dither_text_layers
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|toggle
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
name|toggle
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|toggle
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_toggle_button_update
argument_list|)
argument_list|,
operator|&
name|private
operator|->
name|dither_text_layers
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|toggle
argument_list|,
name|_
argument_list|(
literal|"Dithering text layers will make them uneditable"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|dialog
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|convert_dialog_free (IndexedDialog * private)
name|convert_dialog_free
parameter_list|(
name|IndexedDialog
modifier|*
name|private
parameter_list|)
block|{
if|if
condition|(
name|private
operator|->
name|container
condition|)
name|g_object_unref
argument_list|(
name|private
operator|->
name|container
argument_list|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|context
condition|)
name|g_object_unref
argument_list|(
name|private
operator|->
name|context
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|IndexedDialog
argument_list|,
name|private
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|convert_dialog_response (GtkWidget * dialog,gint response_id,IndexedDialog * private)
name|convert_dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|IndexedDialog
modifier|*
name|private
parameter_list|)
block|{
if|if
condition|(
name|response_id
operator|==
name|GTK_RESPONSE_OK
condition|)
block|{
name|private
operator|->
name|callback
argument_list|(
name|dialog
argument_list|,
name|private
operator|->
name|image
argument_list|,
name|private
operator|->
name|palette_type
argument_list|,
name|private
operator|->
name|max_colors
argument_list|,
name|private
operator|->
name|remove_duplicates
argument_list|,
name|private
operator|->
name|dither_type
argument_list|,
name|private
operator|->
name|dither_alpha
argument_list|,
name|private
operator|->
name|dither_text_layers
argument_list|,
name|private
operator|->
name|custom_palette
argument_list|,
name|private
operator|->
name|user_data
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|convert_dialog_palette_box (IndexedDialog * private)
name|convert_dialog_palette_box
parameter_list|(
name|IndexedDialog
modifier|*
name|private
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
init|=
name|private
operator|->
name|image
operator|->
name|gimp
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|GimpPalette
modifier|*
name|web_palette
init|=
name|NULL
decl_stmt|;
name|gboolean
name|custom_found
init|=
name|FALSE
decl_stmt|;
comment|/* We can't dither to> 256 colors */
name|private
operator|->
name|container
operator|=
name|gimp_container_filter
argument_list|(
name|gimp_data_factory_get_container
argument_list|(
name|gimp
operator|->
name|palette_factory
argument_list|)
argument_list|,
name|convert_dialog_palette_filter
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_container_is_empty
argument_list|(
name|private
operator|->
name|container
argument_list|)
condition|)
block|{
name|g_object_unref
argument_list|(
name|private
operator|->
name|container
argument_list|)
expr_stmt|;
name|private
operator|->
name|container
operator|=
name|NULL
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|private
operator|->
name|context
operator|=
name|gimp_context_new
argument_list|(
name|gimp
argument_list|,
literal|"convert-dialog"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|private
operator|->
name|container
argument_list|)
operator|->
name|queue
operator|->
name|head
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpPalette
modifier|*
name|palette
init|=
name|list
operator|->
name|data
decl_stmt|;
comment|/* Preferentially, the initial default is 'Web' if available */
if|if
condition|(
name|web_palette
operator|==
name|NULL
operator|&&
name|g_ascii_strcasecmp
argument_list|(
name|gimp_object_get_name
argument_list|(
name|palette
argument_list|)
argument_list|,
literal|"Web"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|web_palette
operator|=
name|palette
expr_stmt|;
block|}
if|if
condition|(
name|private
operator|->
name|custom_palette
operator|==
name|palette
condition|)
name|custom_found
operator|=
name|TRUE
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|custom_found
condition|)
block|{
if|if
condition|(
name|web_palette
condition|)
name|private
operator|->
name|custom_palette
operator|=
name|web_palette
expr_stmt|;
else|else
name|private
operator|->
name|custom_palette
operator|=
name|GIMP_LIST
argument_list|(
name|private
operator|->
name|container
argument_list|)
operator|->
name|queue
operator|->
name|head
operator|->
name|data
expr_stmt|;
block|}
name|gimp_context_set_palette
argument_list|(
name|private
operator|->
name|context
argument_list|,
name|private
operator|->
name|custom_palette
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|private
operator|->
name|context
argument_list|,
literal|"palette-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|convert_dialog_palette_changed
argument_list|)
argument_list|,
name|private
argument_list|)
expr_stmt|;
return|return
name|gimp_palette_box_new
argument_list|(
name|private
operator|->
name|container
argument_list|,
name|private
operator|->
name|context
argument_list|,
name|NULL
argument_list|,
literal|4
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|convert_dialog_palette_filter (GimpObject * object,gpointer user_data)
name|convert_dialog_palette_filter
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpPalette
modifier|*
name|palette
init|=
name|GIMP_PALETTE
argument_list|(
name|object
argument_list|)
decl_stmt|;
return|return
operator|(
name|gimp_palette_get_n_colors
argument_list|(
name|palette
argument_list|)
operator|>
literal|0
operator|&&
name|gimp_palette_get_n_colors
argument_list|(
name|palette
argument_list|)
operator|<=
literal|256
operator|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|convert_dialog_palette_changed (GimpContext * context,GimpPalette * palette,IndexedDialog * private)
name|convert_dialog_palette_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpPalette
modifier|*
name|palette
parameter_list|,
name|IndexedDialog
modifier|*
name|private
parameter_list|)
block|{
if|if
condition|(
operator|!
name|palette
condition|)
return|return;
if|if
condition|(
name|gimp_palette_get_n_colors
argument_list|(
name|palette
argument_list|)
operator|>
literal|256
condition|)
block|{
name|gimp_message
argument_list|(
name|private
operator|->
name|image
operator|->
name|gimp
argument_list|,
name|G_OBJECT
argument_list|(
name|private
operator|->
name|dialog
argument_list|)
argument_list|,
name|GIMP_MESSAGE_WARNING
argument_list|,
name|_
argument_list|(
literal|"Cannot convert to a palette "
literal|"with more than 256 colors."
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|private
operator|->
name|custom_palette
operator|=
name|palette
expr_stmt|;
block|}
block|}
end_function

end_unit

