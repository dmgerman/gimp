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
file|<string.h>
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
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-mask.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-undo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-undo-push.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-mask-select.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcolorpanel.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpitemlistview.h"
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
file|"channels-commands.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|channels_opacity_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|channels_color_changed
parameter_list|(
name|GimpColorButton
modifier|*
name|button
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|return_if_no_image (gimage,data)
define|#
directive|define
name|return_if_no_image
parameter_list|(
name|gimage
parameter_list|,
name|data
parameter_list|)
define|\
value|if (GIMP_IS_DISPLAY (data)) \     gimage = ((GimpDisplay *) data)->gimage; \   else if (GIMP_IS_GIMP (data)) \     gimage = gimp_context_get_image (gimp_get_user_context (GIMP (data))); \   else if (GIMP_IS_ITEM_LIST_VIEW (data)) \     gimage = ((GimpItemListView *) data)->gimage; \   else \     gimage = NULL; \   \   if (! gimage) \     return
end_define

begin_define
DECL|macro|return_if_no_channel (gimage,channel,data)
define|#
directive|define
name|return_if_no_channel
parameter_list|(
name|gimage
parameter_list|,
name|channel
parameter_list|,
name|data
parameter_list|)
define|\
value|return_if_no_image (gimage,data); \   channel = gimp_image_get_active_channel (gimage); \   if (! channel) \     return
end_define

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|channels_new_channel_cmd_callback (GtkWidget * widget,gpointer data)
name|channels_new_channel_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|return_if_no_image
argument_list|(
name|gimage
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|channels_new_channel_query
argument_list|(
name|gimage
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|channels_raise_channel_cmd_callback (GtkWidget * widget,gpointer data)
name|channels_raise_channel_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpChannel
modifier|*
name|active_channel
decl_stmt|;
name|return_if_no_channel
argument_list|(
name|gimage
argument_list|,
name|active_channel
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_image_raise_channel
argument_list|(
name|gimage
argument_list|,
name|active_channel
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
DECL|function|channels_lower_channel_cmd_callback (GtkWidget * widget,gpointer data)
name|channels_lower_channel_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpChannel
modifier|*
name|active_channel
decl_stmt|;
name|return_if_no_channel
argument_list|(
name|gimage
argument_list|,
name|active_channel
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_image_lower_channel
argument_list|(
name|gimage
argument_list|,
name|active_channel
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
DECL|function|channels_duplicate_channel_cmd_callback (GtkWidget * widget,gpointer data)
name|channels_duplicate_channel_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpChannel
modifier|*
name|active_channel
decl_stmt|;
name|GimpChannel
modifier|*
name|new_channel
decl_stmt|;
name|return_if_no_channel
argument_list|(
name|gimage
argument_list|,
name|active_channel
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|new_channel
operator|=
name|GIMP_CHANNEL
argument_list|(
name|gimp_item_duplicate
argument_list|(
name|GIMP_ITEM
argument_list|(
name|active_channel
argument_list|)
argument_list|,
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|active_channel
argument_list|)
argument_list|,
name|TRUE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_add_channel
argument_list|(
name|gimage
argument_list|,
name|new_channel
argument_list|,
operator|-
literal|1
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
DECL|function|channels_delete_channel_cmd_callback (GtkWidget * widget,gpointer data)
name|channels_delete_channel_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpChannel
modifier|*
name|active_channel
decl_stmt|;
name|return_if_no_channel
argument_list|(
name|gimage
argument_list|,
name|active_channel
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_image_remove_channel
argument_list|(
name|gimage
argument_list|,
name|active_channel
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
specifier|static
name|void
DECL|function|channels_channel_to_sel (GtkWidget * widget,gpointer data,GimpChannelOps op)
name|channels_channel_to_sel
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|GimpChannelOps
name|op
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpChannel
modifier|*
name|active_channel
decl_stmt|;
name|return_if_no_channel
argument_list|(
name|gimage
argument_list|,
name|active_channel
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_image_mask_select_channel
argument_list|(
name|gimage
argument_list|,
name|_
argument_list|(
literal|"Channel to Selection"
argument_list|)
argument_list|,
name|active_channel
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|op
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|,
literal|0
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
DECL|function|channels_channel_to_sel_cmd_callback (GtkWidget * widget,gpointer data)
name|channels_channel_to_sel_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|channels_channel_to_sel
argument_list|(
name|widget
argument_list|,
name|data
argument_list|,
name|GIMP_CHANNEL_OP_REPLACE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|channels_add_channel_to_sel_cmd_callback (GtkWidget * widget,gpointer data)
name|channels_add_channel_to_sel_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|channels_channel_to_sel
argument_list|(
name|widget
argument_list|,
name|data
argument_list|,
name|GIMP_CHANNEL_OP_ADD
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|channels_sub_channel_from_sel_cmd_callback (GtkWidget * widget,gpointer data)
name|channels_sub_channel_from_sel_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|channels_channel_to_sel
argument_list|(
name|widget
argument_list|,
name|data
argument_list|,
name|GIMP_CHANNEL_OP_SUBTRACT
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|channels_intersect_channel_with_sel_cmd_callback (GtkWidget * widget,gpointer data)
name|channels_intersect_channel_with_sel_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|channels_channel_to_sel
argument_list|(
name|widget
argument_list|,
name|data
argument_list|,
name|GIMP_CHANNEL_OP_INTERSECT
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|channels_edit_channel_attributes_cmd_callback (GtkWidget * widget,gpointer data)
name|channels_edit_channel_attributes_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpChannel
modifier|*
name|active_channel
decl_stmt|;
name|return_if_no_channel
argument_list|(
name|gimage
argument_list|,
name|active_channel
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|channels_edit_channel_query
argument_list|(
name|active_channel
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**********************************/
end_comment

begin_comment
comment|/*  The new channel query dialog  */
end_comment

begin_comment
comment|/**********************************/
end_comment

begin_typedef
DECL|typedef|NewChannelOptions
typedef|typedef
name|struct
name|_NewChannelOptions
name|NewChannelOptions
typedef|;
end_typedef

begin_struct
DECL|struct|_NewChannelOptions
struct|struct
name|_NewChannelOptions
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

begin_decl_stmt
DECL|variable|channel_name
specifier|static
name|gchar
modifier|*
name|channel_name
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|channel_color
specifier|static
name|GimpRGB
name|channel_color
init|=
block|{
literal|0.0
block|,
literal|0.0
block|,
literal|0.0
block|,
literal|0.5
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|new_channel_query_ok_callback (GtkWidget * widget,gpointer data)
name|new_channel_query_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|NewChannelOptions
modifier|*
name|options
decl_stmt|;
name|GimpChannel
modifier|*
name|new_channel
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|options
operator|=
operator|(
name|NewChannelOptions
operator|*
operator|)
name|data
expr_stmt|;
if|if
condition|(
name|channel_name
condition|)
name|g_free
argument_list|(
name|channel_name
argument_list|)
expr_stmt|;
name|channel_name
operator|=
name|g_strdup
argument_list|(
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|options
operator|->
name|name_entry
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|gimage
operator|=
name|options
operator|->
name|gimage
operator|)
condition|)
block|{
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
name|channel_color
argument_list|)
expr_stmt|;
name|new_channel
operator|=
name|gimp_channel_new
argument_list|(
name|gimage
argument_list|,
name|gimage
operator|->
name|width
argument_list|,
name|gimage
operator|->
name|height
argument_list|,
name|channel_name
argument_list|,
operator|&
name|channel_color
argument_list|)
expr_stmt|;
name|gimp_drawable_fill_by_type
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|new_channel
argument_list|)
argument_list|,
name|gimp_get_user_context
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|)
argument_list|,
name|GIMP_TRANSPARENT_FILL
argument_list|)
expr_stmt|;
name|gimp_image_add_channel
argument_list|(
name|gimage
argument_list|,
name|new_channel
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
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
name|void
DECL|function|channels_new_channel_query (GimpImage * gimage,GimpChannel * template,gboolean interactive)
name|channels_new_channel_query
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpChannel
modifier|*
name|template
parameter_list|,
name|gboolean
name|interactive
parameter_list|)
block|{
name|NewChannelOptions
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
name|GtkObject
modifier|*
name|opacity_scale_data
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
operator|!
name|template
operator|||
name|GIMP_IS_CHANNEL
argument_list|(
name|template
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|template
operator|||
operator|!
name|interactive
condition|)
block|{
name|GimpChannel
modifier|*
name|new_channel
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
if|if
condition|(
name|template
condition|)
block|{
name|width
operator|=
name|gimp_drawable_width
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|template
argument_list|)
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_drawable_height
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|template
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_drawable_offsets
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|template
argument_list|)
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
name|color
operator|=
name|template
operator|->
name|color
expr_stmt|;
block|}
else|else
block|{
name|width
operator|=
name|gimp_image_get_width
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_image_get_height
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|off_x
operator|=
literal|0
expr_stmt|;
name|off_y
operator|=
literal|0
expr_stmt|;
name|gimp_rgba_set
argument_list|(
operator|&
name|color
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
block|}
name|gimp_image_undo_group_start
argument_list|(
name|gimage
argument_list|,
name|GIMP_UNDO_GROUP_EDIT_PASTE
argument_list|,
name|_
argument_list|(
literal|"New Channel"
argument_list|)
argument_list|)
expr_stmt|;
name|new_channel
operator|=
name|gimp_channel_new
argument_list|(
name|gimage
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|_
argument_list|(
literal|"Empty Channel Copy"
argument_list|)
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
if|if
condition|(
name|template
condition|)
block|{
name|gimp_drawable_fill_by_type
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|new_channel
argument_list|)
argument_list|,
name|gimp_get_user_context
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|)
argument_list|,
name|GIMP_TRANSPARENT_FILL
argument_list|)
expr_stmt|;
name|gimp_channel_translate
argument_list|(
name|new_channel
argument_list|,
name|off_x
argument_list|,
name|off_y
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
name|gimp_image_add_channel
argument_list|(
name|gimage
argument_list|,
name|new_channel
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_end
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
return|return;
block|}
comment|/*  the new options structure  */
name|options
operator|=
name|g_new
argument_list|(
name|NewChannelOptions
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
name|color_panel
operator|=
name|gimp_color_panel_new
argument_list|(
name|_
argument_list|(
literal|"New Channel Color"
argument_list|)
argument_list|,
operator|&
name|channel_color
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
name|gimage
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"New Channel"
argument_list|)
argument_list|,
literal|"new_channel_options"
argument_list|,
name|GTK_STOCK_NEW
argument_list|,
name|_
argument_list|(
literal|"New Channel Options"
argument_list|)
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"dialogs/channels/new_channel.html"
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|gtk_widget_destroy
argument_list|,
name|NULL
argument_list|,
literal|1
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|GTK_STOCK_OK
argument_list|,
name|new_channel_query_ok_callback
argument_list|,
name|options
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|FALSE
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
literal|2
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
comment|/*  The table  */
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|2
argument_list|,
literal|3
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
literal|2
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|2
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
comment|/*  The name entry  */
name|options
operator|->
name|name_entry
operator|=
name|gtk_entry_new
argument_list|()
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
operator|(
name|channel_name
condition|?
name|channel_name
else|:
name|_
argument_list|(
literal|"New Channel"
argument_list|)
operator|)
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
literal|"Channel Name:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|,
name|options
operator|->
name|name_entry
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/*  The opacity scale  */
name|opacity_scale_data
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|_
argument_list|(
literal|"Fill Opacity:"
argument_list|)
argument_list|,
literal|100
argument_list|,
operator|-
literal|1
argument_list|,
name|channel_color
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
literal|10.0
argument_list|,
literal|1
argument_list|,
name|TRUE
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
name|NULL
argument_list|,
name|NULL
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
name|channels_opacity_update
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
name|channels_color_changed
argument_list|)
argument_list|,
name|opacity_scale_data
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
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

begin_comment
comment|/****************************************/
end_comment

begin_comment
comment|/*  The edit channel attributes dialog  */
end_comment

begin_comment
comment|/****************************************/
end_comment

begin_typedef
DECL|typedef|EditChannelOptions
typedef|typedef
name|struct
name|_EditChannelOptions
name|EditChannelOptions
typedef|;
end_typedef

begin_struct
DECL|struct|_EditChannelOptions
struct|struct
name|_EditChannelOptions
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
DECL|member|channel
name|GimpChannel
modifier|*
name|channel
decl_stmt|;
DECL|member|gimage
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
block|}
struct|;
end_struct

begin_function
specifier|static
name|void
DECL|function|edit_channel_query_ok_callback (GtkWidget * widget,gpointer data)
name|edit_channel_query_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|EditChannelOptions
modifier|*
name|options
decl_stmt|;
name|GimpChannel
modifier|*
name|channel
decl_stmt|;
name|options
operator|=
operator|(
name|EditChannelOptions
operator|*
operator|)
name|data
expr_stmt|;
name|channel
operator|=
name|options
operator|->
name|channel
expr_stmt|;
if|if
condition|(
name|options
operator|->
name|gimage
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|new_name
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|new_name
operator|=
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|options
operator|->
name|name_entry
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|new_name
argument_list|,
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|channel
argument_list|)
argument_list|)
argument_list|)
condition|)
block|{
name|gimp_image_undo_push_item_rename
argument_list|(
name|options
operator|->
name|gimage
argument_list|,
name|_
argument_list|(
literal|"Rename Channel"
argument_list|)
argument_list|,
name|GIMP_ITEM
argument_list|(
name|channel
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|channel
argument_list|)
argument_list|,
name|new_name
argument_list|)
expr_stmt|;
block|}
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
name|color
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_rgba_distance
argument_list|(
operator|&
name|color
argument_list|,
operator|&
name|channel
operator|->
name|color
argument_list|)
operator|>
literal|0.0001
condition|)
block|{
name|gimp_channel_set_color
argument_list|(
name|channel
argument_list|,
operator|&
name|color
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
name|void
DECL|function|channels_edit_channel_query (GimpChannel * channel)
name|channels_edit_channel_query
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|)
block|{
name|EditChannelOptions
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
name|GtkObject
modifier|*
name|opacity_scale_data
decl_stmt|;
name|options
operator|=
name|g_new0
argument_list|(
name|EditChannelOptions
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|options
operator|->
name|channel
operator|=
name|channel
expr_stmt|;
name|options
operator|->
name|gimage
operator|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|channel
argument_list|)
argument_list|)
expr_stmt|;
name|channel_color
operator|=
name|channel
operator|->
name|color
expr_stmt|;
name|options
operator|->
name|color_panel
operator|=
name|gimp_color_panel_new
argument_list|(
name|_
argument_list|(
literal|"Edit Channel Color"
argument_list|)
argument_list|,
operator|&
name|channel_color
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
name|channel
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Channel Attributes"
argument_list|)
argument_list|,
literal|"edit_channel_attributes"
argument_list|,
name|GIMP_STOCK_EDIT
argument_list|,
name|_
argument_list|(
literal|"Edit Channel Attributes"
argument_list|)
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"dialogs/channels/edit_channel_attributes.html"
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|gtk_widget_destroy
argument_list|,
name|NULL
argument_list|,
literal|1
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|GTK_STOCK_OK
argument_list|,
name|edit_channel_query_ok_callback
argument_list|,
name|options
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|FALSE
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
literal|2
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
comment|/*  The table  */
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|2
argument_list|,
literal|3
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
literal|2
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|2
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
comment|/*  The name entry  */
name|options
operator|->
name|name_entry
operator|=
name|gtk_entry_new
argument_list|()
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
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|channel
argument_list|)
argument_list|)
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
literal|"Channel Name:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|,
name|options
operator|->
name|name_entry
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/*  The opacity scale  */
name|opacity_scale_data
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|_
argument_list|(
literal|"Fill Opacity:"
argument_list|)
argument_list|,
literal|100
argument_list|,
operator|-
literal|1
argument_list|,
name|channel_color
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
literal|10.0
argument_list|,
literal|1
argument_list|,
name|TRUE
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
name|NULL
argument_list|,
name|NULL
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
name|channels_opacity_update
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
name|channels_color_changed
argument_list|)
argument_list|,
name|opacity_scale_data
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
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
name|void
DECL|function|channels_duplicate_component_cmd_callback (GtkWidget * widget,gpointer data)
name|channels_duplicate_component_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpChannel
modifier|*
name|channel
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|return_if_no_image
argument_list|(
name|gimage
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_rgba_set
argument_list|(
operator|&
name|color
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
comment|/*  FIXME: hardcoded component  */
name|channel
operator|=
name|gimp_channel_new_from_component
argument_list|(
name|gimage
argument_list|,
name|GIMP_RED_CHANNEL
argument_list|,
literal|"Component Copy"
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|gimp_image_add_channel
argument_list|(
name|gimage
argument_list|,
name|channel
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|gimage
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
DECL|function|channels_opacity_update (GtkAdjustment * adjustment,gpointer data)
name|channels_opacity_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpRGB
name|color
decl_stmt|;
name|gimp_color_button_get_color
argument_list|(
name|GIMP_COLOR_BUTTON
argument_list|(
name|data
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
name|data
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
DECL|function|channels_color_changed (GimpColorButton * button,gpointer data)
name|channels_color_changed
parameter_list|(
name|GimpColorButton
modifier|*
name|button
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GtkAdjustment
modifier|*
name|adj
init|=
name|GTK_ADJUSTMENT
argument_list|(
name|data
argument_list|)
decl_stmt|;
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

