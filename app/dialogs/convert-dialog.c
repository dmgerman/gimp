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
file|"gui-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
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
file|"core/gimpimage-convert.h"
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
file|"widgets/gimpenummenu.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpviewabledialog.h"
end_include

begin_include
include|#
directive|include
file|"palette-select.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon27cb14f60108
block|{
DECL|member|shell
name|GtkWidget
modifier|*
name|shell
decl_stmt|;
DECL|member|custom_palette_button
name|GtkWidget
modifier|*
name|custom_palette_button
decl_stmt|;
DECL|member|gimage
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
DECL|member|palette_select
name|PaletteSelect
modifier|*
name|palette_select
decl_stmt|;
DECL|member|dither_type
name|GimpConvertDitherType
name|dither_type
decl_stmt|;
DECL|member|alpha_dither
name|gboolean
name|alpha_dither
decl_stmt|;
DECL|member|remove_dups
name|gboolean
name|remove_dups
decl_stmt|;
DECL|member|num_colors
name|gint
name|num_colors
decl_stmt|;
DECL|member|palette
name|gint
name|palette
decl_stmt|;
DECL|member|palette_type
name|GimpConvertPaletteType
name|palette_type
decl_stmt|;
DECL|typedef|IndexedDialog
block|}
name|IndexedDialog
typedef|;
end_typedef

begin_function_decl
specifier|static
name|void
name|indexed_response
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
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|indexed_destroy_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|IndexedDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|indexed_custom_palette_button_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|IndexedDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|indexed_palette_select_destroy_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|IndexedDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|build_palette_button
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|UserHasWebPal
specifier|static
name|gboolean
name|UserHasWebPal
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|theCustomPalette
specifier|static
name|GimpPalette
modifier|*
name|theCustomPalette
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* Defaults */
end_comment

begin_decl_stmt
DECL|variable|saved_dither_type
specifier|static
name|GimpConvertDitherType
name|saved_dither_type
init|=
name|GIMP_FS_DITHER
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|saved_alpha_dither
specifier|static
name|gboolean
name|saved_alpha_dither
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|saved_remove_dups
specifier|static
name|gboolean
name|saved_remove_dups
init|=
name|TRUE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|saved_num_colors
specifier|static
name|gint
name|saved_num_colors
init|=
literal|256
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|saved_palette_type
specifier|static
name|GimpConvertPaletteType
name|saved_palette_type
init|=
name|GIMP_MAKE_PALETTE
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|convert_to_rgb (GimpImage * gimage)
name|convert_to_rgb
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_convert
argument_list|(
name|gimage
argument_list|,
name|GIMP_RGB
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|convert_to_grayscale (GimpImage * gimage)
name|convert_to_grayscale
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_convert
argument_list|(
name|gimage
argument_list|,
name|GIMP_GRAY
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|convert_to_indexed (GimpImage * gimage,GtkWidget * parent)
name|convert_to_indexed
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|)
block|{
name|IndexedDialog
modifier|*
name|dialog
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
name|GtkObject
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
name|GSList
modifier|*
name|group
init|=
name|NULL
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GTK_IS_WIDGET
argument_list|(
name|parent
argument_list|)
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|g_new0
argument_list|(
name|IndexedDialog
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|gimage
operator|=
name|gimage
expr_stmt|;
name|dialog
operator|->
name|custom_palette_button
operator|=
name|build_palette_button
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|dither_type
operator|=
name|saved_dither_type
expr_stmt|;
name|dialog
operator|->
name|alpha_dither
operator|=
name|saved_alpha_dither
expr_stmt|;
name|dialog
operator|->
name|remove_dups
operator|=
name|saved_remove_dups
expr_stmt|;
name|dialog
operator|->
name|num_colors
operator|=
name|saved_num_colors
expr_stmt|;
name|dialog
operator|->
name|palette_type
operator|=
name|saved_palette_type
expr_stmt|;
name|dialog
operator|->
name|shell
operator|=
name|gimp_viewable_dialog_new
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Indexed Color Conversion"
argument_list|)
argument_list|,
literal|"gimp-image-convert-indexed"
argument_list|,
name|GIMP_STOCK_CONVERT_INDEXED
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
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|GTK_STOCK_OK
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
operator|->
name|shell
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|indexed_response
argument_list|)
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
operator|->
name|shell
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|indexed_destroy_callback
argument_list|)
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|main_vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
operator|->
name|shell
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|main_vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|main_vbox
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|_
argument_list|(
literal|"General Palette Options"
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
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
literal|2
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
comment|/*  'generate palette'  */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
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
name|hbox
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|toggle
operator|=
name|gtk_radio_button_new_with_label
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Generate Optimum Palette:"
argument_list|)
argument_list|)
expr_stmt|;
name|group
operator|=
name|gtk_radio_button_get_group
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|toggle
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
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|toggle
argument_list|)
argument_list|,
literal|"gimp-item-data"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|GIMP_MAKE_PALETTE
argument_list|)
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
name|gimp_radio_button_update
argument_list|)
argument_list|,
operator|&
name|dialog
operator|->
name|palette_type
argument_list|)
expr_stmt|;
if|if
condition|(
name|dialog
operator|->
name|num_colors
operator|==
literal|256
operator|&&
name|gimp_image_has_alpha
argument_list|(
name|gimage
argument_list|)
condition|)
block|{
name|dialog
operator|->
name|num_colors
operator|=
literal|255
expr_stmt|;
block|}
name|spinbutton
operator|=
name|gimp_spin_button_new
argument_list|(
operator|&
name|adjustment
argument_list|,
name|dialog
operator|->
name|num_colors
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
argument_list|,
literal|1
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
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_int_adjustment_update
argument_list|)
argument_list|,
operator|&
name|dialog
operator|->
name|num_colors
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Max. Number of Colors:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
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
name|gtk_widget_set_sensitive
argument_list|(
name|GTK_WIDGET
argument_list|(
name|spinbutton
argument_list|)
argument_list|,
name|dialog
operator|->
name|num_colors
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|GTK_WIDGET
argument_list|(
name|label
argument_list|)
argument_list|,
name|dialog
operator|->
name|num_colors
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|toggle
argument_list|)
argument_list|,
literal|"set_sensitive"
argument_list|,
name|spinbutton
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|spinbutton
argument_list|)
argument_list|,
literal|"set_sensitive"
argument_list|,
name|label
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|UserHasWebPal
condition|)
block|{
comment|/*  'web palette'        * Only presented as an option to the user if they do not        * already have the 'Web' GIMP palette installed on their        * system.        */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
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
name|toggle
operator|=
name|gtk_radio_button_new_with_label
argument_list|(
name|group
argument_list|,
name|_
argument_list|(
literal|"Use WWW-Optimized Palette"
argument_list|)
argument_list|)
expr_stmt|;
name|group
operator|=
name|gtk_radio_button_get_group
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|toggle
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
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|toggle
argument_list|)
argument_list|,
literal|"gimp-item-data"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|GIMP_WEB_PALETTE
argument_list|)
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
name|gimp_radio_button_update
argument_list|)
argument_list|,
operator|&
name|dialog
operator|->
name|palette_type
argument_list|)
expr_stmt|;
block|}
comment|/*  'mono palette'  */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
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
name|toggle
operator|=
name|gtk_radio_button_new_with_label
argument_list|(
name|group
argument_list|,
name|_
argument_list|(
literal|"Use Black and White (1-Bit) Palette"
argument_list|)
argument_list|)
expr_stmt|;
name|group
operator|=
name|gtk_radio_button_get_group
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|toggle
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
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|toggle
argument_list|)
argument_list|,
literal|"gimp-item-data"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|GIMP_MONO_PALETTE
argument_list|)
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
name|gimp_radio_button_update
argument_list|)
argument_list|,
operator|&
name|dialog
operator|->
name|palette_type
argument_list|)
expr_stmt|;
comment|/* 'custom' palette from dialog */
if|if
condition|(
name|dialog
operator|->
name|custom_palette_button
condition|)
block|{
name|GtkWidget
modifier|*
name|remove_toggle
decl_stmt|;
name|remove_toggle
operator|=
name|gtk_check_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Remove Unused Colors from Final Palette"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|remove_toggle
argument_list|)
argument_list|,
name|dialog
operator|->
name|remove_dups
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|remove_toggle
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_toggle_button_update
argument_list|)
argument_list|,
operator|&
name|dialog
operator|->
name|remove_dups
argument_list|)
expr_stmt|;
comment|/* 'custom' palette from dialog */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
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
name|toggle
operator|=
name|gtk_radio_button_new_with_label
argument_list|(
name|group
argument_list|,
name|_
argument_list|(
literal|"Use Custom Palette:"
argument_list|)
argument_list|)
expr_stmt|;
name|group
operator|=
name|gtk_radio_button_get_group
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|toggle
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
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|toggle
argument_list|)
argument_list|,
literal|"gimp-item-data"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|GIMP_CUSTOM_PALETTE
argument_list|)
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
name|gimp_radio_button_update
argument_list|)
argument_list|,
operator|&
name|dialog
operator|->
name|palette_type
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|toggle
argument_list|)
argument_list|,
literal|"set_sensitive"
argument_list|,
name|remove_toggle
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
operator|->
name|custom_palette_button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|indexed_custom_palette_button_callback
argument_list|)
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|dialog
operator|->
name|custom_palette_button
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
name|dialog
operator|->
name|custom_palette_button
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|remove_toggle
argument_list|,
name|dialog
operator|->
name|palette_type
operator|==
name|GIMP_CUSTOM_PALETTE
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|dialog
operator|->
name|custom_palette_button
argument_list|,
name|dialog
operator|->
name|palette_type
operator|==
name|GIMP_CUSTOM_PALETTE
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|toggle
argument_list|)
argument_list|,
literal|"set_sensitive"
argument_list|,
name|remove_toggle
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|remove_toggle
argument_list|)
argument_list|,
literal|"set_sensitive"
argument_list|,
name|dialog
operator|->
name|custom_palette_button
argument_list|)
expr_stmt|;
comment|/*  add the remove-duplicates toggle  */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
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
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|remove_toggle
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|20
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|remove_toggle
argument_list|)
expr_stmt|;
block|}
name|gimp_radio_group_set_active
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|dialog
operator|->
name|palette_type
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  the dither type  */
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|_
argument_list|(
literal|"Dithering Options"
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
name|gimp_enum_radio_box_new
argument_list|(
name|GIMP_TYPE_CONVERT_DITHER_TYPE
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_radio_button_update
argument_list|)
argument_list|,
operator|&
name|dialog
operator|->
name|dither_type
argument_list|,
operator|&
name|toggle
argument_list|)
expr_stmt|;
name|gimp_radio_group_set_active
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|dialog
operator|->
name|dither_type
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
literal|2
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
comment|/*  the alpha-dither toggle  */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
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
name|toggle
operator|=
name|gtk_check_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Enable Dithering of Transparency"
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
name|dialog
operator|->
name|alpha_dither
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
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
name|dialog
operator|->
name|alpha_dither
argument_list|)
expr_stmt|;
comment|/* if the image isn't non-alpha/layered, set the default number of      colours to one less than max, to leave room for a transparent index      for transparent/animated GIFs */
if|if
condition|(
name|gimp_image_has_alpha
argument_list|(
name|gimage
argument_list|)
condition|)
block|{
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|_
argument_list|(
literal|"[ Warning ]"
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
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
literal|2
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
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"You are attempting to convert an image with an alpha channel "
literal|"to indexed colors.\n"
literal|"Do not generate a palette of more than 255 colors if you "
literal|"intend to create a transparent or animated GIF file."
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_label_set_justify
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|GTK_JUSTIFY_LEFT
argument_list|)
expr_stmt|;
name|gtk_label_set_line_wrap
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|label
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_show
argument_list|(
name|dialog
operator|->
name|shell
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|build_palette_button (Gimp * gimp)
name|build_palette_button
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|GimpPalette
modifier|*
name|palette
decl_stmt|;
name|GimpPalette
modifier|*
name|theWebPalette
init|=
name|NULL
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gint
name|default_palette
decl_stmt|;
name|UserHasWebPal
operator|=
name|FALSE
expr_stmt|;
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|gimp
operator|->
name|palette_factory
operator|->
name|container
argument_list|)
operator|->
name|list
expr_stmt|;
if|if
condition|(
operator|!
name|list
condition|)
block|{
return|return
name|NULL
return|;
block|}
for|for
control|(
name|i
operator|=
literal|0
operator|,
name|default_palette
operator|=
operator|-
literal|1
init|;
name|list
condition|;
name|i
operator|++
operator|,
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|palette
operator|=
operator|(
name|GimpPalette
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
comment|/* Preferentially, the initial default is 'Web' if available */
if|if
condition|(
name|theWebPalette
operator|==
name|NULL
operator|&&
name|g_ascii_strcasecmp
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|palette
argument_list|)
operator|->
name|name
argument_list|,
literal|"Web"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|theWebPalette
operator|=
name|palette
expr_stmt|;
name|UserHasWebPal
operator|=
name|TRUE
expr_stmt|;
block|}
comment|/* We can't dither to> 256 colors */
if|if
condition|(
name|palette
operator|->
name|n_colors
operator|<=
literal|256
condition|)
block|{
if|if
condition|(
name|theCustomPalette
operator|==
name|palette
condition|)
block|{
name|default_palette
operator|=
name|i
expr_stmt|;
block|}
block|}
block|}
comment|/* default to first one with<= 256 colors    * (only used if 'web' palette not available)    */
if|if
condition|(
name|default_palette
operator|==
operator|-
literal|1
condition|)
block|{
if|if
condition|(
name|theWebPalette
condition|)
block|{
name|theCustomPalette
operator|=
name|theWebPalette
expr_stmt|;
name|default_palette
operator|=
literal|1
expr_stmt|;
comment|/*  dummy value  */
block|}
else|else
block|{
for|for
control|(
name|i
operator|=
literal|0
operator|,
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|gimp
operator|->
name|palette_factory
operator|->
name|container
argument_list|)
operator|->
name|list
init|;
name|list
operator|&&
name|default_palette
operator|==
operator|-
literal|1
condition|;
name|i
operator|++
operator|,
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|palette
operator|=
operator|(
name|GimpPalette
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|palette
operator|->
name|n_colors
operator|<=
literal|256
condition|)
block|{
name|theCustomPalette
operator|=
name|palette
expr_stmt|;
name|default_palette
operator|=
name|i
expr_stmt|;
block|}
block|}
block|}
block|}
if|if
condition|(
name|default_palette
operator|==
operator|-
literal|1
condition|)
return|return
name|NULL
return|;
else|else
return|return
name|gtk_button_new_with_label
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|theCustomPalette
argument_list|)
operator|->
name|name
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|indexed_response (GtkWidget * widget,gint response_id,IndexedDialog * dialog)
name|indexed_response
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
name|dialog
parameter_list|)
block|{
if|if
condition|(
name|response_id
operator|==
name|GTK_RESPONSE_OK
condition|)
block|{
comment|/*  Convert the image to indexed color  */
name|gimp_image_convert
argument_list|(
name|dialog
operator|->
name|gimage
argument_list|,
name|GIMP_INDEXED
argument_list|,
name|dialog
operator|->
name|num_colors
argument_list|,
name|dialog
operator|->
name|dither_type
argument_list|,
name|dialog
operator|->
name|alpha_dither
argument_list|,
name|dialog
operator|->
name|remove_dups
argument_list|,
name|dialog
operator|->
name|palette_type
argument_list|,
name|theCustomPalette
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|dialog
operator|->
name|gimage
argument_list|)
expr_stmt|;
comment|/* Save defaults for next time */
name|saved_dither_type
operator|=
name|dialog
operator|->
name|dither_type
expr_stmt|;
name|saved_alpha_dither
operator|=
name|dialog
operator|->
name|alpha_dither
expr_stmt|;
name|saved_remove_dups
operator|=
name|dialog
operator|->
name|remove_dups
expr_stmt|;
name|saved_num_colors
operator|=
name|dialog
operator|->
name|num_colors
expr_stmt|;
name|saved_palette_type
operator|=
name|dialog
operator|->
name|palette_type
expr_stmt|;
block|}
name|gtk_widget_destroy
argument_list|(
name|dialog
operator|->
name|shell
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|indexed_destroy_callback (GtkWidget * widget,IndexedDialog * dialog)
name|indexed_destroy_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|IndexedDialog
modifier|*
name|dialog
parameter_list|)
block|{
if|if
condition|(
name|dialog
operator|->
name|palette_select
condition|)
name|gtk_widget_destroy
argument_list|(
name|dialog
operator|->
name|palette_select
operator|->
name|shell
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|indexed_palette_select_destroy_callback (GtkWidget * widget,IndexedDialog * dialog)
name|indexed_palette_select_destroy_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|IndexedDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|dialog
operator|->
name|palette_select
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|indexed_palette_select_palette (GimpContext * context,GimpPalette * palette,IndexedDialog * dialog)
name|indexed_palette_select_palette
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
name|dialog
parameter_list|)
block|{
if|if
condition|(
name|palette
operator|&&
name|palette
operator|->
name|n_colors
operator|<=
literal|256
condition|)
block|{
name|theCustomPalette
operator|=
name|palette
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|GTK_BIN
argument_list|(
name|dialog
operator|->
name|custom_palette_button
argument_list|)
operator|->
name|child
argument_list|)
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|theCustomPalette
argument_list|)
operator|->
name|name
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|indexed_custom_palette_button_callback (GtkWidget * widget,IndexedDialog * dialog)
name|indexed_custom_palette_button_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|IndexedDialog
modifier|*
name|dialog
parameter_list|)
block|{
if|if
condition|(
name|dialog
operator|->
name|palette_select
operator|==
name|NULL
condition|)
block|{
name|dialog
operator|->
name|palette_select
operator|=
name|palette_select_new
argument_list|(
name|dialog
operator|->
name|gimage
operator|->
name|gimp
argument_list|,
name|_
argument_list|(
literal|"Select Custom Palette"
argument_list|)
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|theCustomPalette
argument_list|)
operator|->
name|name
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
operator|->
name|palette_select
operator|->
name|shell
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|indexed_palette_select_destroy_callback
argument_list|)
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
operator|->
name|palette_select
operator|->
name|context
argument_list|,
literal|"palette_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|indexed_palette_select_palette
argument_list|)
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
operator|->
name|palette_select
operator|->
name|shell
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

