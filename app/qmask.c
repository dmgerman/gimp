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
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"channel.h"
end_include

begin_include
include|#
directive|include
file|"color_panel.h"
end_include

begin_include
include|#
directive|include
file|"floating_sel.h"
end_include

begin_include
include|#
directive|include
file|"gdisplayF.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimage_mask.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpui.h"
end_include

begin_include
include|#
directive|include
file|"global_edit.h"
end_include

begin_include
include|#
directive|include
file|"qmask.h"
end_include

begin_include
include|#
directive|include
file|"undo.h"
end_include

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
DECL|member|gimage
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
DECL|member|color_panel
name|ColorPanel
modifier|*
name|color_panel
decl_stmt|;
DECL|member|opacity
name|double
name|opacity
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|EditQmaskOptions
typedef|typedef
name|struct
name|_EditQmaskOptions
name|EditQmaskOptions
typedef|;
end_typedef

begin_comment
comment|/*  Global variables  */
end_comment

begin_comment
comment|/*  Static variables  */
end_comment

begin_comment
comment|/*  Prototypes */
end_comment

begin_function_decl
specifier|static
name|void
name|edit_qmask_channel_query
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|edit_qmask_query_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|edit_qmask_query_cancel_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|client_data
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
name|gdouble
modifier|*
name|scale_val
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Actual code */
end_comment

begin_function
specifier|static
name|void
DECL|function|qmask_query_scale_update (GtkAdjustment * adjustment,gdouble * scale_val)
name|qmask_query_scale_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|gdouble
modifier|*
name|scale_val
parameter_list|)
block|{
operator|*
name|scale_val
operator|=
name|adjustment
operator|->
name|value
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|qmask_buttons_update (GDisplay * gdisp)
name|qmask_buttons_update
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|g_assert
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|gdisp
operator|->
name|gimage
operator|->
name|qmask_state
operator|!=
name|GTK_TOGGLE_BUTTON
argument_list|(
name|gdisp
operator|->
name|qmaskon
argument_list|)
operator|->
name|active
condition|)
block|{
comment|/* Disable toggle from doing anything */
name|gtk_signal_handler_block_by_func
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gdisp
operator|->
name|qmaskoff
argument_list|)
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|qmask_deactivate
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|gtk_signal_handler_block_by_func
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gdisp
operator|->
name|qmaskon
argument_list|)
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|qmask_activate
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
comment|/* Change the state of the buttons */
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|gdisp
operator|->
name|qmaskon
argument_list|)
argument_list|,
name|gdisp
operator|->
name|gimage
operator|->
name|qmask_state
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|gdisp
operator|->
name|qmaskoff
argument_list|)
argument_list|,
operator|!
name|gdisp
operator|->
name|gimage
operator|->
name|qmask_state
argument_list|)
expr_stmt|;
comment|/* Enable toggle again */
name|gtk_signal_handler_unblock_by_func
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gdisp
operator|->
name|qmaskoff
argument_list|)
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|qmask_deactivate
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|gtk_signal_handler_unblock_by_func
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gdisp
operator|->
name|qmaskon
argument_list|)
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|qmask_activate
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
comment|/* Flush event queue */
comment|/*  while (g_main_iteration(FALSE)); */
block|}
block|}
end_function

begin_function
name|void
DECL|function|qmask_click_handler (GtkWidget * widget,GdkEventButton * event,gpointer data)
name|qmask_click_handler
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|gdisp
operator|=
operator|(
name|GDisplay
operator|*
operator|)
name|data
expr_stmt|;
if|if
condition|(
operator|(
name|event
operator|->
name|type
operator|==
name|GDK_2BUTTON_PRESS
operator|)
operator|&&
operator|(
name|event
operator|->
name|button
operator|==
literal|1
operator|)
condition|)
block|{
name|edit_qmask_channel_query
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|qmask_deactivate (GtkWidget * w,GDisplay * gdisp)
name|qmask_deactivate
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimg
decl_stmt|;
name|GimpChannel
modifier|*
name|gmask
decl_stmt|;
if|if
condition|(
name|gdisp
condition|)
block|{
name|gimg
operator|=
name|gdisp
operator|->
name|gimage
expr_stmt|;
if|if
condition|(
operator|!
name|gimg
condition|)
return|return;
if|if
condition|(
operator|!
name|gdisp
operator|->
name|gimage
operator|->
name|qmask_state
condition|)
block|{
return|return;
comment|/* if already set do nothing */
block|}
name|undo_push_group_start
argument_list|(
name|gimg
argument_list|,
name|QMASK_UNDO
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|gmask
operator|=
name|gimp_image_get_channel_by_name
argument_list|(
name|gimg
argument_list|,
literal|"Qmask"
argument_list|)
operator|)
condition|)
block|{
name|gimage_mask_load
argument_list|(
name|gimg
argument_list|,
name|gmask
argument_list|)
expr_stmt|;
name|gimage_remove_channel
argument_list|(
name|gimg
argument_list|,
name|gmask
argument_list|)
expr_stmt|;
name|undo_push_qmask
argument_list|(
name|gimg
argument_list|)
expr_stmt|;
name|gdisp
operator|->
name|gimage
operator|->
name|qmask_state
operator|=
literal|0
expr_stmt|;
block|}
else|else
name|gdisp
operator|->
name|gimage
operator|->
name|qmask_state
operator|=
literal|0
expr_stmt|;
name|undo_push_group_end
argument_list|(
name|gimg
argument_list|)
expr_stmt|;
if|if
condition|(
name|gmask
condition|)
name|gdisplays_flush
argument_list|()
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|qmask_activate (GtkWidget * w,GDisplay * gdisp)
name|qmask_activate
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimg
decl_stmt|;
name|GimpChannel
modifier|*
name|gmask
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
name|double
name|opacity
decl_stmt|;
name|unsigned
name|char
modifier|*
name|color
decl_stmt|;
if|if
condition|(
name|gdisp
condition|)
block|{
name|gimg
operator|=
name|gdisp
operator|->
name|gimage
expr_stmt|;
if|if
condition|(
operator|!
name|gimg
condition|)
return|return;
if|if
condition|(
name|gdisp
operator|->
name|gimage
operator|->
name|qmask_state
condition|)
block|{
return|return;
comment|/* If already set, do nothing */
block|}
comment|/* Set the defaults */
name|opacity
operator|=
operator|(
name|double
operator|)
name|gimg
operator|->
name|qmask_opacity
expr_stmt|;
name|color
operator|=
name|gimg
operator|->
name|qmask_color
expr_stmt|;
if|if
condition|(
operator|(
name|gmask
operator|=
name|gimp_image_get_channel_by_name
argument_list|(
name|gimg
argument_list|,
literal|"Qmask"
argument_list|)
operator|)
condition|)
block|{
name|gimg
operator|->
name|qmask_state
operator|=
literal|1
expr_stmt|;
comment|/* if the user was clever and created his own */
return|return;
block|}
name|undo_push_group_start
argument_list|(
name|gimg
argument_list|,
name|QMASK_UNDO
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimage_mask_is_empty
argument_list|(
name|gimg
argument_list|)
condition|)
block|{
if|if
condition|(
operator|(
name|layer
operator|=
name|gimage_floating_sel
argument_list|(
name|gimg
argument_list|)
operator|)
condition|)
block|{
name|floating_sel_to_layer
argument_list|(
name|layer
argument_list|)
expr_stmt|;
block|}
comment|/* if no selection */
name|gmask
operator|=
name|channel_new
argument_list|(
name|gimg
argument_list|,
name|gimg
operator|->
name|width
argument_list|,
name|gimg
operator|->
name|height
argument_list|,
literal|"Qmask"
argument_list|,
call|(
name|int
call|)
argument_list|(
literal|255
operator|*
name|opacity
argument_list|)
operator|/
literal|100
argument_list|,
name|color
argument_list|)
expr_stmt|;
name|gimp_image_add_channel
argument_list|(
name|gimg
argument_list|,
name|gmask
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_drawable_fill
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|gmask
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/* edit_clear(gimg,GIMP_DRAWABLE(gmask));  */
name|undo_push_qmask
argument_list|(
name|gimg
argument_list|)
expr_stmt|;
name|gdisp
operator|->
name|gimage
operator|->
name|qmask_state
operator|=
literal|1
expr_stmt|;
block|}
else|else
block|{
comment|/* if selection */
name|gmask
operator|=
name|channel_copy
argument_list|(
name|gimage_get_mask
argument_list|(
name|gimg
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_add_channel
argument_list|(
name|gimg
argument_list|,
name|gmask
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|channel_set_color
argument_list|(
name|gmask
argument_list|,
name|color
argument_list|)
expr_stmt|;
name|channel_set_name
argument_list|(
name|gmask
argument_list|,
literal|"Qmask"
argument_list|)
expr_stmt|;
name|channel_set_opacity
argument_list|(
name|gmask
argument_list|,
name|opacity
argument_list|)
expr_stmt|;
name|gimage_mask_none
argument_list|(
name|gimg
argument_list|)
expr_stmt|;
comment|/* Clear the selection */
name|undo_push_qmask
argument_list|(
name|gimg
argument_list|)
expr_stmt|;
name|gdisp
operator|->
name|gimage
operator|->
name|qmask_state
operator|=
literal|1
expr_stmt|;
block|}
name|undo_push_group_end
argument_list|(
name|gimg
argument_list|)
expr_stmt|;
name|gdisplays_flush
argument_list|()
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|edit_qmask_channel_query (GDisplay * gdisp)
name|edit_qmask_channel_query
parameter_list|(
name|GDisplay
modifier|*
name|gdisp
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
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|opacity_scale
decl_stmt|;
name|GtkObject
modifier|*
name|opacity_scale_data
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|guchar
name|channel_color
index|[
literal|3
index|]
init|=
block|{
literal|0
block|,
literal|0
block|,
literal|0
block|}
decl_stmt|;
comment|/* channel = gimp_image_get_channel_by_name (gdisp->gimage, "Qmask"); */
comment|/*  the new options structure  */
name|options
operator|=
name|g_new
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
name|gdisp
operator|->
name|gimage
expr_stmt|;
name|options
operator|->
name|opacity
operator|=
operator|(
name|gdouble
operator|)
name|options
operator|->
name|gimage
operator|->
name|qmask_opacity
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|3
condition|;
name|i
operator|++
control|)
name|channel_color
index|[
name|i
index|]
operator|=
name|options
operator|->
name|gimage
operator|->
name|qmask_color
index|[
name|i
index|]
expr_stmt|;
name|options
operator|->
name|color_panel
operator|=
name|color_panel_new
argument_list|(
name|channel_color
argument_list|,
literal|48
argument_list|,
literal|64
argument_list|)
expr_stmt|;
comment|/*  The dialog  */
name|options
operator|->
name|query_box
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Edit Qmask Attributes"
argument_list|)
argument_list|,
literal|"edit_qmask_attributes"
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"dialogs/edit_qmask_attributes_dialog.html"
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|_
argument_list|(
literal|"OK"
argument_list|)
argument_list|,
name|edit_qmask_query_ok_callback
argument_list|,
name|options
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|_
argument_list|(
literal|"Cancel"
argument_list|)
argument_list|,
name|edit_qmask_query_cancel_callback
argument_list|,
name|options
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|NULL
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
comment|/*  The opacity scale  */
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Mask Opacity:"
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
literal|1.0
argument_list|,
literal|1.0
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
name|GTK_EXPAND
operator||
name|GTK_FILL
argument_list|,
name|GTK_EXPAND
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
name|label
argument_list|)
expr_stmt|;
name|opacity_scale_data
operator|=
name|gtk_adjustment_new
argument_list|(
name|options
operator|->
name|opacity
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
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|opacity_scale
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|1
argument_list|,
literal|2
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
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|opacity_scale_data
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|qmask_query_scale_update
argument_list|,
operator|&
name|options
operator|->
name|opacity
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|opacity_scale
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
operator|->
name|color_panel_widget
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
operator|->
name|color_panel_widget
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
DECL|function|edit_qmask_query_ok_callback (GtkWidget * widget,gpointer client_data)
specifier|static
name|void
name|edit_qmask_query_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
name|EditQmaskOptions
modifier|*
name|options
decl_stmt|;
name|Channel
modifier|*
name|channel
decl_stmt|;
name|gint
name|opacity
decl_stmt|;
name|gint
name|update
init|=
name|FALSE
decl_stmt|;
name|guchar
modifier|*
name|tmpcolp
decl_stmt|;
name|guchar
name|tmpcol
index|[
literal|3
index|]
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|options
operator|=
operator|(
name|EditQmaskOptions
operator|*
operator|)
name|client_data
expr_stmt|;
name|channel
operator|=
name|gimp_image_get_channel_by_name
argument_list|(
name|options
operator|->
name|gimage
argument_list|,
literal|"Qmask"
argument_list|)
expr_stmt|;
name|opacity
operator|=
call|(
name|int
call|)
argument_list|(
literal|255
operator|*
name|options
operator|->
name|opacity
operator|/
literal|100
argument_list|)
expr_stmt|;
if|if
condition|(
name|options
operator|->
name|gimage
operator|&&
name|channel
condition|)
block|{
comment|/* don't update if opacity hasn't changed */
if|if
condition|(
name|channel_get_opacity
argument_list|(
name|channel
argument_list|)
operator|!=
name|opacity
condition|)
block|{
name|update
operator|=
name|TRUE
expr_stmt|;
block|}
name|tmpcolp
operator|=
name|channel_get_color
argument_list|(
name|channel
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|3
condition|;
name|i
operator|++
control|)
block|{
comment|/* don't update if color hasn't changed */
name|tmpcol
index|[
name|i
index|]
operator|=
name|tmpcolp
index|[
name|i
index|]
expr_stmt|;
comment|/* initialize to same values */
if|if
condition|(
name|options
operator|->
name|color_panel
operator|->
name|color
index|[
name|i
index|]
operator|!=
name|tmpcolp
index|[
name|i
index|]
condition|)
block|{
name|tmpcol
index|[
name|i
index|]
operator|=
name|options
operator|->
name|color_panel
operator|->
name|color
index|[
name|i
index|]
expr_stmt|;
name|update
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
if|if
condition|(
name|update
condition|)
block|{
name|channel_set_opacity
argument_list|(
name|channel
argument_list|,
literal|100
operator|*
name|opacity
operator|/
literal|255
argument_list|)
expr_stmt|;
name|channel_set_color
argument_list|(
name|channel
argument_list|,
name|tmpcol
argument_list|)
expr_stmt|;
name|channel_update
argument_list|(
name|channel
argument_list|)
expr_stmt|;
block|}
block|}
comment|/* update the qmask color no matter what */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|3
condition|;
name|i
operator|++
control|)
block|{
comment|/* TODO: should really have accessor functions for gimage private stuff */
name|options
operator|->
name|gimage
operator|->
name|qmask_color
index|[
name|i
index|]
operator|=
name|options
operator|->
name|color_panel
operator|->
name|color
index|[
name|i
index|]
expr_stmt|;
name|options
operator|->
name|gimage
operator|->
name|qmask_opacity
operator|=
operator|(
name|gint
operator|)
literal|100
operator|*
name|opacity
operator|/
literal|255
expr_stmt|;
block|}
name|color_panel_free
argument_list|(
name|options
operator|->
name|color_panel
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|options
operator|->
name|query_box
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|options
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|edit_qmask_query_cancel_callback (GtkWidget * widget,gpointer client_data)
name|edit_qmask_query_cancel_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
name|EditQmaskOptions
modifier|*
name|options
decl_stmt|;
name|options
operator|=
operator|(
name|EditQmaskOptions
operator|*
operator|)
name|client_data
expr_stmt|;
name|color_panel_free
argument_list|(
name|options
operator|->
name|color_panel
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|options
operator|->
name|query_box
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|options
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

