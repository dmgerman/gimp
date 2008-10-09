begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"core/gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcontainercombobox.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcontainerview.h"
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
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"layer-add-mask-dialog.h"
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
name|layer_add_mask_dialog_channel_selected
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|insert_data
parameter_list|,
name|LayerAddMaskDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|layer_add_mask_dialog_free
parameter_list|(
name|LayerAddMaskDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|LayerAddMaskDialog
modifier|*
DECL|function|layer_add_mask_dialog_new (GimpLayer * layer,GimpContext * context,GtkWidget * parent,GimpAddMaskType add_mask_type,gboolean invert)
name|layer_add_mask_dialog_new
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|,
name|GimpAddMaskType
name|add_mask_type
parameter_list|,
name|gboolean
name|invert
parameter_list|)
block|{
name|LayerAddMaskDialog
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|combo
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GimpChannel
modifier|*
name|channel
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_LAYER
argument_list|(
name|layer
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
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|g_slice_new0
argument_list|(
name|LayerAddMaskDialog
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|layer
operator|=
name|layer
expr_stmt|;
name|dialog
operator|->
name|add_mask_type
operator|=
name|add_mask_type
expr_stmt|;
name|dialog
operator|->
name|invert
operator|=
name|invert
expr_stmt|;
name|dialog
operator|->
name|dialog
operator|=
name|gimp_viewable_dialog_new
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|layer
argument_list|)
argument_list|,
name|context
argument_list|,
name|_
argument_list|(
literal|"Add Layer Mask"
argument_list|)
argument_list|,
literal|"gimp-layer-add-mask"
argument_list|,
name|GIMP_STOCK_LAYER_MASK
argument_list|,
name|_
argument_list|(
literal|"Add a Mask to the Layer"
argument_list|)
argument_list|,
name|parent
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_LAYER_MASK_ADD
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|GTK_STOCK_ADD
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
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
name|layer_add_mask_dialog_free
argument_list|,
name|dialog
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
name|vbox
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
name|vbox
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
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_enum_radio_frame_new
argument_list|(
name|GIMP_TYPE_ADD_MASK_TYPE
argument_list|,
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Initialize Layer Mask to:"
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
name|add_mask_type
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
name|dialog
operator|->
name|add_mask_type
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
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
name|combo
operator|=
name|gimp_container_combo_box_new
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
operator|->
name|image
operator|->
name|channels
argument_list|,
name|context
argument_list|,
name|GIMP_VIEW_SIZE_SMALL
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gimp_enum_radio_frame_add
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|combo
argument_list|,
name|GIMP_ADD_CHANNEL_MASK
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|combo
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|combo
argument_list|,
literal|"select-item"
argument_list|,
name|G_CALLBACK
argument_list|(
name|layer_add_mask_dialog_channel_selected
argument_list|)
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|channel
operator|=
name|gimp_image_get_active_channel
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
operator|->
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|channel
condition|)
name|channel
operator|=
name|GIMP_CHANNEL
argument_list|(
name|gimp_container_get_first_child
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
operator|->
name|image
operator|->
name|channels
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_container_view_select_item
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|combo
argument_list|)
argument_list|,
name|GIMP_VIEWABLE
argument_list|(
name|channel
argument_list|)
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"In_vert mask"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|dialog
operator|->
name|invert
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|button
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
name|button
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|button
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
name|invert
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
name|gboolean
DECL|function|layer_add_mask_dialog_channel_selected (GimpContainerView * view,GimpViewable * viewable,gpointer insert_data,LayerAddMaskDialog * dialog)
name|layer_add_mask_dialog_channel_selected
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|insert_data
parameter_list|,
name|LayerAddMaskDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|dialog
operator|->
name|channel
operator|=
name|GIMP_CHANNEL
argument_list|(
name|viewable
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|layer_add_mask_dialog_free (LayerAddMaskDialog * dialog)
name|layer_add_mask_dialog_free
parameter_list|(
name|LayerAddMaskDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|g_slice_free
argument_list|(
name|LayerAddMaskDialog
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

