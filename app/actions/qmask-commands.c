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
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"actions-types.h"
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
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-qmask.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcolorpanel.h"
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
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"actions.h"
end_include

begin_include
include|#
directive|include
file|"qmask-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_typedef
DECL|typedef|EditQmaskOptions
typedef|typedef
name|struct
name|_EditQmaskOptions
name|EditQmaskOptions
typedef|;
end_typedef

begin_struct
DECL|struct|_EditQmaskOptions
struct|struct
name|_EditQmaskOptions
block|{
DECL|member|query_box
name|GtkWidget
modifier|*
name|query_box
decl_stmt|;
DECL|member|name_entry
name|GtkWidget
modifier|*
name|name_entry
decl_stmt|;
DECL|member|color_panel
name|GtkWidget
modifier|*
name|color_panel
decl_stmt|;
DECL|member|gimage
name|GimpImage
modifier|*
name|gimage
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
name|qmask_channel_query
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|qmask_query_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|EditQmaskOptions
modifier|*
name|options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|qmask_query_scale_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|GtkWidget
modifier|*
name|panel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|qmask_query_color_changed
parameter_list|(
name|GimpColorButton
modifier|*
name|button
parameter_list|,
name|GtkAdjustment
modifier|*
name|adj
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functionss */
end_comment

begin_function
name|void
DECL|function|qmask_toggle_cmd_callback (GtkAction * action,gpointer data)
name|qmask_toggle_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|gboolean
name|active
decl_stmt|;
name|return_if_no_image
argument_list|(
name|gimage
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|active
operator|=
name|gtk_toggle_action_get_active
argument_list|(
name|GTK_TOGGLE_ACTION
argument_list|(
name|action
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|active
operator|!=
name|gimp_image_get_qmask_state
argument_list|(
name|gimage
argument_list|)
condition|)
block|{
name|gimp_image_set_qmask_state
argument_list|(
name|gimage
argument_list|,
name|active
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|qmask_invert_cmd_callback (GtkAction * action,GtkAction * current,gpointer data)
name|qmask_invert_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|GtkAction
modifier|*
name|current
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|gint
name|value
decl_stmt|;
name|return_if_no_image
argument_list|(
name|gimage
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|value
operator|=
name|gtk_radio_action_get_current_value
argument_list|(
name|GTK_RADIO_ACTION
argument_list|(
name|action
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|value
operator|!=
name|gimage
operator|->
name|qmask_inverted
condition|)
block|{
name|gimp_image_qmask_invert
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|qmask_configure_cmd_callback (GtkAction * action,gpointer data)
name|qmask_configure_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|qmask_channel_query
argument_list|(
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|qmask_channel_query (GimpDisplayShell * shell)
name|qmask_channel_query
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|EditQmaskOptions
modifier|*
name|options
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
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
name|opacity_scale
decl_stmt|;
name|GtkObject
modifier|*
name|opacity_scale_data
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|gimp_image_get_qmask_color
argument_list|(
name|shell
operator|->
name|gdisp
operator|->
name|gimage
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
comment|/*  the new options structure  */
name|options
operator|=
name|g_new0
argument_list|(
name|EditQmaskOptions
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|options
operator|->
name|gimage
operator|=
name|shell
operator|->
name|gdisp
operator|->
name|gimage
expr_stmt|;
name|options
operator|->
name|color_panel
operator|=
name|gimp_color_panel_new
argument_list|(
name|_
argument_list|(
literal|"Edit QuickMask Color"
argument_list|)
argument_list|,
operator|&
name|color
argument_list|,
name|GIMP_COLOR_AREA_LARGE_CHECKS
argument_list|,
literal|48
argument_list|,
literal|64
argument_list|)
expr_stmt|;
name|gimp_color_panel_set_context
argument_list|(
name|GIMP_COLOR_PANEL
argument_list|(
name|options
operator|->
name|color_panel
argument_list|)
argument_list|,
name|gimp_get_user_context
argument_list|(
name|options
operator|->
name|gimage
operator|->
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  The dialog  */
name|options
operator|->
name|query_box
operator|=
name|gimp_viewable_dialog_new
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|shell
operator|->
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"QuickMask Attributes"
argument_list|)
argument_list|,
literal|"gimp-qmask-edit"
argument_list|,
name|GIMP_STOCK_QMASK_ON
argument_list|,
name|_
argument_list|(
literal|"Edit QuickMask Attributes"
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|shell
argument_list|)
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_QMASK_EDIT
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
name|options
operator|->
name|query_box
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|qmask_query_response
argument_list|)
argument_list|,
name|options
argument_list|)
expr_stmt|;
name|g_object_weak_ref
argument_list|(
name|G_OBJECT
argument_list|(
name|options
operator|->
name|query_box
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
comment|/*  The main hbox  */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|hbox
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
name|query_box
argument_list|)
operator|->
name|vbox
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
comment|/*  The vbox  */
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|2
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
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
comment|/*  The table  */
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|1
argument_list|,
literal|2
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
comment|/*  The opacity scale  */
name|opacity_scale_data
operator|=
name|gtk_adjustment_new
argument_list|(
name|color
operator|.
name|a
operator|*
literal|100.0
argument_list|,
literal|0.0
argument_list|,
literal|100.0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|opacity_scale
operator|=
name|gtk_hscale_new
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|opacity_scale_data
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|opacity_scale
argument_list|,
literal|100
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_scale_set_value_pos
argument_list|(
name|GTK_SCALE
argument_list|(
name|opacity_scale
argument_list|)
argument_list|,
name|GTK_POS_TOP
argument_list|)
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
literal|"Mask Opacity:"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
name|opacity_scale
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|opacity_scale_data
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|qmask_query_scale_update
argument_list|)
argument_list|,
name|options
operator|->
name|color_panel
argument_list|)
expr_stmt|;
comment|/*  The color panel  */
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|options
operator|->
name|color_panel
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
name|options
operator|->
name|color_panel
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|options
operator|->
name|color_panel
argument_list|,
literal|"color_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|qmask_query_color_changed
argument_list|)
argument_list|,
name|opacity_scale_data
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|options
operator|->
name|query_box
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|qmask_query_response (GtkWidget * widget,gint response_id,EditQmaskOptions * options)
name|qmask_query_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|EditQmaskOptions
modifier|*
name|options
parameter_list|)
block|{
if|if
condition|(
name|response_id
operator|==
name|GTK_RESPONSE_OK
condition|)
block|{
name|GimpRGB
name|old_color
decl_stmt|;
name|GimpRGB
name|new_color
decl_stmt|;
name|gimp_image_get_qmask_color
argument_list|(
name|options
operator|->
name|gimage
argument_list|,
operator|&
name|old_color
argument_list|)
expr_stmt|;
name|gimp_color_button_get_color
argument_list|(
name|GIMP_COLOR_BUTTON
argument_list|(
name|options
operator|->
name|color_panel
argument_list|)
argument_list|,
operator|&
name|new_color
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_rgba_distance
argument_list|(
operator|&
name|old_color
argument_list|,
operator|&
name|new_color
argument_list|)
operator|>
literal|0.0001
condition|)
block|{
name|gimp_image_set_qmask_color
argument_list|(
name|options
operator|->
name|gimage
argument_list|,
operator|&
name|new_color
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|options
operator|->
name|gimage
argument_list|)
expr_stmt|;
block|}
block|}
name|gtk_widget_destroy
argument_list|(
name|options
operator|->
name|query_box
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|qmask_query_scale_update (GtkAdjustment * adjustment,GtkWidget * panel)
name|qmask_query_scale_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|GtkWidget
modifier|*
name|panel
parameter_list|)
block|{
name|GimpRGB
name|color
decl_stmt|;
name|gimp_color_button_get_color
argument_list|(
name|GIMP_COLOR_BUTTON
argument_list|(
name|panel
argument_list|)
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|gimp_rgb_set_alpha
argument_list|(
operator|&
name|color
argument_list|,
name|adjustment
operator|->
name|value
operator|/
literal|100.0
argument_list|)
expr_stmt|;
name|gimp_color_button_set_color
argument_list|(
name|GIMP_COLOR_BUTTON
argument_list|(
name|panel
argument_list|)
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|qmask_query_color_changed (GimpColorButton * button,GtkAdjustment * adj)
name|qmask_query_color_changed
parameter_list|(
name|GimpColorButton
modifier|*
name|button
parameter_list|,
name|GtkAdjustment
modifier|*
name|adj
parameter_list|)
block|{
name|GimpRGB
name|color
decl_stmt|;
name|gimp_color_button_get_color
argument_list|(
name|button
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|adj
argument_list|,
name|color
operator|.
name|a
operator|*
literal|100.0
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

