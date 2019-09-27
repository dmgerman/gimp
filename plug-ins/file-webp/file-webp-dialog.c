begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * file-webp - WebP file format plug-in for the GIMP  * Copyright (C) 2015  Nathan Osman  * Copyright (C) 2016  Ben Touchette  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation, either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpui.h>
end_include

begin_include
include|#
directive|include
file|<webp/encode.h>
end_include

begin_include
include|#
directive|include
file|"file-webp.h"
end_include

begin_include
include|#
directive|include
file|"file-webp-dialog.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|save_dialog_toggle_scale
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|save_dialog_toggle_minsize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|show_maxkeyframe_hints
parameter_list|(
name|GtkAdjustment
modifier|*
name|adj
parameter_list|,
name|GtkLabel
modifier|*
name|label
parameter_list|)
function_decl|;
end_function_decl

begin_function
specifier|static
name|void
DECL|function|save_dialog_toggle_scale (GtkWidget * widget,gpointer data)
name|save_dialog_toggle_scale
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gimp_scale_entry_set_sensitive
argument_list|(
name|data
argument_list|,
operator|!
name|gtk_toggle_button_get_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|widget
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|save_dialog_toggle_minsize (GtkWidget * widget,gpointer data)
name|save_dialog_toggle_minsize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gtk_widget_set_sensitive
argument_list|(
name|GTK_WIDGET
argument_list|(
name|data
argument_list|)
argument_list|,
operator|!
name|gtk_toggle_button_get_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|widget
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|show_maxkeyframe_hints (GtkAdjustment * adj,GtkLabel * label)
name|show_maxkeyframe_hints
parameter_list|(
name|GtkAdjustment
modifier|*
name|adj
parameter_list|,
name|GtkLabel
modifier|*
name|label
parameter_list|)
block|{
name|gint
name|kmax
decl_stmt|;
name|kmax
operator|=
operator|(
name|gint
operator|)
name|gtk_adjustment_get_value
argument_list|(
name|adj
argument_list|)
expr_stmt|;
if|if
condition|(
name|kmax
operator|==
literal|0
condition|)
block|{
name|gtk_label_set_text
argument_list|(
name|label
argument_list|,
name|_
argument_list|(
literal|"(no keyframes)"
argument_list|)
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|kmax
operator|==
literal|1
condition|)
block|{
name|gtk_label_set_text
argument_list|(
name|label
argument_list|,
name|_
argument_list|(
literal|"(all frames are keyframes)"
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_label_set_text
argument_list|(
name|label
argument_list|,
literal|""
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gboolean
DECL|function|save_dialog (WebPSaveParams * params,GimpImage * image)
name|save_dialog
parameter_list|(
name|WebPSaveParams
modifier|*
name|params
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|grid
decl_stmt|;
name|GtkWidget
modifier|*
name|expander
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox2
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|toggle
decl_stmt|;
name|GtkWidget
modifier|*
name|toggle_minsize
decl_stmt|;
name|GtkWidget
modifier|*
name|combo
decl_stmt|;
name|GtkAdjustment
modifier|*
name|quality_scale
decl_stmt|;
name|GtkAdjustment
modifier|*
name|alpha_quality_scale
decl_stmt|;
name|gint32
name|nlayers
decl_stmt|;
name|gboolean
name|animation_supported
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|run
decl_stmt|;
name|gchar
modifier|*
name|text
decl_stmt|;
name|gint
name|row
init|=
literal|0
decl_stmt|;
name|g_free
argument_list|(
name|gimp_image_get_layers
argument_list|(
name|image
argument_list|,
operator|&
name|nlayers
argument_list|)
argument_list|)
expr_stmt|;
name|animation_supported
operator|=
name|nlayers
operator|>
literal|1
expr_stmt|;
comment|/* Create the dialog */
name|dialog
operator|=
name|gimp_export_dialog_new
argument_list|(
name|_
argument_list|(
literal|"WebP"
argument_list|)
argument_list|,
name|PLUG_IN_BINARY
argument_list|,
name|SAVE_PROC
argument_list|)
expr_stmt|;
comment|/* Create the vbox */
name|vbox
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
name|vbox
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|gimp_export_dialog_get_content_area
argument_list|(
name|dialog
argument_list|)
argument_list|)
argument_list|,
name|vbox
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
name|vbox
argument_list|)
expr_stmt|;
comment|/* Create the grid */
name|grid
operator|=
name|gtk_grid_new
argument_list|()
expr_stmt|;
name|gtk_grid_set_row_spacing
argument_list|(
name|GTK_GRID
argument_list|(
name|grid
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_grid_set_column_spacing
argument_list|(
name|GTK_GRID
argument_list|(
name|grid
argument_list|)
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
name|grid
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
name|grid
argument_list|)
expr_stmt|;
comment|/* Create the lossless checkbox */
name|toggle
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Lossless"
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
name|params
operator|->
name|lossless
argument_list|)
expr_stmt|;
name|gtk_grid_attach
argument_list|(
name|GTK_GRID
argument_list|(
name|grid
argument_list|)
argument_list|,
name|toggle
argument_list|,
literal|0
argument_list|,
name|row
argument_list|,
literal|3
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|toggle
argument_list|)
expr_stmt|;
name|row
operator|++
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
name|params
operator|->
name|lossless
argument_list|)
expr_stmt|;
comment|/* Create the slider for image quality */
name|quality_scale
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_GRID
argument_list|(
name|grid
argument_list|)
argument_list|,
literal|0
argument_list|,
name|row
operator|++
argument_list|,
name|_
argument_list|(
literal|"Image _quality:"
argument_list|)
argument_list|,
literal|125
argument_list|,
literal|0
argument_list|,
name|params
operator|->
name|quality
argument_list|,
literal|0.0
argument_list|,
literal|100.0
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
name|_
argument_list|(
literal|"Image quality"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_scale_entry_set_sensitive
argument_list|(
name|quality_scale
argument_list|,
operator|!
name|params
operator|->
name|lossless
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|quality_scale
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_float_adjustment_update
argument_list|)
argument_list|,
operator|&
name|params
operator|->
name|quality
argument_list|)
expr_stmt|;
comment|/* Create the slider for alpha channel quality */
name|alpha_quality_scale
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_GRID
argument_list|(
name|grid
argument_list|)
argument_list|,
literal|0
argument_list|,
name|row
operator|++
argument_list|,
name|_
argument_list|(
literal|"Alpha q_uality:"
argument_list|)
argument_list|,
literal|125
argument_list|,
literal|0
argument_list|,
name|params
operator|->
name|alpha_quality
argument_list|,
literal|0.0
argument_list|,
literal|100.0
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
name|_
argument_list|(
literal|"Alpha channel quality"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_scale_entry_set_sensitive
argument_list|(
name|alpha_quality_scale
argument_list|,
operator|!
name|params
operator|->
name|lossless
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|alpha_quality_scale
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_float_adjustment_update
argument_list|)
argument_list|,
operator|&
name|params
operator|->
name|alpha_quality
argument_list|)
expr_stmt|;
comment|/* Enable and disable the sliders when the lossless option is selected */
name|g_signal_connect
argument_list|(
name|toggle
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|save_dialog_toggle_scale
argument_list|)
argument_list|,
name|quality_scale
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
name|save_dialog_toggle_scale
argument_list|)
argument_list|,
name|alpha_quality_scale
argument_list|)
expr_stmt|;
comment|/* Create the combobox containing the presets */
name|combo
operator|=
name|gimp_int_combo_box_new
argument_list|(
literal|"Default"
argument_list|,
name|WEBP_PRESET_DEFAULT
argument_list|,
literal|"Picture"
argument_list|,
name|WEBP_PRESET_PICTURE
argument_list|,
literal|"Photo"
argument_list|,
name|WEBP_PRESET_PHOTO
argument_list|,
literal|"Drawing"
argument_list|,
name|WEBP_PRESET_DRAWING
argument_list|,
literal|"Icon"
argument_list|,
name|WEBP_PRESET_ICON
argument_list|,
literal|"Text"
argument_list|,
name|WEBP_PRESET_TEXT
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|label
operator|=
name|gimp_grid_attach_aligned
argument_list|(
name|GTK_GRID
argument_list|(
name|grid
argument_list|)
argument_list|,
literal|0
argument_list|,
name|row
operator|++
argument_list|,
name|_
argument_list|(
literal|"Source _type:"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|,
name|combo
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|label
argument_list|,
name|_
argument_list|(
literal|"WebP encoder \"preset\""
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_int_combo_box_connect
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|,
name|params
operator|->
name|preset
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_int_combo_box_get_active
argument_list|)
argument_list|,
operator|&
name|params
operator|->
name|preset
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|animation_supported
condition|)
block|{
name|GtkWidget
modifier|*
name|animation_box
decl_stmt|;
name|GtkAdjustment
modifier|*
name|adj
decl_stmt|;
name|GtkWidget
modifier|*
name|delay
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|label_kf
decl_stmt|;
name|GtkAdjustment
modifier|*
name|adj_kf
decl_stmt|;
name|GtkWidget
modifier|*
name|kf_distance
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox_kf
decl_stmt|;
name|PangoAttrList
modifier|*
name|attrs
decl_stmt|;
name|PangoAttribute
modifier|*
name|attr
decl_stmt|;
name|vbox2
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|vbox2
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
name|vbox2
argument_list|)
expr_stmt|;
name|text
operator|=
name|g_strdup_printf
argument_list|(
literal|"<b>%s</b>"
argument_list|,
name|_
argument_list|(
literal|"_Advanced Options"
argument_list|)
argument_list|)
expr_stmt|;
name|expander
operator|=
name|gtk_expander_new_with_mnemonic
argument_list|(
name|text
argument_list|)
expr_stmt|;
name|gtk_expander_set_use_markup
argument_list|(
name|GTK_EXPANDER
argument_list|(
name|expander
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|text
argument_list|)
expr_stmt|;
comment|/* Create the top-level animation checkbox expander */
name|text
operator|=
name|g_strdup_printf
argument_list|(
literal|"<b>%s</b>"
argument_list|,
name|_
argument_list|(
literal|"As A_nimation"
argument_list|)
argument_list|)
expr_stmt|;
name|toggle
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|text
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|text
argument_list|)
expr_stmt|;
name|gtk_label_set_use_markup
argument_list|(
name|GTK_LABEL
argument_list|(
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|toggle
argument_list|)
argument_list|)
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|,
name|params
operator|->
name|animation
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox2
argument_list|)
argument_list|,
name|toggle
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
name|params
operator|->
name|animation
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_frame_new
argument_list|(
literal|"<expander>"
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox2
argument_list|)
argument_list|,
name|frame
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
name|frame
argument_list|)
expr_stmt|;
name|g_object_bind_property
argument_list|(
name|toggle
argument_list|,
literal|"active"
argument_list|,
name|frame
argument_list|,
literal|"visible"
argument_list|,
name|G_BINDING_SYNC_CREATE
argument_list|)
expr_stmt|;
comment|/* animation options box */
name|animation_box
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
name|animation_box
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|animation_box
argument_list|)
expr_stmt|;
comment|/* loop animation checkbox */
name|toggle
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"Loop _forever"
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
name|params
operator|->
name|loop
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|animation_box
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
name|params
operator|->
name|loop
argument_list|)
expr_stmt|;
comment|/* create a hbox for 'max key-frame distance */
name|hbox_kf
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|animation_box
argument_list|)
argument_list|,
name|hbox_kf
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|hbox_kf
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox_kf
argument_list|)
expr_stmt|;
comment|/* label for 'max key-frame distance' adjustment */
name|label_kf
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Max distance between key-frames:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_label_set_xalign
argument_list|(
name|GTK_LABEL
argument_list|(
name|label_kf
argument_list|)
argument_list|,
literal|0.2
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox_kf
argument_list|)
argument_list|,
name|label_kf
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
name|label_kf
argument_list|)
expr_stmt|;
comment|/* key-frame distance entry */
name|adj_kf
operator|=
name|gtk_adjustment_new
argument_list|(
name|params
operator|->
name|kf_distance
argument_list|,
literal|0.0
argument_list|,
literal|10000.0
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|kf_distance
operator|=
name|gimp_spin_button_new
argument_list|(
name|adj_kf
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_spin_button_set_numeric
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|kf_distance
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox_kf
argument_list|)
argument_list|,
name|kf_distance
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
name|kf_distance
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|adj_kf
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_int_adjustment_update
argument_list|)
argument_list|,
operator|&
name|params
operator|->
name|kf_distance
argument_list|)
expr_stmt|;
comment|/* Add some hinting text for special values of key-frame distance. */
name|label_kf
operator|=
name|gtk_label_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox_kf
argument_list|)
argument_list|,
name|label_kf
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
name|label_kf
argument_list|)
expr_stmt|;
name|attrs
operator|=
name|pango_attr_list_new
argument_list|()
expr_stmt|;
name|attr
operator|=
name|pango_attr_style_new
argument_list|(
name|PANGO_STYLE_ITALIC
argument_list|)
expr_stmt|;
name|pango_attr_list_insert
argument_list|(
name|attrs
argument_list|,
name|attr
argument_list|)
expr_stmt|;
name|gtk_label_set_attributes
argument_list|(
name|GTK_LABEL
argument_list|(
name|label_kf
argument_list|)
argument_list|,
name|attrs
argument_list|)
expr_stmt|;
name|pango_attr_list_unref
argument_list|(
name|attrs
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|adj_kf
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|show_maxkeyframe_hints
argument_list|)
argument_list|,
name|label_kf
argument_list|)
expr_stmt|;
name|show_maxkeyframe_hints
argument_list|(
name|adj_kf
argument_list|,
name|GTK_LABEL
argument_list|(
name|label_kf
argument_list|)
argument_list|)
expr_stmt|;
comment|/* minimize-size checkbox */
name|toggle_minsize
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Minimize output size (slower)"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|animation_box
argument_list|)
argument_list|,
name|toggle_minsize
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
name|toggle_minsize
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|toggle_minsize
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_toggle_button_update
argument_list|)
argument_list|,
operator|&
name|params
operator|->
name|minimize_size
argument_list|)
expr_stmt|;
comment|/* Enable and disable the kf-distance box when the 'minimize size' option is selected */
name|g_signal_connect
argument_list|(
name|toggle_minsize
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|save_dialog_toggle_minsize
argument_list|)
argument_list|,
name|hbox_kf
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|toggle_minsize
argument_list|)
argument_list|,
name|params
operator|->
name|minimize_size
argument_list|)
expr_stmt|;
comment|/* create a hbox for delay */
name|hbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|animation_box
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
comment|/* label for 'delay' adjustment */
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Delay between frames where unspecified:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_label_set_xalign
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
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
comment|/* default delay */
name|adj
operator|=
name|gtk_adjustment_new
argument_list|(
name|params
operator|->
name|delay
argument_list|,
literal|1
argument_list|,
literal|10000
argument_list|,
literal|1
argument_list|,
literal|10
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|delay
operator|=
name|gimp_spin_button_new
argument_list|(
name|adj
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_spin_button_set_numeric
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|delay
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|delay
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
name|delay
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|adj
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_int_adjustment_update
argument_list|)
argument_list|,
operator|&
name|params
operator|->
name|delay
argument_list|)
expr_stmt|;
comment|/* label for 'ms' adjustment */
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"milliseconds"
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
comment|/* Create the force-delay checkbox */
name|toggle
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"Use _delay entered above for all frames"
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
name|params
operator|->
name|force_delay
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|animation_box
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
name|params
operator|->
name|force_delay
argument_list|)
expr_stmt|;
block|}
comment|/* Save EXIF data */
name|toggle
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Save Exif data"
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
name|params
operator|->
name|save_exif
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
name|params
operator|->
name|save_exif
argument_list|)
expr_stmt|;
comment|/* XMP metadata */
name|toggle
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"Save _XMP data"
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
name|params
operator|->
name|save_xmp
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
name|params
operator|->
name|save_xmp
argument_list|)
expr_stmt|;
comment|/* Color profile */
name|toggle
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"Save color _profile"
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
name|params
operator|->
name|save_profile
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
name|params
operator|->
name|save_profile
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
name|run
operator|=
operator|(
name|gimp_dialog_run
argument_list|(
name|GIMP_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
operator|==
name|GTK_RESPONSE_OK
operator|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
return|return
name|run
return|;
block|}
end_function

end_unit

