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
file|"core/gimpprogress.h"
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
file|"gimp-intl.h"
end_include

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2932c72c0108
block|{
DECL|member|dialog
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
DECL|member|image
name|GimpImage
modifier|*
name|image
decl_stmt|;
DECL|member|progress
name|GimpProgress
modifier|*
name|progress
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
DECL|member|custom_palette
name|GimpPalette
modifier|*
name|custom_palette
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
name|dialog
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
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|convert_dialog_palette_filter
parameter_list|(
specifier|const
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
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  defaults  */
end_comment

begin_decl_stmt
DECL|variable|saved_dither_type
specifier|static
name|GimpConvertDitherType
name|saved_dither_type
init|=
name|GIMP_NO_DITHER
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

begin_decl_stmt
DECL|variable|saved_palette
specifier|static
name|GimpPalette
modifier|*
name|saved_palette
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|convert_dialog_new (GimpImage * image,GtkWidget * parent,GimpProgress * progress)
name|convert_dialog_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|IndexedDialog
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
name|progress
operator|==
name|NULL
operator|||
name|GIMP_IS_PROGRESS
argument_list|(
name|progress
argument_list|)
argument_list|,
name|NULL
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
name|image
operator|=
name|image
expr_stmt|;
name|dialog
operator|->
name|progress
operator|=
name|progress
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
name|dialog
operator|=
name|gimp_viewable_dialog_new
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|image
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
name|NULL
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_dialog_add_button
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
operator|->
name|dialog
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"C_onvert"
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|)
expr_stmt|;
name|gtk_button_set_image
argument_list|(
name|GTK_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|gtk_image_new_from_stock
argument_list|(
name|GIMP_STOCK_CONVERT_INDEXED
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_dialog_set_alternative_button_order
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
operator|->
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
operator|->
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
operator|->
name|dialog
argument_list|)
argument_list|,
operator|(
name|GWeakNotify
operator|)
name|g_free
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
operator|->
name|dialog
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|convert_dialog_response
argument_list|)
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|palette_box
operator|=
name|convert_dialog_palette_box
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
name|main_vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
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
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
operator|->
name|dialog
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
comment|/*  palette  */
name|frame
operator|=
name|gimp_enum_radio_frame_new_with_range
argument_list|(
name|GIMP_TYPE_CONVERT_PALETTE_TYPE
argument_list|,
name|GIMP_MAKE_PALETTE
argument_list|,
name|palette_box
condition|?
name|GIMP_CUSTOM_PALETTE
else|:
name|GIMP_MONO_PALETTE
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
name|dialog
operator|->
name|palette_type
argument_list|,
operator|&
name|toggle
argument_list|)
expr_stmt|;
name|gimp_int_radio_group_set_active
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|,
name|dialog
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
name|gtk_hbox_new
argument_list|(
name|FALSE
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
name|GIMP_MAKE_PALETTE
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
name|dialog
operator|->
name|num_colors
operator|==
literal|256
operator|&&
name|gimp_image_has_alpha
argument_list|(
name|image
argument_list|)
condition|)
name|dialog
operator|->
name|num_colors
operator|=
literal|255
expr_stmt|;
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
name|dialog
operator|->
name|num_colors
argument_list|)
expr_stmt|;
comment|/*  custom palette  */
if|if
condition|(
name|palette_box
condition|)
block|{
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gimp_enum_radio_frame_add
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|vbox
argument_list|,
name|GIMP_CUSTOM_PALETTE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|palette_box
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
name|palette_box
argument_list|)
expr_stmt|;
name|toggle
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Remove unused colors "
literal|"from final palette"
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
name|remove_dups
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
name|dialog
operator|->
name|remove_dups
argument_list|)
expr_stmt|;
block|}
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
name|gtk_vbox_new
argument_list|(
name|FALSE
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
name|dialog
operator|->
name|dither_type
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_int_combo_box_get_active
argument_list|)
argument_list|,
operator|&
name|dialog
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
name|dialog
operator|->
name|alpha_dither
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
name|dialog
operator|->
name|alpha_dither
argument_list|)
expr_stmt|;
return|return
name|dialog
operator|->
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
DECL|function|convert_dialog_response (GtkWidget * widget,gint response_id,IndexedDialog * dialog)
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
name|GimpProgress
modifier|*
name|progress
decl_stmt|;
name|progress
operator|=
name|gimp_progress_start
argument_list|(
name|dialog
operator|->
name|progress
argument_list|,
name|_
argument_list|(
literal|"Converting to indexed"
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/*  Convert the image to indexed color  */
name|gimp_image_convert
argument_list|(
name|dialog
operator|->
name|image
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
name|dialog
operator|->
name|custom_palette
argument_list|,
name|progress
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
condition|)
name|gimp_progress_end
argument_list|(
name|progress
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|dialog
operator|->
name|image
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
name|saved_palette
operator|=
name|dialog
operator|->
name|custom_palette
expr_stmt|;
block|}
name|gtk_widget_destroy
argument_list|(
name|dialog
operator|->
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|convert_dialog_palette_box (IndexedDialog * dialog)
name|convert_dialog_palette_box
parameter_list|(
name|IndexedDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
init|=
name|dialog
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
name|palette
decl_stmt|;
name|GimpPalette
modifier|*
name|web_palette
init|=
name|NULL
decl_stmt|;
name|gboolean
name|default_found
init|=
name|FALSE
decl_stmt|;
comment|/* We can't dither to> 256 colors */
name|dialog
operator|->
name|container
operator|=
name|gimp_container_filter
argument_list|(
name|gimp
operator|->
name|palette_factory
operator|->
name|container
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
name|dialog
operator|->
name|container
argument_list|)
condition|)
block|{
name|g_object_unref
argument_list|(
name|dialog
operator|->
name|container
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|container
operator|=
name|NULL
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|dialog
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
name|g_object_weak_ref
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
operator|->
name|dialog
argument_list|)
argument_list|,
operator|(
name|GWeakNotify
operator|)
name|g_object_unref
argument_list|,
name|dialog
operator|->
name|context
argument_list|)
expr_stmt|;
name|g_object_weak_ref
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
operator|->
name|dialog
argument_list|)
argument_list|,
operator|(
name|GWeakNotify
operator|)
name|g_object_unref
argument_list|,
name|dialog
operator|->
name|container
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|dialog
operator|->
name|container
argument_list|)
operator|->
name|list
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
name|palette
operator|=
name|list
operator|->
name|data
expr_stmt|;
comment|/* Preferentially, the initial default is 'Web' if available */
if|if
condition|(
name|web_palette
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
name|web_palette
operator|=
name|palette
expr_stmt|;
block|}
if|if
condition|(
name|saved_palette
operator|==
name|palette
condition|)
block|{
name|dialog
operator|->
name|custom_palette
operator|=
name|saved_palette
expr_stmt|;
name|default_found
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
if|if
condition|(
operator|!
name|default_found
condition|)
block|{
if|if
condition|(
name|web_palette
condition|)
name|dialog
operator|->
name|custom_palette
operator|=
name|web_palette
expr_stmt|;
else|else
name|dialog
operator|->
name|custom_palette
operator|=
name|GIMP_LIST
argument_list|(
name|dialog
operator|->
name|container
argument_list|)
operator|->
name|list
operator|->
name|data
expr_stmt|;
block|}
name|gimp_context_set_palette
argument_list|(
name|dialog
operator|->
name|context
argument_list|,
name|dialog
operator|->
name|custom_palette
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
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
name|dialog
argument_list|)
expr_stmt|;
return|return
name|gimp_palette_box_new
argument_list|(
name|dialog
operator|->
name|container
argument_list|,
name|dialog
operator|->
name|context
argument_list|,
literal|4
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|convert_dialog_palette_filter (const GimpObject * object,gpointer user_data)
name|convert_dialog_palette_filter
parameter_list|(
specifier|const
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
name|palette
operator|->
name|n_colors
operator|>
literal|0
operator|&&
name|palette
operator|->
name|n_colors
operator|<=
literal|256
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|convert_dialog_palette_changed (GimpContext * context,GimpPalette * palette,IndexedDialog * dialog)
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
name|dialog
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
name|palette
operator|->
name|n_colors
operator|>
literal|256
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Cannot convert to a palette with more than 256 colors."
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|dialog
operator|->
name|custom_palette
operator|=
name|palette
expr_stmt|;
block|}
block|}
end_function

end_unit

