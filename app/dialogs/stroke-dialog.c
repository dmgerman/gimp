begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Copyright (C) 2003  Henrik Brix Andersen<brix@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpconfig/gimpconfig.h"
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
file|"core/gimppaintinfo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpstrokedesc.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpstrokeoptions.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
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
file|"widgets/gimpviewabledialog.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpstrokeeditor.h"
end_include

begin_include
include|#
directive|include
file|"stroke-dialog.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|RESPONSE_RESET
define|#
directive|define
name|RESPONSE_RESET
value|1
end_define

begin_comment
comment|/*  local functions  */
end_comment

begin_function_decl
specifier|static
name|void
name|stroke_dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|GtkWidget
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|stroke_dialog_paint_info_selected
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
name|GimpStrokeDesc
modifier|*
name|desc
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public function  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|stroke_dialog_new (GimpItem * item,GimpContext * context,const gchar * title,const gchar * stock_id,const gchar * help_id,GtkWidget * parent)
name|stroke_dialog_new
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|)
block|{
name|GimpStrokeDesc
modifier|*
name|desc
decl_stmt|;
name|GimpStrokeDesc
modifier|*
name|saved_desc
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|main_vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|radio_box
decl_stmt|;
name|GtkWidget
modifier|*
name|libart_radio
decl_stmt|;
name|GtkWidget
modifier|*
name|paint_radio
decl_stmt|;
name|GSList
modifier|*
name|group
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_ITEM
argument_list|(
name|item
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
name|stock_id
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|help_id
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|parent
operator|==
name|NULL
operator|||
name|GTK_IS_WIDGET
argument_list|(
name|parent
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_item_get_image
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|desc
operator|=
name|gimp_stroke_desc_new
argument_list|(
name|context
operator|->
name|gimp
argument_list|,
name|context
argument_list|)
expr_stmt|;
name|saved_desc
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|context
operator|->
name|gimp
argument_list|)
argument_list|,
literal|"saved-stroke-desc"
argument_list|)
expr_stmt|;
if|if
condition|(
name|saved_desc
condition|)
name|gimp_config_sync
argument_list|(
name|G_OBJECT
argument_list|(
name|saved_desc
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|desc
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|gimp_viewable_dialog_new
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|item
argument_list|)
argument_list|,
name|context
argument_list|,
name|title
argument_list|,
literal|"gimp-stroke-options"
argument_list|,
name|stock_id
argument_list|,
name|_
argument_list|(
literal|"Choose Stroke Style"
argument_list|)
argument_list|,
name|parent
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|help_id
argument_list|,
name|GIMP_STOCK_RESET
argument_list|,
name|RESPONSE_RESET
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|stock_id
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
name|RESPONSE_RESET
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
name|g_signal_connect
argument_list|(
name|dialog
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|stroke_dialog_response
argument_list|)
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimp-item"
argument_list|,
name|item
argument_list|)
expr_stmt|;
name|g_object_set_data_full
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimp-stroke-desc"
argument_list|,
name|desc
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_object_unref
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
name|radio_box
operator|=
name|gimp_prop_enum_radio_box_new
argument_list|(
name|G_OBJECT
argument_list|(
name|desc
argument_list|)
argument_list|,
literal|"method"
argument_list|,
operator|-
literal|1
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|group
operator|=
name|gtk_radio_button_get_group
argument_list|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|radio_box
argument_list|)
argument_list|,
literal|"radio-button"
argument_list|)
argument_list|)
expr_stmt|;
name|libart_radio
operator|=
name|g_object_ref
argument_list|(
name|group
operator|->
name|next
operator|->
name|data
argument_list|)
expr_stmt|;
name|gtk_container_remove
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|radio_box
argument_list|)
argument_list|,
name|libart_radio
argument_list|)
expr_stmt|;
name|paint_radio
operator|=
name|g_object_ref
argument_list|(
name|group
operator|->
name|data
argument_list|)
expr_stmt|;
name|gtk_container_remove
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|radio_box
argument_list|)
argument_list|,
name|paint_radio
argument_list|)
expr_stmt|;
name|g_object_ref_sink
argument_list|(
name|radio_box
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|radio_box
argument_list|)
expr_stmt|;
block|{
name|PangoFontDescription
modifier|*
name|font_desc
decl_stmt|;
name|font_desc
operator|=
name|pango_font_description_new
argument_list|()
expr_stmt|;
name|pango_font_description_set_weight
argument_list|(
name|font_desc
argument_list|,
name|PANGO_WEIGHT_BOLD
argument_list|)
expr_stmt|;
name|gtk_widget_modify_font
argument_list|(
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|libart_radio
argument_list|)
argument_list|)
argument_list|,
name|font_desc
argument_list|)
expr_stmt|;
name|gtk_widget_modify_font
argument_list|(
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|paint_radio
argument_list|)
argument_list|)
argument_list|,
name|font_desc
argument_list|)
expr_stmt|;
name|pango_font_description_free
argument_list|(
name|font_desc
argument_list|)
expr_stmt|;
block|}
comment|/*  the stroke frame  */
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|NULL
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
name|gtk_frame_set_label_widget
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|libart_radio
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|libart_radio
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|libart_radio
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_toggle_button_sensitive_update
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|{
name|GtkWidget
modifier|*
name|stroke_editor
decl_stmt|;
name|gdouble
name|xres
decl_stmt|;
name|gdouble
name|yres
decl_stmt|;
name|gimp_image_get_resolution
argument_list|(
name|image
argument_list|,
operator|&
name|xres
argument_list|,
operator|&
name|yres
argument_list|)
expr_stmt|;
name|stroke_editor
operator|=
name|gimp_stroke_editor_new
argument_list|(
name|desc
operator|->
name|stroke_options
argument_list|,
name|yres
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|stroke_editor
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|stroke_editor
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|stroke_editor
argument_list|,
name|desc
operator|->
name|method
operator|==
name|GIMP_STROKE_METHOD_LIBART
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|libart_radio
argument_list|)
argument_list|,
literal|"set_sensitive"
argument_list|,
name|stroke_editor
argument_list|)
expr_stmt|;
block|}
comment|/*  the paint tool frame  */
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|NULL
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
name|gtk_frame_set_label_widget
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|paint_radio
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|paint_radio
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|paint_radio
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_toggle_button_sensitive_update
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|{
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
name|GtkWidget
modifier|*
name|combo
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
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
name|gtk_widget_set_sensitive
argument_list|(
name|vbox
argument_list|,
name|desc
operator|->
name|method
operator|==
name|GIMP_STROKE_METHOD_PAINT_CORE
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|paint_radio
argument_list|)
argument_list|,
literal|"set_sensitive"
argument_list|,
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
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Paint tool:"
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
name|gimp_container_combo_box_new
argument_list|(
name|image
operator|->
name|gimp
operator|->
name|paint_info_list
argument_list|,
name|context
argument_list|,
literal|16
argument_list|,
literal|0
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
name|desc
operator|->
name|paint_info
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
name|g_signal_connect
argument_list|(
name|combo
argument_list|,
literal|"select-item"
argument_list|,
name|G_CALLBACK
argument_list|(
name|stroke_dialog_paint_info_selected
argument_list|)
argument_list|,
name|desc
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimp-tool-menu"
argument_list|,
name|combo
argument_list|)
expr_stmt|;
name|button
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|G_OBJECT
argument_list|(
name|desc
argument_list|)
argument_list|,
literal|"emulate-brush-dynamics"
argument_list|,
name|_
argument_list|(
literal|"_Emulate brush dynamics"
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
block|}
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
DECL|function|stroke_dialog_response (GtkWidget * widget,gint response_id,GtkWidget * dialog)
name|stroke_dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|GtkWidget
modifier|*
name|dialog
parameter_list|)
block|{
name|GimpStrokeDesc
modifier|*
name|desc
decl_stmt|;
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|item
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimp-item"
argument_list|)
expr_stmt|;
name|desc
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimp-stroke-desc"
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_item_get_image
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|context
operator|=
name|GIMP_VIEWABLE_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|context
expr_stmt|;
switch|switch
condition|(
name|response_id
condition|)
block|{
case|case
name|RESPONSE_RESET
case|:
block|{
name|GimpToolInfo
modifier|*
name|tool_info
init|=
name|gimp_context_get_tool
argument_list|(
name|context
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|combo
init|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimp-tool-menu"
argument_list|)
decl_stmt|;
empty_stmt|;
name|gimp_config_reset
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|desc
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
name|tool_info
operator|->
name|paint_info
argument_list|)
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GTK_RESPONSE_OK
case|:
block|{
name|GimpDrawable
modifier|*
name|drawable
init|=
name|gimp_image_get_active_drawable
argument_list|(
name|image
argument_list|)
decl_stmt|;
name|GimpStrokeDesc
modifier|*
name|saved_desc
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|drawable
condition|)
block|{
name|gimp_message
argument_list|(
name|context
operator|->
name|gimp
argument_list|,
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
name|GIMP_MESSAGE_WARNING
argument_list|,
name|_
argument_list|(
literal|"There is no active layer or channel "
literal|"to stroke to."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|saved_desc
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|context
operator|->
name|gimp
argument_list|)
argument_list|,
literal|"saved-stroke-desc"
argument_list|)
expr_stmt|;
if|if
condition|(
name|saved_desc
condition|)
name|g_object_ref
argument_list|(
name|saved_desc
argument_list|)
expr_stmt|;
else|else
name|saved_desc
operator|=
name|gimp_stroke_desc_new
argument_list|(
name|context
operator|->
name|gimp
argument_list|,
name|context
argument_list|)
expr_stmt|;
name|gimp_config_sync
argument_list|(
name|G_OBJECT
argument_list|(
name|desc
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|saved_desc
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_object_set_data_full
argument_list|(
name|G_OBJECT
argument_list|(
name|context
operator|->
name|gimp
argument_list|)
argument_list|,
literal|"saved-stroke-desc"
argument_list|,
name|saved_desc
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_object_unref
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_item_stroke
argument_list|(
name|item
argument_list|,
name|drawable
argument_list|,
name|context
argument_list|,
name|desc
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|gimp_message
argument_list|(
name|context
operator|->
name|gimp
argument_list|,
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
name|GIMP_MESSAGE_WARNING
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
return|return;
block|}
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
comment|/* fallthrough */
default|default:
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|stroke_dialog_paint_info_selected (GimpContainerView * view,GimpViewable * viewable,gpointer insert_data,GimpStrokeDesc * desc)
name|stroke_dialog_paint_info_selected
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
name|GimpStrokeDesc
modifier|*
name|desc
parameter_list|)
block|{
name|g_object_set
argument_list|(
name|desc
argument_list|,
literal|"paint-info"
argument_list|,
name|viewable
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

