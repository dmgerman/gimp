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
file|"actions-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpguiconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/core-enums.h"
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
file|"core/gimpimage-convert.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-crop.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-duplicate.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-flip.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-merge.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-resize.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-rotate.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-scale.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-undo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdock.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpmessagebox.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpmessagedialog.h"
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
file|"dialogs/convert-dialog.h"
end_include

begin_include
include|#
directive|include
file|"dialogs/dialogs.h"
end_include

begin_include
include|#
directive|include
file|"dialogs/grid-dialog.h"
end_include

begin_include
include|#
directive|include
file|"dialogs/image-merge-layers-dialog.h"
end_include

begin_include
include|#
directive|include
file|"dialogs/image-new-dialog.h"
end_include

begin_include
include|#
directive|include
file|"dialogs/resize-dialog.h"
end_include

begin_include
include|#
directive|include
file|"actions.h"
end_include

begin_include
include|#
directive|include
file|"image-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_typedef
DECL|typedef|ImageResizeOptions
typedef|typedef
name|struct
name|_ImageResizeOptions
name|ImageResizeOptions
typedef|;
end_typedef

begin_struct
DECL|struct|_ImageResizeOptions
struct|struct
name|_ImageResizeOptions
block|{
DECL|member|dialog
name|ResizeDialog
modifier|*
name|dialog
decl_stmt|;
DECL|member|context
name|GimpContext
modifier|*
name|context
decl_stmt|;
DECL|member|gdisp
name|GimpDisplay
modifier|*
name|gdisp
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
name|image_resize_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|image_scale_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|image_scale_confirm_large
parameter_list|(
name|ImageResizeOptions
modifier|*
name|options
parameter_list|,
name|gint64
name|new_memsize
parameter_list|,
name|gint64
name|max_memsize
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|image_scale_confirm_small
parameter_list|(
name|ImageResizeOptions
modifier|*
name|options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|image_scale_confirm_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|ImageResizeOptions
modifier|*
name|options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|image_scale_implement
parameter_list|(
name|ImageResizeOptions
modifier|*
name|options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|image_merge_layers_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|ImageMergeLayersDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|image_new_cmd_callback (GtkAction * action,gpointer data)
name|image_new_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|return_if_no_widget
argument_list|(
name|widget
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|gimp_dialog_factory_dialog_new
argument_list|(
name|global_dialog_factory
argument_list|,
name|gtk_widget_get_screen
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"gimp-image-new-dialog"
argument_list|,
operator|-
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|dialog
condition|)
block|{
name|image_new_dialog_set
argument_list|(
name|dialog
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|image_new_from_image_cmd_callback (GtkAction * action,gpointer data)
name|image_new_from_image_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|return_if_no_widget
argument_list|(
name|widget
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|gimp_dialog_factory_dialog_new
argument_list|(
name|global_dialog_factory
argument_list|,
name|gtk_widget_get_screen
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"gimp-image-new-dialog"
argument_list|,
operator|-
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|dialog
condition|)
block|{
name|GimpImage
modifier|*
name|gimage
init|=
name|action_data_get_image
argument_list|(
name|data
argument_list|)
decl_stmt|;
if|if
condition|(
name|gimage
condition|)
name|image_new_dialog_set
argument_list|(
name|dialog
argument_list|,
name|gimage
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|image_convert_cmd_callback (GtkAction * action,gint value,gpointer data)
name|image_convert_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gint
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
name|return_if_no_image
argument_list|(
name|gimage
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|return_if_no_widget
argument_list|(
name|widget
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
switch|switch
condition|(
operator|(
name|GimpImageBaseType
operator|)
name|value
condition|)
block|{
case|case
name|GIMP_RGB
case|:
case|case
name|GIMP_GRAY
case|:
name|gimp_image_convert
argument_list|(
name|gimage
argument_list|,
operator|(
name|GimpImageBaseType
operator|)
name|value
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_INDEXED
case|:
name|gtk_widget_show
argument_list|(
name|convert_dialog_new
argument_list|(
name|gimage
argument_list|,
name|widget
argument_list|,
name|GIMP_PROGRESS
argument_list|(
name|gdisp
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
name|void
DECL|function|image_resize_cmd_callback (GtkAction * action,gpointer data)
name|image_resize_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|ImageResizeOptions
modifier|*
name|options
decl_stmt|;
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimage
operator|=
name|gdisp
operator|->
name|gimage
expr_stmt|;
name|options
operator|=
name|g_new0
argument_list|(
name|ImageResizeOptions
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|options
operator|->
name|context
operator|=
name|action_data_get_context
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|options
operator|->
name|gdisp
operator|=
name|gdisp
expr_stmt|;
name|options
operator|->
name|gimage
operator|=
name|gimage
expr_stmt|;
name|options
operator|->
name|dialog
operator|=
name|resize_dialog_new
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|gdisp
operator|->
name|shell
argument_list|,
name|RESIZE_DIALOG
argument_list|,
name|gimage
operator|->
name|width
argument_list|,
name|gimage
operator|->
name|height
argument_list|,
name|gimage
operator|->
name|xresolution
argument_list|,
name|gimage
operator|->
name|yresolution
argument_list|,
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
operator|->
name|unit
argument_list|,
name|G_CALLBACK
argument_list|(
name|image_resize_callback
argument_list|)
argument_list|,
name|options
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|gdisp
argument_list|,
literal|"disconnect"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_widget_destroy
argument_list|)
argument_list|,
name|options
operator|->
name|dialog
operator|->
name|shell
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
name|g_object_weak_ref
argument_list|(
name|G_OBJECT
argument_list|(
name|options
operator|->
name|dialog
operator|->
name|shell
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
name|gtk_widget_show
argument_list|(
name|options
operator|->
name|dialog
operator|->
name|shell
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|image_resize_to_layers_cmd_callback (GtkAction * action,gpointer data)
name|image_resize_to_layers_cmd_callback
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
name|GimpProgress
modifier|*
name|progress
decl_stmt|;
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|progress
operator|=
name|gimp_progress_start
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|gdisp
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Resizing..."
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_image_resize_to_layers
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|action_data_get_context
argument_list|(
name|data
argument_list|)
argument_list|,
name|progress
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
condition|)
name|gimp_progress_end
argument_list|(
name|progress
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|image_scale_cmd_callback (GtkAction * action,gpointer data)
name|image_scale_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|ImageResizeOptions
modifier|*
name|options
decl_stmt|;
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimage
operator|=
name|gdisp
operator|->
name|gimage
expr_stmt|;
name|options
operator|=
name|g_new0
argument_list|(
name|ImageResizeOptions
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|options
operator|->
name|context
operator|=
name|action_data_get_context
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|options
operator|->
name|gdisp
operator|=
name|gdisp
expr_stmt|;
name|options
operator|->
name|gimage
operator|=
name|gimage
expr_stmt|;
name|options
operator|->
name|dialog
operator|=
name|resize_dialog_new
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|gdisp
operator|->
name|shell
argument_list|,
name|SCALE_DIALOG
argument_list|,
name|gimage
operator|->
name|width
argument_list|,
name|gimage
operator|->
name|height
argument_list|,
name|gimage
operator|->
name|xresolution
argument_list|,
name|gimage
operator|->
name|yresolution
argument_list|,
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
operator|->
name|unit
argument_list|,
name|G_CALLBACK
argument_list|(
name|image_scale_callback
argument_list|)
argument_list|,
name|options
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|gdisp
argument_list|,
literal|"disconnect"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_widget_destroy
argument_list|)
argument_list|,
name|options
operator|->
name|dialog
operator|->
name|shell
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
name|g_object_weak_ref
argument_list|(
name|G_OBJECT
argument_list|(
name|options
operator|->
name|dialog
operator|->
name|shell
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
name|gtk_widget_show
argument_list|(
name|options
operator|->
name|dialog
operator|->
name|shell
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|image_flip_cmd_callback (GtkAction * action,gint value,gpointer data)
name|image_flip_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gint
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
name|GimpProgress
modifier|*
name|progress
decl_stmt|;
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|progress
operator|=
name|gimp_progress_start
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|gdisp
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Flipping..."
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_image_flip
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|action_data_get_context
argument_list|(
name|data
argument_list|)
argument_list|,
operator|(
name|GimpOrientationType
operator|)
name|value
argument_list|,
name|progress
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
condition|)
name|gimp_progress_end
argument_list|(
name|progress
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|image_rotate_cmd_callback (GtkAction * action,gint value,gpointer data)
name|image_rotate_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gint
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
name|GimpProgress
modifier|*
name|progress
decl_stmt|;
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|progress
operator|=
name|gimp_progress_start
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|gdisp
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Rotating..."
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_image_rotate
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|action_data_get_context
argument_list|(
name|data
argument_list|)
argument_list|,
operator|(
name|GimpRotationType
operator|)
name|value
argument_list|,
name|progress
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
condition|)
name|gimp_progress_end
argument_list|(
name|progress
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|image_crop_cmd_callback (GtkAction * action,gpointer data)
name|image_crop_cmd_callback
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
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|return_if_no_image
argument_list|(
name|gimage
argument_list|,
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_channel_bounds
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Cannot crop because the current selection is empty."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|gimp_image_crop
argument_list|(
name|gimage
argument_list|,
name|action_data_get_context
argument_list|(
name|data
argument_list|)
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|,
name|FALSE
argument_list|,
name|TRUE
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
DECL|function|image_duplicate_cmd_callback (GtkAction * action,gpointer data)
name|image_duplicate_cmd_callback
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
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|GimpImage
modifier|*
name|new_gimage
decl_stmt|;
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|new_gimage
operator|=
name|gimp_image_duplicate
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|gimp_create_display
argument_list|(
name|new_gimage
operator|->
name|gimp
argument_list|,
name|new_gimage
argument_list|,
name|shell
operator|->
name|unit
argument_list|,
name|shell
operator|->
name|scale
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|new_gimage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|image_merge_layers_cmd_callback (GtkAction * action,gpointer data)
name|image_merge_layers_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|ImageMergeLayersDialog
modifier|*
name|dialog
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|return_if_no_image
argument_list|(
name|gimage
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|return_if_no_widget
argument_list|(
name|widget
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|image_merge_layers_dialog_new
argument_list|(
name|gimage
argument_list|,
name|action_data_get_context
argument_list|(
name|data
argument_list|)
argument_list|,
name|widget
argument_list|,
name|GIMP_EXPAND_AS_NECESSARY
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
name|image_merge_layers_response
argument_list|)
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
operator|->
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|image_flatten_image_cmd_callback (GtkAction * action,gpointer data)
name|image_flatten_image_cmd_callback
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
name|return_if_no_image
argument_list|(
name|gimage
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_image_flatten
argument_list|(
name|gimage
argument_list|,
name|action_data_get_context
argument_list|(
name|data
argument_list|)
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
DECL|function|image_configure_grid_cmd_callback (GtkAction * action,gpointer data)
name|image_configure_grid_cmd_callback
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
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|gimage
operator|=
name|gdisp
operator|->
name|gimage
expr_stmt|;
if|if
condition|(
operator|!
name|shell
operator|->
name|grid_dialog
condition|)
block|{
name|shell
operator|->
name|grid_dialog
operator|=
name|grid_dialog_new
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|gtk_window_set_transient_for
argument_list|(
name|GTK_WINDOW
argument_list|(
name|shell
operator|->
name|grid_dialog
argument_list|)
argument_list|,
name|GTK_WINDOW
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_window_set_destroy_with_parent
argument_list|(
name|GTK_WINDOW
argument_list|(
name|shell
operator|->
name|grid_dialog
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_object_add_weak_pointer
argument_list|(
name|G_OBJECT
argument_list|(
name|shell
operator|->
name|grid_dialog
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|*
operator|)
operator|&
name|shell
operator|->
name|grid_dialog
argument_list|)
expr_stmt|;
block|}
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|shell
operator|->
name|grid_dialog
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
DECL|function|image_resize_callback (GtkWidget * widget,gpointer data)
name|image_resize_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|ImageResizeOptions
modifier|*
name|options
init|=
name|data
decl_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|options
operator|->
name|dialog
operator|->
name|shell
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|options
operator|->
name|dialog
operator|->
name|width
operator|>
literal|0
operator|&&
name|options
operator|->
name|dialog
operator|->
name|height
operator|>
literal|0
condition|)
block|{
name|GimpProgress
modifier|*
name|progress
decl_stmt|;
name|progress
operator|=
name|gimp_progress_start
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|options
operator|->
name|gdisp
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Resizing..."
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_image_resize
argument_list|(
name|options
operator|->
name|gimage
argument_list|,
name|options
operator|->
name|context
argument_list|,
name|options
operator|->
name|dialog
operator|->
name|width
argument_list|,
name|options
operator|->
name|dialog
operator|->
name|height
argument_list|,
name|options
operator|->
name|dialog
operator|->
name|offset_x
argument_list|,
name|options
operator|->
name|dialog
operator|->
name|offset_y
argument_list|,
name|progress
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
condition|)
name|gimp_progress_end
argument_list|(
name|progress
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
else|else
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Resize Error: Both width and height must be "
literal|"greater than zero."
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_destroy
argument_list|(
name|options
operator|->
name|dialog
operator|->
name|shell
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|image_scale_callback (GtkWidget * widget,gpointer data)
name|image_scale_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|ImageResizeOptions
modifier|*
name|options
init|=
name|data
decl_stmt|;
name|GimpImageScaleCheckType
name|scale_check
decl_stmt|;
name|gint64
name|max_memsize
decl_stmt|;
name|gint64
name|new_memsize
decl_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|options
operator|->
name|dialog
operator|->
name|shell
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|max_memsize
operator|=
name|GIMP_GUI_CONFIG
argument_list|(
name|options
operator|->
name|gimage
operator|->
name|gimp
operator|->
name|config
argument_list|)
operator|->
name|max_new_image_size
expr_stmt|;
name|scale_check
operator|=
name|gimp_image_scale_check
argument_list|(
name|options
operator|->
name|gimage
argument_list|,
name|options
operator|->
name|dialog
operator|->
name|width
argument_list|,
name|options
operator|->
name|dialog
operator|->
name|height
argument_list|,
name|max_memsize
argument_list|,
operator|&
name|new_memsize
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|scale_check
condition|)
block|{
case|case
name|GIMP_IMAGE_SCALE_TOO_BIG
case|:
name|image_scale_confirm_large
argument_list|(
name|options
argument_list|,
name|new_memsize
argument_list|,
name|max_memsize
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_IMAGE_SCALE_TOO_SMALL
case|:
name|image_scale_confirm_small
argument_list|(
name|options
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_IMAGE_SCALE_OK
case|:
comment|/* If all is well, return directly after scaling image. */
name|image_scale_implement
argument_list|(
name|options
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|options
operator|->
name|dialog
operator|->
name|shell
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|image_scale_confirm_dialog (ImageResizeOptions * options)
name|image_scale_confirm_dialog
parameter_list|(
name|ImageResizeOptions
modifier|*
name|options
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|dialog
operator|=
name|gimp_message_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Confirm Scaling"
argument_list|)
argument_list|,
name|GIMP_STOCK_WARNING
argument_list|,
name|options
operator|->
name|dialog
operator|->
name|shell
argument_list|,
name|GTK_DIALOG_DESTROY_WITH_PARENT
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_IMAGE_SCALE_WARNING
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|GIMP_STOCK_SCALE
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
name|image_scale_confirm_response
argument_list|)
argument_list|,
name|options
argument_list|)
expr_stmt|;
return|return
name|dialog
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|image_scale_confirm_large (ImageResizeOptions * options,gint64 new_memsize,gint64 max_memsize)
name|image_scale_confirm_large
parameter_list|(
name|ImageResizeOptions
modifier|*
name|options
parameter_list|,
name|gint64
name|new_memsize
parameter_list|,
name|gint64
name|max_memsize
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
init|=
name|image_scale_confirm_dialog
argument_list|(
name|options
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|size
decl_stmt|;
name|size
operator|=
name|gimp_memsize_to_string
argument_list|(
name|new_memsize
argument_list|)
expr_stmt|;
name|gimp_message_box_set_primary_text
argument_list|(
name|GIMP_MESSAGE_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|box
argument_list|,
name|_
argument_list|(
literal|"You are trying to create an image "
literal|"with a size of %s."
argument_list|)
argument_list|,
name|size
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|size
argument_list|)
expr_stmt|;
name|size
operator|=
name|gimp_memsize_to_string
argument_list|(
name|max_memsize
argument_list|)
expr_stmt|;
name|gimp_message_box_set_text
argument_list|(
name|GIMP_MESSAGE_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|box
argument_list|,
name|_
argument_list|(
literal|"Scaling the image to the choosen size will "
literal|"make it use more memory than what is "
literal|"configured as \"Maximum Image Size\" in the "
literal|"Preferences dialog (currently %s)."
argument_list|)
argument_list|,
name|size
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|size
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|image_scale_confirm_small (ImageResizeOptions * options)
name|image_scale_confirm_small
parameter_list|(
name|ImageResizeOptions
modifier|*
name|options
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
init|=
name|image_scale_confirm_dialog
argument_list|(
name|options
argument_list|)
decl_stmt|;
name|gimp_message_box_set_primary_text
argument_list|(
name|GIMP_MESSAGE_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|box
argument_list|,
name|_
argument_list|(
literal|"Scaling the image to the choosen size "
literal|"will shrink some layers completely "
literal|"away."
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_message_box_set_text
argument_list|(
name|GIMP_MESSAGE_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|box
argument_list|,
name|_
argument_list|(
literal|"Is this what you want to do?"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|image_scale_confirm_response (GtkWidget * dialog,gint response_id,ImageResizeOptions * options)
name|image_scale_confirm_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|ImageResizeOptions
modifier|*
name|options
parameter_list|)
block|{
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
if|if
condition|(
name|response_id
operator|==
name|GTK_RESPONSE_OK
condition|)
block|{
name|image_scale_implement
argument_list|(
name|options
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|options
operator|->
name|dialog
operator|->
name|shell
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_widget_set_sensitive
argument_list|(
name|options
operator|->
name|dialog
operator|->
name|shell
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|image_scale_implement (ImageResizeOptions * options)
name|image_scale_implement
parameter_list|(
name|ImageResizeOptions
modifier|*
name|options
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
init|=
name|options
operator|->
name|gimage
decl_stmt|;
if|if
condition|(
name|options
operator|->
name|dialog
operator|->
name|resolution_x
operator|==
name|gimage
operator|->
name|xresolution
operator|&&
name|options
operator|->
name|dialog
operator|->
name|resolution_y
operator|==
name|gimage
operator|->
name|yresolution
operator|&&
name|options
operator|->
name|dialog
operator|->
name|unit
operator|==
name|gimage
operator|->
name|resolution_unit
operator|&&
name|options
operator|->
name|dialog
operator|->
name|width
operator|==
name|gimage
operator|->
name|width
operator|&&
name|options
operator|->
name|dialog
operator|->
name|height
operator|==
name|gimage
operator|->
name|height
condition|)
return|return;
name|gimp_image_undo_group_start
argument_list|(
name|gimage
argument_list|,
name|GIMP_UNDO_GROUP_IMAGE_SCALE
argument_list|,
name|_
argument_list|(
literal|"Scale Image"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_set_resolution
argument_list|(
name|gimage
argument_list|,
name|options
operator|->
name|dialog
operator|->
name|resolution_x
argument_list|,
name|options
operator|->
name|dialog
operator|->
name|resolution_y
argument_list|)
expr_stmt|;
name|gimp_image_set_unit
argument_list|(
name|gimage
argument_list|,
name|options
operator|->
name|dialog
operator|->
name|unit
argument_list|)
expr_stmt|;
if|if
condition|(
name|options
operator|->
name|dialog
operator|->
name|width
operator|!=
name|gimage
operator|->
name|width
operator|||
name|options
operator|->
name|dialog
operator|->
name|height
operator|!=
name|gimage
operator|->
name|height
condition|)
block|{
if|if
condition|(
name|options
operator|->
name|dialog
operator|->
name|width
operator|>
literal|0
operator|&&
name|options
operator|->
name|dialog
operator|->
name|height
operator|>
literal|0
condition|)
block|{
name|GimpProgress
modifier|*
name|progress
decl_stmt|;
name|progress
operator|=
name|gimp_progress_start
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|options
operator|->
name|gdisp
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Scaling..."
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_image_scale
argument_list|(
name|gimage
argument_list|,
name|options
operator|->
name|dialog
operator|->
name|width
argument_list|,
name|options
operator|->
name|dialog
operator|->
name|height
argument_list|,
name|options
operator|->
name|dialog
operator|->
name|interpolation
argument_list|,
name|progress
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
condition|)
name|gimp_progress_end
argument_list|(
name|progress
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Scale Error: Both width and height must be "
literal|"greater than zero."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
name|gimp_image_undo_group_end
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
end_function

begin_function
specifier|static
name|void
DECL|function|image_merge_layers_response (GtkWidget * widget,gint response_id,ImageMergeLayersDialog * dialog)
name|image_merge_layers_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|ImageMergeLayersDialog
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
name|gimp_image_merge_visible_layers
argument_list|(
name|dialog
operator|->
name|gimage
argument_list|,
name|dialog
operator|->
name|context
argument_list|,
name|dialog
operator|->
name|merge_type
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|dialog
operator|->
name|gimage
argument_list|)
expr_stmt|;
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

end_unit

