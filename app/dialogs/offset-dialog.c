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
file|"libgimpmath/gimpmath.h"
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
file|"core/gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable-offset.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayermask.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
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
file|"offset-dialog.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|WRAP_AROUND
define|#
directive|define
name|WRAP_AROUND
value|(1<< 3)
end_define

begin_define
DECL|macro|FILL_MASK
define|#
directive|define
name|FILL_MASK
value|(GIMP_OFFSET_BACKGROUND | GIMP_OFFSET_TRANSPARENT)
end_define

begin_typedef
DECL|typedef|OffsetDialog
typedef|typedef
name|struct
name|_OffsetDialog
name|OffsetDialog
typedef|;
end_typedef

begin_struct
DECL|struct|_OffsetDialog
struct|struct
name|_OffsetDialog
block|{
DECL|member|context
name|GimpContext
modifier|*
name|context
decl_stmt|;
DECL|member|dialog
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
DECL|member|off_se
name|GtkWidget
modifier|*
name|off_se
decl_stmt|;
DECL|member|fill_type
name|GimpOffsetType
name|fill_type
decl_stmt|;
DECL|member|image
name|GimpImage
modifier|*
name|image
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|offset_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|OffsetDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|offset_halfheight_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|OffsetDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|offset_dialog_new (GimpDrawable * drawable,GimpContext * context,GtkWidget * parent)
name|offset_dialog_new
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|)
block|{
name|OffsetDialog
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
name|button
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
name|radio_button
decl_stmt|;
name|GtkObject
modifier|*
name|adjustment
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|title
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DRAWABLE
argument_list|(
name|drawable
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
name|dialog
operator|=
name|g_new0
argument_list|(
name|OffsetDialog
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|context
operator|=
name|context
expr_stmt|;
name|dialog
operator|->
name|fill_type
operator|=
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
operator||
name|WRAP_AROUND
expr_stmt|;
name|dialog
operator|->
name|image
operator|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_LAYER
argument_list|(
name|drawable
argument_list|)
condition|)
name|title
operator|=
name|_
argument_list|(
literal|"Offset Layer"
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|GIMP_IS_LAYER_MASK
argument_list|(
name|drawable
argument_list|)
condition|)
name|title
operator|=
name|_
argument_list|(
literal|"Offset Layer Mask"
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|GIMP_IS_CHANNEL
argument_list|(
name|drawable
argument_list|)
condition|)
name|title
operator|=
name|_
argument_list|(
literal|"Offset Channel"
argument_list|)
expr_stmt|;
else|else
name|g_warning
argument_list|(
literal|"%s: unexpected drawable type"
argument_list|,
name|G_STRFUNC
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|dialog
operator|=
name|gimp_viewable_dialog_new
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|context
argument_list|,
name|_
argument_list|(
literal|"Offset"
argument_list|)
argument_list|,
literal|"gimp-drawable-offset"
argument_list|,
name|GIMP_STOCK_TOOL_MOVE
argument_list|,
name|title
argument_list|,
name|parent
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_LAYER_OFFSET
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
comment|/*  offset, used as a verb  */
name|_
argument_list|(
literal|"_Offset"
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
name|offset_response
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
comment|/*  The offset frame  */
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Offset"
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
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
literal|0
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
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
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
literal|6
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
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
name|spinbutton
operator|=
name|gimp_spin_button_new
argument_list|(
operator|&
name|adjustment
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|10
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_entry_set_width_chars
argument_list|(
name|GTK_ENTRY
argument_list|(
name|spinbutton
argument_list|)
argument_list|,
literal|10
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|off_se
operator|=
name|gimp_size_entry_new
argument_list|(
literal|1
argument_list|,
name|GIMP_UNIT_PIXEL
argument_list|,
literal|"%a"
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
literal|10
argument_list|,
name|GIMP_SIZE_ENTRY_UPDATE_SIZE
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|dialog
operator|->
name|off_se
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|dialog
operator|->
name|off_se
argument_list|)
argument_list|,
literal|1
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|dialog
operator|->
name|off_se
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gimp_size_entry_add_field
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|dialog
operator|->
name|off_se
argument_list|)
argument_list|,
name|GTK_SPIN_BUTTON
argument_list|(
name|spinbutton
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|dialog
operator|->
name|off_se
argument_list|)
argument_list|,
name|spinbutton
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|spinbutton
argument_list|)
expr_stmt|;
name|gimp_size_entry_attach_label
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|dialog
operator|->
name|off_se
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"_X:"
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gimp_size_entry_attach_label
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|dialog
operator|->
name|off_se
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"_Y:"
argument_list|)
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|dialog
operator|->
name|off_se
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
name|dialog
operator|->
name|off_se
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_unit
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|dialog
operator|->
name|off_se
argument_list|)
argument_list|,
name|GIMP_UNIT_PIXEL
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_resolution
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|dialog
operator|->
name|off_se
argument_list|)
argument_list|,
literal|0
argument_list|,
name|dialog
operator|->
name|image
operator|->
name|xresolution
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_resolution
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|dialog
operator|->
name|off_se
argument_list|)
argument_list|,
literal|1
argument_list|,
name|dialog
operator|->
name|image
operator|->
name|yresolution
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval_boundaries
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|dialog
operator|->
name|off_se
argument_list|)
argument_list|,
literal|0
argument_list|,
operator|-
name|dialog
operator|->
name|image
operator|->
name|width
argument_list|,
name|dialog
operator|->
name|image
operator|->
name|width
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval_boundaries
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|dialog
operator|->
name|off_se
argument_list|)
argument_list|,
literal|1
argument_list|,
operator|-
name|dialog
operator|->
name|image
operator|->
name|height
argument_list|,
name|dialog
operator|->
name|image
operator|->
name|height
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_size
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|dialog
operator|->
name|off_se
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|dialog
operator|->
name|image
operator|->
name|width
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_size
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|dialog
operator|->
name|off_se
argument_list|)
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
name|dialog
operator|->
name|image
operator|->
name|height
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|dialog
operator|->
name|off_se
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|dialog
operator|->
name|off_se
argument_list|)
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"Offset by  x/_2, y/2"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
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
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|offset_halfheight_callback
argument_list|)
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
comment|/*  The edge behavior frame  */
name|frame
operator|=
name|gimp_int_radio_group_new
argument_list|(
name|TRUE
argument_list|,
name|_
argument_list|(
literal|"Edge Behavior"
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
name|fill_type
argument_list|,
name|dialog
operator|->
name|fill_type
argument_list|,
name|_
argument_list|(
literal|"_Wrap around"
argument_list|)
argument_list|,
name|WRAP_AROUND
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Fill with _background color"
argument_list|)
argument_list|,
name|GIMP_OFFSET_BACKGROUND
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Make _transparent"
argument_list|)
argument_list|,
name|GIMP_OFFSET_TRANSPARENT
argument_list|,
operator|&
name|radio_button
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
condition|)
name|gtk_widget_set_sensitive
argument_list|(
name|radio_button
argument_list|,
name|FALSE
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
DECL|function|offset_response (GtkWidget * widget,gint response_id,OffsetDialog * dialog)
name|offset_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|OffsetDialog
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
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|gint
name|offset_x
decl_stmt|;
name|gint
name|offset_y
decl_stmt|;
if|if
condition|(
operator|(
name|image
operator|=
name|dialog
operator|->
name|image
operator|)
operator|!=
name|NULL
condition|)
block|{
name|drawable
operator|=
name|gimp_image_active_drawable
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|offset_x
operator|=
name|RINT
argument_list|(
name|gimp_size_entry_get_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|dialog
operator|->
name|off_se
argument_list|)
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
name|offset_y
operator|=
name|RINT
argument_list|(
name|gimp_size_entry_get_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|dialog
operator|->
name|off_se
argument_list|)
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_drawable_offset
argument_list|(
name|drawable
argument_list|,
name|dialog
operator|->
name|context
argument_list|,
name|dialog
operator|->
name|fill_type
operator|&
name|WRAP_AROUND
condition|?
name|TRUE
else|:
name|FALSE
argument_list|,
name|dialog
operator|->
name|fill_type
operator|&
name|FILL_MASK
argument_list|,
name|offset_x
argument_list|,
name|offset_y
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
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
name|void
DECL|function|offset_halfheight_callback (GtkWidget * widget,OffsetDialog * dialog)
name|offset_halfheight_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|OffsetDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|dialog
operator|->
name|image
decl_stmt|;
name|gimp_size_entry_set_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|dialog
operator|->
name|off_se
argument_list|)
argument_list|,
literal|0
argument_list|,
name|image
operator|->
name|width
operator|/
literal|2
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|dialog
operator|->
name|off_se
argument_list|)
argument_list|,
literal|1
argument_list|,
name|image
operator|->
name|height
operator|/
literal|2
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

