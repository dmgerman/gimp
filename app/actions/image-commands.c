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
file|"libgimpbase/gimputils.h"
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
file|"display/gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"gui/convert-dialog.h"
end_include

begin_include
include|#
directive|include
file|"gui/grid-dialog.h"
end_include

begin_include
include|#
directive|include
file|"gui/resize-dialog.h"
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
typedef|typedef
struct|struct
DECL|struct|__anon29c0033b0108
block|{
DECL|member|resize
name|Resize
modifier|*
name|resize
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
DECL|typedef|ImageResize
block|}
name|ImageResize
typedef|;
end_typedef

begin_define
DECL|macro|return_if_no_display (gdisp,data)
define|#
directive|define
name|return_if_no_display
parameter_list|(
name|gdisp
parameter_list|,
name|data
parameter_list|)
define|\
value|if (GIMP_IS_DISPLAY (data)) \     gdisp = data; \   else if (GIMP_IS_GIMP (data)) \     gdisp = gimp_context_get_display (gimp_get_user_context (GIMP (data))); \   else if (GIMP_IS_DOCK (data)) \     gdisp = gimp_context_get_display (((GimpDock *) data)->context); \   else \     gdisp = NULL; \   if (! gdisp) \     return
end_define

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
value|if (GIMP_IS_DISPLAY (data)) \     gimage = ((GimpDisplay *) data)->gimage; \   else if (GIMP_IS_GIMP (data)) \     gimage = gimp_context_get_image (gimp_get_user_context (GIMP (data))); \   else if (GIMP_IS_DOCK (data)) \     gimage = gimp_context_get_image (((GimpDock *) data)->context); \   else \     gimage = NULL; \   if (! gimage) \     return
end_define

begin_comment
comment|/*  local functions  */
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
name|image_scale_warn
parameter_list|(
name|ImageResize
modifier|*
name|image_scale
parameter_list|,
specifier|const
name|gchar
modifier|*
name|warning_title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|warning_message
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|image_scale_warn_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gboolean
name|do_scale
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|image_scale_implement
parameter_list|(
name|ImageResize
modifier|*
name|image_scale
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|image_convert_rgb_cmd_callback (GtkAction * action,gpointer data)
name|image_convert_rgb_cmd_callback
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
name|gimp_image_convert
argument_list|(
name|gimage
argument_list|,
name|GIMP_RGB
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
DECL|function|image_convert_grayscale_cmd_callback (GtkAction * action,gpointer data)
name|image_convert_grayscale_cmd_callback
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
name|gimp_image_convert
argument_list|(
name|gimage
argument_list|,
name|GIMP_GRAY
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
DECL|function|image_convert_indexed_cmd_callback (GtkAction * action,gpointer data)
name|image_convert_indexed_cmd_callback
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
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|convert_dialog_new
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
name|gtk_widget_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
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
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|ImageResize
modifier|*
name|image_resize
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
name|image_resize
operator|=
name|g_new0
argument_list|(
name|ImageResize
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|image_resize
operator|->
name|gdisp
operator|=
name|gdisp
expr_stmt|;
name|image_resize
operator|->
name|gimage
operator|=
name|gimage
expr_stmt|;
name|image_resize
operator|->
name|resize
operator|=
name|resize_widget_new
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
name|ResizeWidget
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
name|gimage
operator|->
name|unit
argument_list|,
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
operator|->
name|dot_for_dot
argument_list|,
name|G_CALLBACK
argument_list|(
name|image_resize_callback
argument_list|)
argument_list|,
name|image_resize
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
name|image_resize
operator|->
name|resize
operator|->
name|resize_shell
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
name|g_object_weak_ref
argument_list|(
name|G_OBJECT
argument_list|(
name|image_resize
operator|->
name|resize
operator|->
name|resize_shell
argument_list|)
argument_list|,
operator|(
name|GWeakNotify
operator|)
name|g_free
argument_list|,
name|image_resize
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|image_resize
operator|->
name|resize
operator|->
name|resize_shell
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
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|ImageResize
modifier|*
name|image_scale
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
name|image_scale
operator|=
name|g_new0
argument_list|(
name|ImageResize
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|image_scale
operator|->
name|gdisp
operator|=
name|gdisp
expr_stmt|;
name|image_scale
operator|->
name|gimage
operator|=
name|gimage
expr_stmt|;
name|image_scale
operator|->
name|resize
operator|=
name|resize_widget_new
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
name|ScaleWidget
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
name|gimage
operator|->
name|unit
argument_list|,
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
operator|->
name|dot_for_dot
argument_list|,
name|G_CALLBACK
argument_list|(
name|image_scale_callback
argument_list|)
argument_list|,
name|image_scale
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
name|image_scale
operator|->
name|resize
operator|->
name|resize_shell
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
name|g_object_weak_ref
argument_list|(
name|G_OBJECT
argument_list|(
name|image_scale
operator|->
name|resize
operator|->
name|resize_shell
argument_list|)
argument_list|,
operator|(
name|GWeakNotify
operator|)
name|g_free
argument_list|,
name|image_scale
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|image_scale
operator|->
name|resize
operator|->
name|resize_shell
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
name|gdisp
argument_list|,
name|_
argument_list|(
literal|"Flipping..."
argument_list|)
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_image_flip
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|gimp_get_user_context
argument_list|(
name|gdisp
operator|->
name|gimage
operator|->
name|gimp
argument_list|)
argument_list|,
operator|(
name|GimpOrientationType
operator|)
name|value
argument_list|,
name|gimp_progress_update_and_flush
argument_list|,
name|progress
argument_list|)
expr_stmt|;
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
name|gdisp
argument_list|,
name|_
argument_list|(
literal|"Rotating..."
argument_list|)
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_image_rotate
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|gimp_get_user_context
argument_list|(
name|gdisp
operator|->
name|gimage
operator|->
name|gimp
argument_list|)
argument_list|,
operator|(
name|GimpRotationType
operator|)
name|value
argument_list|,
name|gimp_progress_update_and_flush
argument_list|,
name|progress
argument_list|)
expr_stmt|;
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
name|GimpDisplay
modifier|*
name|gdisp
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
name|return_if_no_display
argument_list|(
name|gdisp
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
name|gdisp
operator|->
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
name|gdisp
operator|->
name|gimage
argument_list|,
name|gimp_get_user_context
argument_list|(
name|gdisp
operator|->
name|gimage
operator|->
name|gimp
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
name|gdisp
operator|->
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
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpImage
modifier|*
name|new_gimage
decl_stmt|;
name|return_if_no_image
argument_list|(
name|gimage
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|new_gimage
operator|=
name|gimp_image_duplicate
argument_list|(
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
literal|1.0
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
name|image_layers_merge_query
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|TRUE
argument_list|,
name|gdisp
operator|->
name|shell
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
name|gimp_get_user_context
argument_list|(
name|gimage
operator|->
name|gimp
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
comment|/****************************/
end_comment

begin_comment
comment|/*  The layer merge dialog  */
end_comment

begin_comment
comment|/****************************/
end_comment

begin_typedef
DECL|typedef|LayerMergeOptions
typedef|typedef
name|struct
name|_LayerMergeOptions
name|LayerMergeOptions
typedef|;
end_typedef

begin_struct
DECL|struct|_LayerMergeOptions
struct|struct
name|_LayerMergeOptions
block|{
DECL|member|query_box
name|GtkWidget
modifier|*
name|query_box
decl_stmt|;
DECL|member|gimage
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
DECL|member|merge_visible
name|gboolean
name|merge_visible
decl_stmt|;
DECL|member|merge_type
name|GimpMergeType
name|merge_type
decl_stmt|;
block|}
struct|;
end_struct

begin_function
specifier|static
name|void
DECL|function|image_layers_merge_query_response (GtkWidget * widget,gint response_id,LayerMergeOptions * options)
name|image_layers_merge_query_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|LayerMergeOptions
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
operator|!
name|gimage
condition|)
return|return;
if|if
condition|(
name|response_id
operator|==
name|GTK_RESPONSE_OK
condition|)
block|{
if|if
condition|(
name|options
operator|->
name|merge_visible
condition|)
name|gimp_image_merge_visible_layers
argument_list|(
name|gimage
argument_list|,
name|gimp_get_user_context
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|)
argument_list|,
name|options
operator|->
name|merge_type
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
DECL|function|image_layers_merge_query (GimpImage * gimage,gboolean merge_visible,GtkWidget * parent)
name|image_layers_merge_query
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
comment|/*  if FALSE, anchor active layer  */
name|gboolean
name|merge_visible
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|)
block|{
name|LayerMergeOptions
modifier|*
name|options
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
comment|/*  The new options structure  */
name|options
operator|=
name|g_new
argument_list|(
name|LayerMergeOptions
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
name|merge_visible
operator|=
name|merge_visible
expr_stmt|;
name|options
operator|->
name|merge_type
operator|=
name|GIMP_EXPAND_AS_NECESSARY
expr_stmt|;
comment|/* The dialog  */
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
literal|"Merge Layers"
argument_list|)
argument_list|,
literal|"gimp-image-merge-layers"
argument_list|,
name|GIMP_STOCK_MERGE_DOWN
argument_list|,
name|_
argument_list|(
literal|"Layers Merge Options"
argument_list|)
argument_list|,
name|parent
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_IMAGE_MERGE_LAYERS
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
name|image_layers_merge_query_response
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
name|frame
operator|=
name|gimp_int_radio_group_new
argument_list|(
name|TRUE
argument_list|,
name|merge_visible
condition|?
name|_
argument_list|(
literal|"Final, Merged Layer should be:"
argument_list|)
else|:
name|_
argument_list|(
literal|"Final, Anchored Layer should be:"
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
name|merge_type
argument_list|,
name|options
operator|->
name|merge_type
argument_list|,
name|_
argument_list|(
literal|"Expanded as necessary"
argument_list|)
argument_list|,
name|GIMP_EXPAND_AS_NECESSARY
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Clipped to image"
argument_list|)
argument_list|,
name|GIMP_CLIP_TO_IMAGE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Clipped to bottom layer"
argument_list|)
argument_list|,
name|GIMP_CLIP_TO_BOTTOM_LAYER
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
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
name|options
operator|->
name|query_box
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|frame
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
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
name|ImageResize
modifier|*
name|image_resize
decl_stmt|;
name|image_resize
operator|=
operator|(
name|ImageResize
operator|*
operator|)
name|data
expr_stmt|;
name|g_assert
argument_list|(
name|image_resize
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|image_resize
operator|->
name|gimage
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|image_resize
operator|->
name|resize
operator|->
name|resize_shell
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_resize
operator|->
name|resize
operator|->
name|width
operator|>
literal|0
operator|&&
name|image_resize
operator|->
name|resize
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
name|image_resize
operator|->
name|gdisp
argument_list|,
name|_
argument_list|(
literal|"Resizing..."
argument_list|)
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_image_resize
argument_list|(
name|image_resize
operator|->
name|gimage
argument_list|,
name|gimp_get_user_context
argument_list|(
name|image_resize
operator|->
name|gimage
operator|->
name|gimp
argument_list|)
argument_list|,
name|image_resize
operator|->
name|resize
operator|->
name|width
argument_list|,
name|image_resize
operator|->
name|resize
operator|->
name|height
argument_list|,
name|image_resize
operator|->
name|resize
operator|->
name|offset_x
argument_list|,
name|image_resize
operator|->
name|resize
operator|->
name|offset_y
argument_list|,
name|gimp_progress_update_and_flush
argument_list|,
name|progress
argument_list|)
expr_stmt|;
name|gimp_progress_end
argument_list|(
name|progress
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image_resize
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
name|image_resize
operator|->
name|resize
operator|->
name|resize_shell
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
name|ImageResize
modifier|*
name|image_scale
init|=
name|data
decl_stmt|;
name|GimpImageScaleCheckType
name|scale_check
decl_stmt|;
name|gint64
name|new_memsize
decl_stmt|;
name|gchar
modifier|*
name|warning_message
decl_stmt|;
name|g_assert
argument_list|(
name|image_scale
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|image_scale
operator|->
name|gimage
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|image_scale
operator|->
name|resize
operator|->
name|resize_shell
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|scale_check
operator|=
name|gimp_image_scale_check
argument_list|(
name|image_scale
operator|->
name|gimage
argument_list|,
name|image_scale
operator|->
name|resize
operator|->
name|width
argument_list|,
name|image_scale
operator|->
name|resize
operator|->
name|height
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
block|{
name|gchar
modifier|*
name|size_str
decl_stmt|;
name|gchar
modifier|*
name|max_size_str
decl_stmt|;
name|size_str
operator|=
name|gimp_memsize_to_string
argument_list|(
name|new_memsize
argument_list|)
expr_stmt|;
name|max_size_str
operator|=
name|gimp_memsize_to_string
argument_list|(
name|GIMP_GUI_CONFIG
argument_list|(
name|image_scale
operator|->
name|gimage
operator|->
name|gimp
operator|->
name|config
argument_list|)
operator|->
name|max_new_image_size
argument_list|)
expr_stmt|;
name|warning_message
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"You are trying to create an image with a size of %s.\n\n"
literal|"Choose OK to create this image anyway.\n"
literal|"Choose Cancel if you did not intend to create such a "
literal|"large image.\n\n"
literal|"To prevent this dialog from appearing, increase the "
literal|"\"Maximum Image Size\" setting (currently %s) in the "
literal|"Preferences dialog."
argument_list|)
argument_list|,
name|size_str
argument_list|,
name|max_size_str
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|size_str
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|max_size_str
argument_list|)
expr_stmt|;
name|image_scale_warn
argument_list|(
name|image_scale
argument_list|,
name|_
argument_list|(
literal|"Image exceeds maximum image size"
argument_list|)
argument_list|,
name|warning_message
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|warning_message
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_IMAGE_SCALE_TOO_SMALL
case|:
name|warning_message
operator|=
name|_
argument_list|(
literal|"The chosen image size will shrink "
literal|"some layers completely away. "
literal|"Is this what you want?"
argument_list|)
expr_stmt|;
name|image_scale_warn
argument_list|(
name|image_scale
argument_list|,
name|_
argument_list|(
literal|"Layer Too Small"
argument_list|)
argument_list|,
name|warning_message
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_IMAGE_SCALE_OK
case|:
comment|/* If all is well, return directly after scaling image. */
name|image_scale_implement
argument_list|(
name|image_scale
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|image_scale
operator|->
name|resize
operator|->
name|resize_shell
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|image_scale_warn (ImageResize * image_scale,const gchar * warning_title,const gchar * warning_message)
name|image_scale_warn
parameter_list|(
name|ImageResize
modifier|*
name|image_scale
parameter_list|,
specifier|const
name|gchar
modifier|*
name|warning_title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|warning_message
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|dialog
operator|=
name|gimp_query_boolean_box
argument_list|(
name|warning_title
argument_list|,
name|image_scale
operator|->
name|resize
operator|->
name|resize_shell
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_IMAGE_SCALE_WARNING
argument_list|,
name|GTK_STOCK_DIALOG_QUESTION
argument_list|,
name|warning_message
argument_list|,
name|GTK_STOCK_OK
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|G_OBJECT
argument_list|(
name|image_scale
operator|->
name|resize
operator|->
name|resize_shell
argument_list|)
argument_list|,
literal|"destroy"
argument_list|,
name|image_scale_warn_callback
argument_list|,
name|image_scale
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
DECL|function|image_scale_warn_callback (GtkWidget * widget,gboolean do_scale,gpointer data)
name|image_scale_warn_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gboolean
name|do_scale
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|ImageResize
modifier|*
name|image_scale
init|=
name|data
decl_stmt|;
if|if
condition|(
name|do_scale
condition|)
comment|/* User doesn't mind losing layers or                  * creating huge image... */
block|{
name|image_scale_implement
argument_list|(
name|image_scale
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|image_scale
operator|->
name|resize
operator|->
name|resize_shell
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_widget_set_sensitive
argument_list|(
name|image_scale
operator|->
name|resize
operator|->
name|resize_shell
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
DECL|function|image_scale_implement (ImageResize * image_scale)
name|image_scale_implement
parameter_list|(
name|ImageResize
modifier|*
name|image_scale
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|g_assert
argument_list|(
name|image_scale
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|image_scale
operator|->
name|gimage
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gimage
operator|=
name|image_scale
operator|->
name|gimage
expr_stmt|;
if|if
condition|(
name|image_scale
operator|->
name|resize
operator|->
name|resolution_x
operator|==
name|gimage
operator|->
name|xresolution
operator|&&
name|image_scale
operator|->
name|resize
operator|->
name|resolution_y
operator|==
name|gimage
operator|->
name|yresolution
operator|&&
name|image_scale
operator|->
name|resize
operator|->
name|unit
operator|==
name|gimage
operator|->
name|unit
operator|&&
name|image_scale
operator|->
name|resize
operator|->
name|width
operator|==
name|gimage
operator|->
name|width
operator|&&
name|image_scale
operator|->
name|resize
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
name|image_scale
operator|->
name|resize
operator|->
name|resolution_x
argument_list|,
name|image_scale
operator|->
name|resize
operator|->
name|resolution_y
argument_list|)
expr_stmt|;
name|gimp_image_set_unit
argument_list|(
name|gimage
argument_list|,
name|image_scale
operator|->
name|resize
operator|->
name|unit
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_scale
operator|->
name|resize
operator|->
name|width
operator|!=
name|gimage
operator|->
name|width
operator|||
name|image_scale
operator|->
name|resize
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
name|image_scale
operator|->
name|resize
operator|->
name|width
operator|>
literal|0
operator|&&
name|image_scale
operator|->
name|resize
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
name|image_scale
operator|->
name|gdisp
argument_list|,
name|_
argument_list|(
literal|"Scaling..."
argument_list|)
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_image_scale
argument_list|(
name|gimage
argument_list|,
name|image_scale
operator|->
name|resize
operator|->
name|width
argument_list|,
name|image_scale
operator|->
name|resize
operator|->
name|height
argument_list|,
name|image_scale
operator|->
name|resize
operator|->
name|interpolation
argument_list|,
name|gimp_progress_update_and_flush
argument_list|,
name|progress
argument_list|)
expr_stmt|;
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

end_unit

