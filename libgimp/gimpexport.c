begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpexport.c  * Copyright (C) 1999-2000 Sven Neumann<sven@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
file|"gimpdialog.h"
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
file|"libgimp-intl.h"
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
DECL|struct|__anon28bfa86f0108
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
name|gint32
name|nlayers
decl_stmt|;
name|gint32
name|nvisible
init|=
literal|0
decl_stmt|;
name|gint32
name|i
decl_stmt|;
name|gint32
modifier|*
name|layers
decl_stmt|;
name|gint32
name|visible
init|=
operator|*
name|drawable_ID
decl_stmt|;
name|gint32
name|merged
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
name|gimp_drawable_visible
argument_list|(
name|layers
index|[
name|i
index|]
argument_list|)
condition|)
block|{
name|nvisible
operator|++
expr_stmt|;
name|visible
operator|=
name|layers
index|[
name|i
index|]
expr_stmt|;
block|}
block|}
if|if
condition|(
name|nvisible
operator|==
literal|1
operator|&&
operator|*
name|drawable_ID
operator|!=
name|visible
condition|)
operator|*
name|drawable_ID
operator|=
name|visible
expr_stmt|;
if|if
condition|(
name|nvisible
operator|>
literal|1
condition|)
block|{
name|g_free
argument_list|(
name|layers
argument_list|)
expr_stmt|;
name|merged
operator|=
name|gimp_image_merge_visible_layers
argument_list|(
name|image_ID
argument_list|,
name|GIMP_CLIP_TO_IMAGE
argument_list|)
expr_stmt|;
if|if
condition|(
name|merged
operator|!=
operator|-
literal|1
condition|)
operator|*
name|drawable_ID
operator|=
name|merged
expr_stmt|;
else|else
return|return;
comment|/* shouldn't happen */
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
block|}
comment|/* remove any remaining (invisible) layers */
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
name|gint32
name|flattened
decl_stmt|;
name|flattened
operator|=
name|gimp_image_flatten
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
if|if
condition|(
name|flattened
operator|!=
operator|-
literal|1
condition|)
operator|*
name|drawable_ID
operator|=
name|flattened
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
name|gint32
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
name|gint32
name|nlayers
decl_stmt|;
name|gint32
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
literal|"can't Handle Layers"
argument_list|)
block|,
block|{
name|N_
argument_list|(
literal|"Merge Visible Layers"
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
literal|"can only Handle Layers as Animation Frames"
argument_list|)
block|,
block|{
name|N_
argument_list|(
literal|"Save as Animation"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Merge Visible Layers"
argument_list|)
block|}
block|,
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|export_action_animate_or_flatten
specifier|static
name|ExportAction
name|export_action_animate_or_flatten
init|=
block|{
name|NULL
block|,
name|export_flatten
block|,
name|N_
argument_list|(
literal|"can only Handle Layers as Animation Frames"
argument_list|)
block|,
block|{
name|N_
argument_list|(
literal|"Save as Animation"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Flatten"
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
name|export_flatten
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"can't Handle Transparency"
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
name|export_convert_rgb
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"can only Handle RGB Images"
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
name|export_convert_grayscale
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"can only Handle Grayscale Images"
argument_list|)
block|,
block|{
name|N_
argument_list|(
literal|"Convert to Grayscale"
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
name|export_convert_indexed
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"can only Handle Indexed Images"
argument_list|)
block|,
block|{
name|N_
argument_list|(
literal|"Convert to indexed using default settings\n"
literal|"(Do it manually to tune the result)"
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
name|export_convert_rgb
block|,
name|export_convert_grayscale
block|,
name|N_
argument_list|(
literal|"can only Handle RGB or Grayscale Images"
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
literal|"Convert to Grayscale"
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
name|export_convert_rgb
block|,
name|export_convert_indexed
block|,
name|N_
argument_list|(
literal|"can only Handle RGB or Indexed Images"
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
literal|"Convert to indexed using default settings\n"
literal|"(Do it manually to tune the result)"
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
name|export_convert_indexed
block|,
name|export_convert_grayscale
block|,
name|N_
argument_list|(
literal|"can only Handle Grayscale or Indexed Images"
argument_list|)
block|,
block|{
name|N_
argument_list|(
literal|"Convert to indexed using default settings\n"
literal|"(Do it manually to tune the result)"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Convert to Grayscale"
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
name|export_add_alpha
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"needs an Alpha Channel"
argument_list|)
block|,
block|{
name|N_
argument_list|(
literal|"Add Alpha Channel"
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
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Export File"
argument_list|)
argument_list|,
literal|"export_file"
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"dialogs/export_file.html"
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|_
argument_list|(
literal|"Export"
argument_list|)
argument_list|,
name|export_export_callback
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|_
argument_list|(
literal|"Ignore"
argument_list|)
argument_list|,
name|export_skip_callback
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|_
argument_list|(
literal|"Cancel"
argument_list|)
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
name|NULL
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
name|GTK_SIGNAL_FUNC
argument_list|(
name|export_cancel_callback
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* the headline */
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
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|vbox
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Your image should be exported before it "
literal|"can be saved for the following reasons:"
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
name|vbox
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
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
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
literal|0
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
name|GTK_SIGNAL_FUNC
argument_list|(
name|export_toggle_callback
argument_list|)
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
literal|0
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
literal|2
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
literal|2
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
name|vbox
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
name|gtk_widget_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
name|gtk_main
argument_list|()
expr_stmt|;
return|return
name|dialog_return
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_export_image:  * @image_ID: Pointer to the image_ID.  * @drawable_ID: Pointer to the drawable_ID.  * @format_name: The (short) name of the image_format (e.g. JPEG or GIF).  * @capabilities: What can the image_format do?  *  * Takes an image and a drawable to be saved together with a  * description of the capabilities of the image_format. If the  * type of image doesn't match the capabilities of the format  * a dialog is opened that informs the user that the image has  * to be exported and offers to do the necessary conversions.  *  * If the user chooses to export the image, a copy is created.  * This copy is then converted, the image_ID and drawable_ID  * are changed to point to the new image and the procedure returns  * EXPORT_EXPORT. The save_plugin has to take care of deleting the  * created image using gimp_image_delete() when it has saved it.  *  * If the user chooses to Ignore the export problem, the image_ID  * and drawable_ID is not altered, EXPORT_IGNORE is returned and   * the save_plugin should try to save the original image. If the   * user chooses Cancel, EXPORT_CANCEL is returned and the   * save_plugin should quit itself with status #STATUS_CANCEL.  *  * Returns: An enum of #GimpExportReturnType describing the user_action.  */
end_comment

begin_function
name|GimpExportReturnType
DECL|function|gimp_export_image (gint32 * image_ID,gint32 * drawable_ID,gchar * format_name,GimpExportCapabilities capabilities)
name|gimp_export_image
parameter_list|(
name|gint32
modifier|*
name|image_ID
parameter_list|,
name|gint32
modifier|*
name|drawable_ID
parameter_list|,
name|gchar
modifier|*
name|format_name
parameter_list|,
name|GimpExportCapabilities
name|capabilities
parameter_list|)
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
name|gint32
name|i
decl_stmt|;
name|gint32
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
name|gboolean
name|background_has_alpha
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
name|image_ID
operator|>
operator|-
literal|1
operator|&&
operator|*
name|drawable_ID
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
name|capabilities
operator|&
name|NEEDS_ALPHA
condition|)
name|capabilities
operator||=
name|CAN_HANDLE_ALPHA
expr_stmt|;
if|if
condition|(
name|capabilities
operator|&
name|CAN_HANDLE_LAYERS_AS_ANIMATION
condition|)
name|capabilities
operator||=
name|CAN_HANDLE_LAYERS
expr_stmt|;
comment|/* check alpha */
name|layers
operator|=
name|gimp_image_get_layers
argument_list|(
operator|*
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
name|i
operator|==
name|nlayers
operator|-
literal|1
condition|)
name|background_has_alpha
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|capabilities
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
name|capabilities
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
name|capabilities
operator|&
name|CAN_HANDLE_LAYERS_AS_ANIMATION
condition|)
block|{
if|if
condition|(
name|background_has_alpha
operator|||
name|capabilities
operator|&
name|NEEDS_ALPHA
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
else|else
name|actions
operator|=
name|g_slist_prepend
argument_list|(
name|actions
argument_list|,
operator|&
name|export_action_animate_or_flatten
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
operator|(
name|capabilities
operator|&
name|CAN_HANDLE_LAYERS
operator|)
condition|)
block|{
if|if
condition|(
name|background_has_alpha
operator|||
name|capabilities
operator|&
name|NEEDS_ALPHA
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
else|else
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
block|}
block|}
comment|/* check the image type */
name|type
operator|=
name|gimp_image_base_type
argument_list|(
operator|*
name|image_ID
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
name|capabilities
operator|&
name|CAN_HANDLE_RGB
operator|)
condition|)
block|{
if|if
condition|(
operator|(
name|capabilities
operator|&
name|CAN_HANDLE_INDEXED
operator|)
operator|&&
operator|(
name|capabilities
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
name|capabilities
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
name|capabilities
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
name|capabilities
operator|&
name|CAN_HANDLE_GRAY
operator|)
condition|)
block|{
if|if
condition|(
operator|(
name|capabilities
operator|&
name|CAN_HANDLE_RGB
operator|)
operator|&&
operator|(
name|capabilities
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
name|capabilities
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
name|capabilities
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
name|capabilities
operator|&
name|CAN_HANDLE_INDEXED
operator|)
condition|)
block|{
if|if
condition|(
operator|(
name|capabilities
operator|&
name|CAN_HANDLE_RGB
operator|)
operator|&&
operator|(
name|capabilities
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
name|capabilities
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
name|capabilities
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
name|format_name
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
name|image_ID
operator|=
name|gimp_image_duplicate
argument_list|(
operator|*
name|image_ID
argument_list|)
expr_stmt|;
operator|*
name|drawable_ID
operator|=
name|gimp_image_get_active_layer
argument_list|(
operator|*
name|image_ID
argument_list|)
expr_stmt|;
name|gimp_image_undo_disable
argument_list|(
operator|*
name|image_ID
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
name|image_ID
argument_list|,
name|drawable_ID
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
name|image_ID
argument_list|,
name|drawable_ID
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
name|dialog_return
return|;
block|}
end_function

end_unit

