begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Copyright (C) 2003  Henrik Brix Andersen<brix@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"config/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpconfig-utils.h"
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
file|"widgets/gimpcontainermenuimpl.h"
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
name|GtkWidget
modifier|*
name|menu
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|insert_date
parameter_list|,
name|GtkWidget
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public function  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|stroke_dialog_new (GimpItem * item,const gchar * stock_id,const gchar * help_id,GtkWidget * parent)
name|stroke_dialog_new
parameter_list|(
name|GimpItem
modifier|*
name|item
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
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpStrokeOptions
modifier|*
name|options
decl_stmt|;
name|GimpStrokeOptions
modifier|*
name|saved_options
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
name|button
decl_stmt|;
name|GSList
modifier|*
name|group
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|gboolean
name|libart_stroking
init|=
name|TRUE
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
name|context
operator|=
name|gimp_get_user_context
argument_list|(
name|image
operator|->
name|gimp
argument_list|)
expr_stmt|;
name|tool_info
operator|=
name|gimp_context_get_tool
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|options
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_STROKE_OPTIONS
argument_list|,
literal|"gimp"
argument_list|,
name|image
operator|->
name|gimp
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|options
argument_list|)
argument_list|,
literal|"libart-stroking"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|libart_stroking
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|options
argument_list|)
argument_list|,
literal|"gimp-paint-info"
argument_list|,
name|gimp_context_get_tool
argument_list|(
name|context
argument_list|)
operator|->
name|paint_info
argument_list|)
expr_stmt|;
name|saved_options
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|context
argument_list|)
argument_list|,
literal|"saved-stroke-options"
argument_list|)
expr_stmt|;
if|if
condition|(
name|saved_options
condition|)
block|{
name|gimp_config_sync
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|saved_options
argument_list|)
argument_list|,
name|GIMP_CONFIG
argument_list|(
name|options
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|libart_stroking
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|saved_options
argument_list|)
argument_list|,
literal|"libart-stroking"
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|options
argument_list|)
argument_list|,
literal|"libart-stroking"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|libart_stroking
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|options
argument_list|)
argument_list|,
literal|"gimp-paint-info"
argument_list|,
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|saved_options
argument_list|)
argument_list|,
literal|"gimp-paint-info"
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gimp_context_set_parent
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
argument_list|,
name|context
argument_list|)
expr_stmt|;
name|gimp_context_define_properties
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
argument_list|,
name|GIMP_CONTEXT_FOREGROUND_MASK
operator||
name|GIMP_CONTEXT_PATTERN_MASK
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/* the dialog */
name|dialog
operator|=
name|gimp_viewable_dialog_new
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|item
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Stroke Options"
argument_list|)
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
literal|"gimp-stroke-options"
argument_list|,
name|options
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
comment|/*  the stroke frame  */
name|frame
operator|=
name|gtk_frame_new
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
name|button
operator|=
name|gtk_radio_button_new_with_label
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Stroke"
argument_list|)
argument_list|)
expr_stmt|;
name|group
operator|=
name|gtk_radio_button_get_group
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_frame_set_label_widget
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|button
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
name|gimp_toggle_button_sensitive_update
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimp-stroke-button"
argument_list|,
name|button
argument_list|)
expr_stmt|;
block|{
name|GtkWidget
modifier|*
name|stroke_editor
decl_stmt|;
name|stroke_editor
operator|=
name|gimp_stroke_editor_new
argument_list|(
name|options
argument_list|,
name|image
operator|->
name|yresolution
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|stroke_editor
argument_list|)
argument_list|,
literal|4
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
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"set_sensitive"
argument_list|,
name|stroke_editor
argument_list|)
expr_stmt|;
block|}
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|libart_stroking
argument_list|)
expr_stmt|;
comment|/*  the paint tool frame  */
name|frame
operator|=
name|gtk_frame_new
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
name|button
operator|=
name|gtk_radio_button_new_with_label
argument_list|(
name|group
argument_list|,
name|_
argument_list|(
literal|"Stroke Using a Paint Tool"
argument_list|)
argument_list|)
expr_stmt|;
name|group
operator|=
name|gtk_radio_button_get_group
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_frame_set_label_widget
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|button
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
name|gimp_toggle_button_sensitive_update
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|{
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
name|optionmenu
decl_stmt|;
name|GtkWidget
modifier|*
name|menu
decl_stmt|;
name|GimpPaintInfo
modifier|*
name|paint_info
decl_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
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
name|hbox
argument_list|)
argument_list|,
literal|4
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
name|gtk_widget_set_sensitive
argument_list|(
name|GTK_WIDGET
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"set_sensitive"
argument_list|,
name|hbox
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Paint Tool:"
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
name|optionmenu
operator|=
name|gtk_option_menu_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|optionmenu
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
name|optionmenu
argument_list|)
expr_stmt|;
name|menu
operator|=
name|gimp_container_menu_new
argument_list|(
name|image
operator|->
name|gimp
operator|->
name|paint_info_list
argument_list|,
name|NULL
argument_list|,
literal|16
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_option_menu_set_menu
argument_list|(
name|GTK_OPTION_MENU
argument_list|(
name|optionmenu
argument_list|)
argument_list|,
name|menu
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|menu
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|menu
argument_list|,
literal|"select_item"
argument_list|,
name|G_CALLBACK
argument_list|(
name|stroke_dialog_paint_info_selected
argument_list|)
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|paint_info
operator|=
name|GIMP_PAINT_INFO
argument_list|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|options
argument_list|)
argument_list|,
literal|"gimp-paint-info"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_container_menu_select_item
argument_list|(
name|GIMP_CONTAINER_MENU
argument_list|(
name|menu
argument_list|)
argument_list|,
name|GIMP_VIEWABLE
argument_list|(
name|paint_info
argument_list|)
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
name|menu
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimp-paint-info"
argument_list|,
name|paint_info
argument_list|)
expr_stmt|;
block|}
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
operator|!
name|libart_stroking
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
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GimpImage
modifier|*
name|image
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
name|button
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimp-stroke-button"
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
name|gimp_get_user_context
argument_list|(
name|image
operator|->
name|gimp
argument_list|)
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
name|GObject
modifier|*
name|options
decl_stmt|;
name|GtkWidget
modifier|*
name|menu
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|options
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimp-stroke-options"
argument_list|)
expr_stmt|;
name|menu
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimp-tool-menu"
argument_list|)
expr_stmt|;
name|tool_info
operator|=
name|gimp_context_get_tool
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_container_menu_select_item
argument_list|(
name|GIMP_CONTAINER_MENU
argument_list|(
name|menu
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
name|gimp_config_reset
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|options
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
decl_stmt|;
name|GimpObject
modifier|*
name|options
decl_stmt|;
name|GObject
modifier|*
name|saved_options
decl_stmt|;
name|drawable
operator|=
name|gimp_image_active_drawable
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|drawable
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"There is no active layer or channel to stroke to."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|saved_options
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|context
argument_list|)
argument_list|,
literal|"saved-stroke-options"
argument_list|)
expr_stmt|;
name|options
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimp-stroke-options"
argument_list|)
expr_stmt|;
if|if
condition|(
name|saved_options
condition|)
block|{
name|gimp_config_sync
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|options
argument_list|)
argument_list|,
name|GIMP_CONFIG
argument_list|(
name|saved_options
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_object_set_data_full
argument_list|(
name|G_OBJECT
argument_list|(
name|context
argument_list|)
argument_list|,
literal|"saved-stroke-options"
argument_list|,
name|g_object_ref
argument_list|(
name|options
argument_list|)
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_object_unref
argument_list|)
expr_stmt|;
name|saved_options
operator|=
name|G_OBJECT
argument_list|(
name|options
argument_list|)
expr_stmt|;
block|}
name|g_object_set_data
argument_list|(
name|saved_options
argument_list|,
literal|"gimp-paint-info"
argument_list|,
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimp-paint-info"
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gtk_toggle_button_get_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|)
condition|)
block|{
name|g_object_set_data
argument_list|(
name|saved_options
argument_list|,
literal|"libart-stroking"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|TRUE
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_object_set_data
argument_list|(
name|saved_options
argument_list|,
literal|"libart-stroking"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|FALSE
argument_list|)
argument_list|)
expr_stmt|;
name|options
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimp-paint-info"
argument_list|)
expr_stmt|;
block|}
name|gimp_item_stroke
argument_list|(
name|item
argument_list|,
name|drawable
argument_list|,
name|options
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
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
DECL|function|stroke_dialog_paint_info_selected (GtkWidget * menu,GimpViewable * viewable,gpointer insert_date,GtkWidget * dialog)
name|stroke_dialog_paint_info_selected
parameter_list|(
name|GtkWidget
modifier|*
name|menu
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|insert_date
parameter_list|,
name|GtkWidget
modifier|*
name|dialog
parameter_list|)
block|{
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimp-paint-info"
argument_list|,
name|viewable
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

