begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Library General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Library General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimpenums.h"
end_include

begin_include
include|#
directive|include
file|"gimpexport.h"
end_include

begin_include
include|#
directive|include
file|"gimpintl.h"
end_include

begin_typedef
DECL|typedef|ExportFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|ExportFunc
function_decl|)
parameter_list|(
name|gint32
name|imageID
parameter_list|,
name|gint32
modifier|*
name|drawable_ID
parameter_list|)
function_decl|;
end_typedef

begin_comment
comment|/* the export action structure */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c3903730108
block|{
DECL|member|default_action
name|ExportFunc
name|default_action
decl_stmt|;
DECL|member|alt_action
name|ExportFunc
name|alt_action
decl_stmt|;
DECL|member|reason
name|gchar
modifier|*
name|reason
decl_stmt|;
DECL|member|possibilities
name|gchar
modifier|*
name|possibilities
index|[
literal|2
index|]
decl_stmt|;
DECL|member|choice
name|gint
name|choice
decl_stmt|;
DECL|typedef|ExportAction
block|}
name|ExportAction
typedef|;
end_typedef

begin_comment
comment|/* the functions that do the actual export */
end_comment

begin_function
specifier|static
name|void
DECL|function|export_merge (gint32 image_ID,gint32 * drawable_ID)
name|export_merge
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
modifier|*
name|drawable_ID
parameter_list|)
block|{
name|gint
name|nlayers
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gint32
modifier|*
name|layers
decl_stmt|;
operator|*
name|drawable_ID
operator|=
name|gimp_image_merge_visible_layers
argument_list|(
name|image_ID
argument_list|,
name|GIMP_CLIP_TO_IMAGE
argument_list|)
expr_stmt|;
comment|/* remove any remaining (invisible) layers */
name|layers
operator|=
name|gimp_image_get_layers
argument_list|(
name|image_ID
argument_list|,
operator|&
name|nlayers
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
name|nlayers
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|layers
index|[
name|i
index|]
operator|!=
operator|*
name|drawable_ID
condition|)
name|gimp_image_remove_layer
argument_list|(
name|image_ID
argument_list|,
name|layers
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|layers
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|export_flatten (gint32 image_ID,gint32 * drawable_ID)
name|export_flatten
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
modifier|*
name|drawable_ID
parameter_list|)
block|{
operator|*
name|drawable_ID
operator|=
name|gimp_image_flatten
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|export_convert_rgb (gint32 image_ID,gint32 * drawable_ID)
name|export_convert_rgb
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
modifier|*
name|drawable_ID
parameter_list|)
block|{
name|gimp_image_convert_rgb
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|export_convert_grayscale (gint32 image_ID,gint32 * drawable_ID)
name|export_convert_grayscale
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
modifier|*
name|drawable_ID
parameter_list|)
block|{
name|gimp_image_convert_grayscale
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|export_convert_indexed (gint32 image_ID,gint32 * drawable_ID)
name|export_convert_indexed
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
modifier|*
name|drawable_ID
parameter_list|)
block|{
name|gint
name|nlayers
decl_stmt|;
comment|/* check alpha */
name|g_free
argument_list|(
name|gimp_image_get_layers
argument_list|(
name|image_ID
argument_list|,
operator|&
name|nlayers
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|nlayers
operator|>
literal|1
operator|||
name|gimp_drawable_has_alpha
argument_list|(
operator|*
name|drawable_ID
argument_list|)
condition|)
name|gimp_image_convert_indexed
argument_list|(
name|image_ID
argument_list|,
name|GIMP_FS_DITHER
argument_list|,
name|GIMP_MAKE_PALETTE
argument_list|,
literal|255
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|""
argument_list|)
expr_stmt|;
else|else
name|gimp_image_convert_indexed
argument_list|(
name|image_ID
argument_list|,
name|GIMP_FS_DITHER
argument_list|,
name|GIMP_MAKE_PALETTE
argument_list|,
literal|256
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|""
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|export_add_alpha (gint32 image_ID,gint32 * drawable_ID)
name|export_add_alpha
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
modifier|*
name|drawable_ID
parameter_list|)
block|{
name|gint
name|nlayers
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gint32
modifier|*
name|layers
decl_stmt|;
name|layers
operator|=
name|gimp_image_get_layers
argument_list|(
name|image_ID
argument_list|,
operator|&
name|nlayers
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
name|nlayers
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
operator|!
name|gimp_drawable_has_alpha
argument_list|(
name|layers
index|[
name|i
index|]
argument_list|)
condition|)
name|gimp_layer_add_alpha
argument_list|(
name|layers
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|layers
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* a set of predefined actions */
end_comment

begin_decl_stmt
DECL|variable|export_action_merge
specifier|static
name|ExportAction
name|export_action_merge
init|=
block|{
name|export_merge
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"can't handle layers"
argument_list|)
block|,
block|{
name|N_
argument_list|(
literal|"Merge visible layers"
argument_list|)
block|,
name|NULL
block|}
block|,
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|export_action_animate_or_merge
specifier|static
name|ExportAction
name|export_action_animate_or_merge
init|=
block|{
name|NULL
block|,
name|export_merge
block|,
name|N_
argument_list|(
literal|"can only handle layers as animation frames"
argument_list|)
block|,
block|{
name|N_
argument_list|(
literal|"Save as animation"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Merge visible layers"
argument_list|)
block|}
block|,
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|export_action_flatten
specifier|static
name|ExportAction
name|export_action_flatten
init|=
block|{
operator|&
name|export_flatten
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"can't handle transparency"
argument_list|)
block|,
block|{
name|N_
argument_list|(
literal|"Flatten Image"
argument_list|)
block|,
name|NULL
block|}
block|,
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|export_action_convert_rgb
specifier|static
name|ExportAction
name|export_action_convert_rgb
init|=
block|{
operator|&
name|export_convert_rgb
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"can only handle RGB images"
argument_list|)
block|,
block|{
name|N_
argument_list|(
literal|"Convert to RGB"
argument_list|)
block|,
name|NULL
block|}
block|,
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|export_action_convert_grayscale
specifier|static
name|ExportAction
name|export_action_convert_grayscale
init|=
block|{
operator|&
name|export_convert_grayscale
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"can only handle grayscale images"
argument_list|)
block|,
block|{
name|N_
argument_list|(
literal|"Convert to grayscale"
argument_list|)
block|,
name|NULL
block|}
block|,
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|export_action_convert_indexed
specifier|static
name|ExportAction
name|export_action_convert_indexed
init|=
block|{
operator|&
name|export_convert_indexed
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"can only handle indexed images"
argument_list|)
block|,
block|{
name|N_
argument_list|(
literal|"Convert to indexed using default settings\n(Do it manually to tune the result)"
argument_list|)
block|,
name|NULL
block|}
block|,
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|export_action_convert_rgb_or_grayscale
specifier|static
name|ExportAction
name|export_action_convert_rgb_or_grayscale
init|=
block|{
operator|&
name|export_convert_rgb
block|,
operator|&
name|export_convert_grayscale
block|,
name|N_
argument_list|(
literal|"can only handle RGB or grayscale images"
argument_list|)
block|,
block|{
name|N_
argument_list|(
literal|"Convert to RGB"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Convert to grayscale"
argument_list|)
block|}
block|,
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|export_action_convert_rgb_or_indexed
specifier|static
name|ExportAction
name|export_action_convert_rgb_or_indexed
init|=
block|{
operator|&
name|export_convert_rgb
block|,
operator|&
name|export_convert_indexed
block|,
name|N_
argument_list|(
literal|"can only handle RGB or indexed images"
argument_list|)
block|,
block|{
name|N_
argument_list|(
literal|"Convert to RGB"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Convert to indexed using default settings\n(Do it manually to tune the result)"
argument_list|)
block|}
block|,
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|export_action_convert_indexed_or_grayscale
specifier|static
name|ExportAction
name|export_action_convert_indexed_or_grayscale
init|=
block|{
operator|&
name|export_convert_indexed
block|,
operator|&
name|export_convert_grayscale
block|,
name|N_
argument_list|(
literal|"can only handle grayscale or indexed images"
argument_list|)
block|,
block|{
name|N_
argument_list|(
literal|"Convert to indexed using default settings\n(Do it manually to tune the result)"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Convert to grayscale"
argument_list|)
block|}
block|,
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|export_action_add_alpha
specifier|static
name|ExportAction
name|export_action_add_alpha
init|=
block|{
operator|&
name|export_add_alpha
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"needs an alpha channel"
argument_list|)
block|,
block|{
name|N_
argument_list|(
literal|"Add alpha channel"
argument_list|)
block|,
name|NULL
block|}
block|,
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* dialog functions */
end_comment

begin_decl_stmt
DECL|variable|dialog
specifier|static
name|GtkWidget
modifier|*
name|dialog
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|dialog_return
specifier|static
name|GimpExportReturnType
name|dialog_return
init|=
name|EXPORT_CANCEL
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|export_export_callback (GtkWidget * widget,gpointer data)
name|export_export_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
name|dialog_return
operator|=
name|EXPORT_EXPORT
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|export_skip_callback (GtkWidget * widget,gpointer data)
name|export_skip_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
name|dialog_return
operator|=
name|EXPORT_IGNORE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|export_cancel_callback (GtkWidget * widget,gpointer data)
name|export_cancel_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|dialog_return
operator|=
name|EXPORT_CANCEL
expr_stmt|;
name|dialog
operator|=
name|NULL
expr_stmt|;
name|gtk_main_quit
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|export_toggle_callback (GtkWidget * widget,gpointer data)
name|export_toggle_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gint
modifier|*
name|choice
init|=
operator|(
name|gint
operator|*
operator|)
name|data
decl_stmt|;
if|if
condition|(
name|gtk_toggle_button_get_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|widget
argument_list|)
argument_list|)
condition|)
operator|*
name|choice
operator|=
literal|0
expr_stmt|;
else|else
operator|*
name|choice
operator|=
literal|1
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|export_dialog (GSList * actions,gchar * format)
name|export_dialog
parameter_list|(
name|GSList
modifier|*
name|actions
parameter_list|,
name|gchar
modifier|*
name|format
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|hbbox
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
name|gchar
modifier|*
name|text
decl_stmt|;
name|ExportAction
modifier|*
name|action
decl_stmt|;
name|dialog_return
operator|=
name|EXPORT_CANCEL
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|actions
operator|!=
name|NULL
operator|&&
name|format
operator|!=
name|NULL
argument_list|,
name|dialog_return
argument_list|)
expr_stmt|;
comment|/*    *  Plug-ins have called gtk_init () before calling gimp_export ().    *  Otherwise bad things will happen now!!    */
comment|/* the dialog */
name|dialog
operator|=
name|gtk_dialog_new
argument_list|()
expr_stmt|;
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Export File"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_window_position
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"destroy"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|export_cancel_callback
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  Action area  */
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|action_area
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_set_homogeneous
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|action_area
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|hbbox
operator|=
name|gtk_hbutton_box_new
argument_list|()
expr_stmt|;
name|gtk_button_box_set_spacing
argument_list|(
name|GTK_BUTTON_BOX
argument_list|(
name|hbbox
argument_list|)
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|action_area
argument_list|)
argument_list|,
name|hbbox
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
name|hbbox
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Export"
argument_list|)
argument_list|)
expr_stmt|;
name|GTK_WIDGET_SET_FLAGS
argument_list|(
name|button
argument_list|,
name|GTK_CAN_DEFAULT
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|export_export_callback
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbbox
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
name|gtk_widget_grab_default
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Ignore"
argument_list|)
argument_list|)
expr_stmt|;
name|GTK_WIDGET_SET_FLAGS
argument_list|(
name|button
argument_list|,
name|GTK_CAN_DEFAULT
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|export_skip_callback
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbbox
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
name|button
operator|=
name|gtk_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Cancel"
argument_list|)
argument_list|)
expr_stmt|;
name|GTK_WIDGET_SET_FLAGS
argument_list|(
name|button
argument_list|,
name|GTK_CAN_DEFAULT
argument_list|)
expr_stmt|;
name|gtk_signal_connect_object
argument_list|(
name|GTK_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|gtk_widget_destroy
argument_list|,
name|GTK_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbbox
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
comment|/* the headline */
name|gtk_container_set_border_width
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
literal|6
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Your image should be exported before it can be saved for the following reasons:"
argument_list|)
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
name|gtk_label_set_justify
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|GTK_JUSTIFY_CENTER
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|label
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|actions
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
block|{
name|action
operator|=
operator|(
name|ExportAction
operator|*
operator|)
operator|(
name|list
operator|->
name|data
operator|)
expr_stmt|;
name|text
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s %s"
argument_list|,
name|format
argument_list|,
name|gettext
argument_list|(
name|action
operator|->
name|reason
argument_list|)
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|text
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|text
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|frame
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
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
if|if
condition|(
name|action
operator|->
name|possibilities
index|[
literal|0
index|]
operator|&&
name|action
operator|->
name|possibilities
index|[
literal|1
index|]
condition|)
block|{
name|GSList
modifier|*
name|radio_group
init|=
name|NULL
decl_stmt|;
name|button
operator|=
name|gtk_radio_button_new_with_label
argument_list|(
name|radio_group
argument_list|,
name|gettext
argument_list|(
name|action
operator|->
name|possibilities
index|[
literal|0
index|]
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_label_set_justify
argument_list|(
name|GTK_LABEL
argument_list|(
name|GTK_BIN
argument_list|(
name|button
argument_list|)
operator|->
name|child
argument_list|)
argument_list|,
name|GTK_JUSTIFY_LEFT
argument_list|)
expr_stmt|;
name|radio_group
operator|=
name|gtk_radio_button_group
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|button
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
name|button
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|export_toggle_callback
argument_list|,
operator|&
name|action
operator|->
name|choice
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
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_radio_button_new_with_label
argument_list|(
name|radio_group
argument_list|,
name|gettext
argument_list|(
name|action
operator|->
name|possibilities
index|[
literal|1
index|]
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_label_set_justify
argument_list|(
name|GTK_LABEL
argument_list|(
name|GTK_BIN
argument_list|(
name|button
argument_list|)
operator|->
name|child
argument_list|)
argument_list|,
name|GTK_JUSTIFY_LEFT
argument_list|)
expr_stmt|;
name|radio_group
operator|=
name|gtk_radio_button_group
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|button
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
name|button
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|action
operator|->
name|possibilities
index|[
literal|0
index|]
condition|)
block|{
name|label
operator|=
name|gtk_label_new
argument_list|(
name|gettext
argument_list|(
name|action
operator|->
name|possibilities
index|[
literal|0
index|]
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
literal|4
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|action
operator|->
name|choice
operator|=
literal|0
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|action
operator|->
name|possibilities
index|[
literal|1
index|]
condition|)
block|{
name|label
operator|=
name|gtk_label_new
argument_list|(
name|gettext
argument_list|(
name|action
operator|->
name|possibilities
index|[
literal|1
index|]
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
literal|4
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|action
operator|->
name|choice
operator|=
literal|1
expr_stmt|;
block|}
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
block|}
comment|/* the footline */
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"The export conversion won't modify your original image."
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|label
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
name|gtk_main
argument_list|()
expr_stmt|;
return|return
operator|(
name|dialog_return
operator|)
return|;
block|}
end_function

begin_function
name|GimpExportReturnType
DECL|function|gimp_export_image (gint32 * image_ID_ptr,gint32 * drawable_ID_ptr,gchar * format,gint cap)
name|gimp_export_image
parameter_list|(
name|gint32
modifier|*
name|image_ID_ptr
parameter_list|,
name|gint32
modifier|*
name|drawable_ID_ptr
parameter_list|,
name|gchar
modifier|*
name|format
parameter_list|,
name|gint
name|cap
parameter_list|)
comment|/* cap like capabilities */
block|{
name|GSList
modifier|*
name|actions
init|=
name|NULL
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
name|GimpImageBaseType
name|type
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gint
name|nlayers
decl_stmt|;
name|gint32
modifier|*
name|layers
decl_stmt|;
name|gboolean
name|added_flatten
init|=
name|FALSE
decl_stmt|;
name|ExportAction
modifier|*
name|action
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
operator|*
name|image_ID_ptr
operator|>
operator|-
literal|1
operator|&&
operator|*
name|drawable_ID_ptr
operator|>
operator|-
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/* do some sanity checks */
if|if
condition|(
name|cap
operator|&
name|NEEDS_ALPHA
condition|)
name|cap
operator||=
name|CAN_HANDLE_ALPHA
expr_stmt|;
if|if
condition|(
name|cap
operator|&
name|CAN_HANDLE_LAYERS_AS_ANIMATION
condition|)
name|cap
operator||=
name|CAN_HANDLE_LAYERS
expr_stmt|;
comment|/* check alpha */
name|layers
operator|=
name|gimp_image_get_layers
argument_list|(
operator|*
name|image_ID_ptr
argument_list|,
operator|&
name|nlayers
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
name|nlayers
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|gimp_drawable_has_alpha
argument_list|(
name|layers
index|[
name|i
index|]
argument_list|)
condition|)
block|{
if|if
condition|(
operator|!
operator|(
name|cap
operator|&
name|CAN_HANDLE_ALPHA
operator|)
condition|)
block|{
name|actions
operator|=
name|g_slist_prepend
argument_list|(
name|actions
argument_list|,
operator|&
name|export_action_flatten
argument_list|)
expr_stmt|;
name|added_flatten
operator|=
name|TRUE
expr_stmt|;
break|break;
block|}
block|}
else|else
block|{
if|if
condition|(
name|cap
operator|&
name|NEEDS_ALPHA
condition|)
block|{
name|actions
operator|=
name|g_slist_prepend
argument_list|(
name|actions
argument_list|,
operator|&
name|export_action_add_alpha
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
block|}
name|g_free
argument_list|(
name|layers
argument_list|)
expr_stmt|;
comment|/* check multiple layers */
if|if
condition|(
operator|!
name|added_flatten
operator|&&
name|nlayers
operator|>
literal|1
condition|)
block|{
if|if
condition|(
name|cap
operator|&
name|CAN_HANDLE_LAYERS_AS_ANIMATION
condition|)
name|actions
operator|=
name|g_slist_prepend
argument_list|(
name|actions
argument_list|,
operator|&
name|export_action_animate_or_merge
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
operator|!
operator|(
name|cap
operator|&
name|CAN_HANDLE_LAYERS
operator|)
condition|)
name|actions
operator|=
name|g_slist_prepend
argument_list|(
name|actions
argument_list|,
operator|&
name|export_action_merge
argument_list|)
expr_stmt|;
block|}
comment|/* check the image type */
name|type
operator|=
name|gimp_image_base_type
argument_list|(
operator|*
name|image_ID_ptr
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|type
condition|)
block|{
case|case
name|GIMP_RGB
case|:
if|if
condition|(
operator|!
operator|(
name|cap
operator|&
name|CAN_HANDLE_RGB
operator|)
condition|)
block|{
if|if
condition|(
operator|(
name|cap
operator|&
name|CAN_HANDLE_INDEXED
operator|)
operator|&&
operator|(
name|cap
operator|&
name|CAN_HANDLE_GRAY
operator|)
condition|)
name|actions
operator|=
name|g_slist_prepend
argument_list|(
name|actions
argument_list|,
operator|&
name|export_action_convert_indexed_or_grayscale
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|cap
operator|&
name|CAN_HANDLE_INDEXED
condition|)
name|actions
operator|=
name|g_slist_prepend
argument_list|(
name|actions
argument_list|,
operator|&
name|export_action_convert_indexed
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|cap
operator|&
name|CAN_HANDLE_GRAY
condition|)
name|actions
operator|=
name|g_slist_prepend
argument_list|(
name|actions
argument_list|,
operator|&
name|export_action_convert_grayscale
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_GRAY
case|:
if|if
condition|(
operator|!
operator|(
name|cap
operator|&
name|CAN_HANDLE_GRAY
operator|)
condition|)
block|{
if|if
condition|(
operator|(
name|cap
operator|&
name|CAN_HANDLE_RGB
operator|)
operator|&&
operator|(
name|cap
operator|&
name|CAN_HANDLE_INDEXED
operator|)
condition|)
name|actions
operator|=
name|g_slist_prepend
argument_list|(
name|actions
argument_list|,
operator|&
name|export_action_convert_rgb_or_indexed
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|cap
operator|&
name|CAN_HANDLE_RGB
condition|)
name|actions
operator|=
name|g_slist_prepend
argument_list|(
name|actions
argument_list|,
operator|&
name|export_action_convert_rgb
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|cap
operator|&
name|CAN_HANDLE_INDEXED
condition|)
name|actions
operator|=
name|g_slist_prepend
argument_list|(
name|actions
argument_list|,
operator|&
name|export_action_convert_indexed
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_INDEXED
case|:
if|if
condition|(
operator|!
operator|(
name|cap
operator|&
name|CAN_HANDLE_INDEXED
operator|)
condition|)
block|{
if|if
condition|(
operator|(
name|cap
operator|&
name|CAN_HANDLE_RGB
operator|)
operator|&&
operator|(
name|cap
operator|&
name|CAN_HANDLE_GRAY
operator|)
condition|)
name|actions
operator|=
name|g_slist_prepend
argument_list|(
name|actions
argument_list|,
operator|&
name|export_action_convert_rgb_or_grayscale
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|cap
operator|&
name|CAN_HANDLE_RGB
condition|)
name|actions
operator|=
name|g_slist_prepend
argument_list|(
name|actions
argument_list|,
operator|&
name|export_action_convert_rgb
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|cap
operator|&
name|CAN_HANDLE_GRAY
condition|)
name|actions
operator|=
name|g_slist_prepend
argument_list|(
name|actions
argument_list|,
operator|&
name|export_action_convert_grayscale
argument_list|)
expr_stmt|;
block|}
break|break;
block|}
if|if
condition|(
name|actions
condition|)
block|{
name|actions
operator|=
name|g_slist_reverse
argument_list|(
name|actions
argument_list|)
expr_stmt|;
name|dialog_return
operator|=
name|export_dialog
argument_list|(
name|actions
argument_list|,
name|format
argument_list|)
expr_stmt|;
block|}
else|else
name|dialog_return
operator|=
name|EXPORT_IGNORE
expr_stmt|;
if|if
condition|(
name|dialog_return
operator|==
name|EXPORT_EXPORT
condition|)
block|{
operator|*
name|image_ID_ptr
operator|=
name|gimp_image_duplicate
argument_list|(
operator|*
name|image_ID_ptr
argument_list|)
expr_stmt|;
operator|*
name|drawable_ID_ptr
operator|=
name|gimp_image_get_active_layer
argument_list|(
operator|*
name|image_ID_ptr
argument_list|)
expr_stmt|;
name|gimp_image_undo_disable
argument_list|(
operator|*
name|image_ID_ptr
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|actions
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
block|{
name|action
operator|=
operator|(
name|ExportAction
operator|*
operator|)
operator|(
name|list
operator|->
name|data
operator|)
expr_stmt|;
if|if
condition|(
name|action
operator|->
name|choice
operator|==
literal|0
operator|&&
name|action
operator|->
name|default_action
condition|)
name|action
operator|->
name|default_action
argument_list|(
operator|*
name|image_ID_ptr
argument_list|,
name|drawable_ID_ptr
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|action
operator|->
name|choice
operator|==
literal|1
operator|&&
name|action
operator|->
name|alt_action
condition|)
name|action
operator|->
name|alt_action
argument_list|(
operator|*
name|image_ID_ptr
argument_list|,
name|drawable_ID_ptr
argument_list|)
expr_stmt|;
block|}
block|}
name|g_slist_free
argument_list|(
name|actions
argument_list|)
expr_stmt|;
return|return
operator|(
name|dialog_return
operator|)
return|;
block|}
end_function

end_unit

