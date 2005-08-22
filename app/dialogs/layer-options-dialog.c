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
file|"libgimpbase/gimpbase.h"
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
file|"text/gimptext.h"
end_include

begin_include
include|#
directive|include
file|"text/gimptextlayer.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpviewabledialog.h"
end_include

begin_include
include|#
directive|include
file|"layer-options-dialog.h"
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
name|void
name|layer_options_dialog_toggle_rename
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|LayerOptionsDialog
modifier|*
name|options
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|LayerOptionsDialog
modifier|*
DECL|function|layer_options_dialog_new (GimpImage * gimage,GimpContext * context,GimpLayer * layer,GtkWidget * parent,const gchar * layer_name,GimpFillType layer_fill_type,const gchar * title,const gchar * role,const gchar * stock_id,const gchar * desc,const gchar * help_id)
name|layer_options_dialog_new
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|,
specifier|const
name|gchar
modifier|*
name|layer_name
parameter_list|,
name|GimpFillType
name|layer_fill_type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|role
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|desc
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|)
block|{
name|LayerOptionsDialog
modifier|*
name|options
decl_stmt|;
name|GimpViewable
modifier|*
name|viewable
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|table
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
name|button
decl_stmt|;
name|options
operator|=
name|g_new0
argument_list|(
name|LayerOptionsDialog
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|options
operator|->
name|gimage
operator|=
name|gimage
expr_stmt|;
name|options
operator|->
name|context
operator|=
name|context
expr_stmt|;
name|options
operator|->
name|layer
operator|=
name|layer
expr_stmt|;
name|options
operator|->
name|fill_type
operator|=
name|layer_fill_type
expr_stmt|;
if|if
condition|(
name|layer
condition|)
name|viewable
operator|=
name|GIMP_VIEWABLE
argument_list|(
name|layer
argument_list|)
expr_stmt|;
else|else
name|viewable
operator|=
name|GIMP_VIEWABLE
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|options
operator|->
name|dialog
operator|=
name|gimp_viewable_dialog_new
argument_list|(
name|viewable
argument_list|,
name|title
argument_list|,
name|role
argument_list|,
name|stock_id
argument_list|,
name|desc
argument_list|,
name|parent
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|help_id
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
name|g_object_weak_ref
argument_list|(
name|G_OBJECT
argument_list|(
name|options
operator|->
name|dialog
argument_list|)
argument_list|,
operator|(
name|GWeakNotify
operator|)
name|g_free
argument_list|,
name|options
argument_list|)
expr_stmt|;
name|gtk_dialog_set_alternative_button_order
argument_list|(
name|GTK_DIALOG
argument_list|(
name|options
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
name|options
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
name|table
operator|=
name|gtk_table_new
argument_list|(
name|layer
condition|?
literal|1
else|:
literal|3
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
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
comment|/*  The name label and entry  */
name|options
operator|->
name|name_entry
operator|=
name|gtk_entry_new
argument_list|()
expr_stmt|;
name|gimp_table_attach_aligned
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Layer _name:"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|,
name|options
operator|->
name|name_entry
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_entry_set_activates_default
argument_list|(
name|GTK_ENTRY
argument_list|(
name|options
operator|->
name|name_entry
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|options
operator|->
name|name_entry
argument_list|)
argument_list|,
name|layer_name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|layer
condition|)
block|{
comment|/*  The size labels  */
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Width:"
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
literal|0
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
name|GTK_SHRINK
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Height:"
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
literal|0
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|3
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
name|GTK_SHRINK
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
comment|/*  The size sizeentry  */
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
name|options
operator|->
name|size_se
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
name|options
operator|->
name|size_se
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
name|options
operator|->
name|size_se
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
name|options
operator|->
name|size_se
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
name|options
operator|->
name|size_se
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
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|options
operator|->
name|size_se
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|1
argument_list|,
literal|3
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|options
operator|->
name|size_se
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_unit
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|options
operator|->
name|size_se
argument_list|)
argument_list|,
name|GIMP_UNIT_PIXEL
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_resolution
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|options
operator|->
name|size_se
argument_list|)
argument_list|,
literal|0
argument_list|,
name|gimage
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
name|options
operator|->
name|size_se
argument_list|)
argument_list|,
literal|1
argument_list|,
name|gimage
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
name|options
operator|->
name|size_se
argument_list|)
argument_list|,
literal|0
argument_list|,
name|GIMP_MIN_IMAGE_SIZE
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval_boundaries
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|options
operator|->
name|size_se
argument_list|)
argument_list|,
literal|1
argument_list|,
name|GIMP_MIN_IMAGE_SIZE
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_size
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|options
operator|->
name|size_se
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|gimage
operator|->
name|width
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_size
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|options
operator|->
name|size_se
argument_list|)
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
name|gimage
operator|->
name|height
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|options
operator|->
name|size_se
argument_list|)
argument_list|,
literal|0
argument_list|,
name|gimage
operator|->
name|width
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|options
operator|->
name|size_se
argument_list|)
argument_list|,
literal|1
argument_list|,
name|gimage
operator|->
name|height
argument_list|)
expr_stmt|;
comment|/*  The radio frame  */
name|frame
operator|=
name|gimp_enum_radio_frame_new_with_range
argument_list|(
name|GIMP_TYPE_FILL_TYPE
argument_list|,
name|GIMP_FOREGROUND_FILL
argument_list|,
name|GIMP_TRANSPARENT_FILL
argument_list|,
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Layer Fill Type"
argument_list|)
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_radio_button_update
argument_list|)
argument_list|,
operator|&
name|options
operator|->
name|fill_type
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
name|options
operator|->
name|fill_type
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
block|}
else|else
block|{
comment|/*  For text layers add a toggle to control "auto-rename"  */
if|if
condition|(
name|gimp_drawable_is_text_layer
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
condition|)
block|{
name|options
operator|->
name|rename_toggle
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"Set Name from _Text"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|options
operator|->
name|rename_toggle
argument_list|)
argument_list|,
name|GIMP_TEXT_LAYER
argument_list|(
name|layer
argument_list|)
operator|->
name|auto_rename
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|options
operator|->
name|rename_toggle
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|options
operator|->
name|rename_toggle
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|options
operator|->
name|rename_toggle
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|layer_options_dialog_toggle_rename
argument_list|)
argument_list|,
name|options
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|options
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|layer_options_dialog_toggle_rename (GtkWidget * widget,LayerOptionsDialog * options)
name|layer_options_dialog_toggle_rename
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|LayerOptionsDialog
modifier|*
name|options
parameter_list|)
block|{
if|if
condition|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|widget
argument_list|)
operator|->
name|active
operator|&&
name|gimp_drawable_is_text_layer
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|options
operator|->
name|layer
argument_list|)
argument_list|)
condition|)
block|{
name|GimpTextLayer
modifier|*
name|text_layer
init|=
name|GIMP_TEXT_LAYER
argument_list|(
name|options
operator|->
name|layer
argument_list|)
decl_stmt|;
name|GimpText
modifier|*
name|text
init|=
name|gimp_text_layer_get_text
argument_list|(
name|text_layer
argument_list|)
decl_stmt|;
if|if
condition|(
name|text
operator|&&
name|text
operator|->
name|text
condition|)
block|{
name|gchar
modifier|*
name|name
init|=
name|gimp_utf8_strtrim
argument_list|(
name|text
operator|->
name|text
argument_list|,
literal|30
argument_list|)
decl_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|options
operator|->
name|name_entry
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

end_unit

