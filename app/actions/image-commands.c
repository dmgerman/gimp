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
file|"core/gimpimage-mask.h"
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
file|"core/gimpimage-scale.h"
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
file|"convert-dialog.h"
end_include

begin_include
include|#
directive|include
file|"image-commands.h"
end_include

begin_include
include|#
directive|include
file|"resize-dialog.h"
end_include

begin_include
include|#
directive|include
file|"undo.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2b31cf580108
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
value|gdisp = gimp_context_get_display (gimp_get_user_context (GIMP (data))); \   if (! gdisp) \     return
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
value|gimage = gimp_context_get_image (gimp_get_user_context (GIMP (data))); \   if (! gimage) \     return
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
DECL|function|image_convert_rgb_cmd_callback (GtkWidget * widget,gpointer data)
name|image_convert_rgb_cmd_callback
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
name|convert_to_rgb
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|image_convert_grayscale_cmd_callback (GtkWidget * widget,gpointer data)
name|image_convert_grayscale_cmd_callback
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
name|convert_to_grayscale
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|image_convert_indexed_cmd_callback (GtkWidget * widget,gpointer data)
name|image_convert_indexed_cmd_callback
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
name|convert_to_indexed
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|image_resize_cmd_callback (GtkWidget * widget,gpointer data)
name|image_resize_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
name|gimage
argument_list|,
name|ResizeWidget
argument_list|,
name|ResizeImage
argument_list|,
name|G_OBJECT
argument_list|(
name|gdisp
argument_list|)
argument_list|,
literal|"disconnect"
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
name|NULL
argument_list|,
name|image_resize
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
DECL|function|image_scale_cmd_callback (GtkWidget * widget,gpointer data)
name|image_scale_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
name|gimage
argument_list|,
name|ScaleWidget
argument_list|,
name|ResizeImage
argument_list|,
name|G_OBJECT
argument_list|(
name|gdisp
argument_list|)
argument_list|,
literal|"disconnect"
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
name|NULL
argument_list|,
name|image_scale
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
DECL|function|image_crop_cmd_callback (GtkWidget * widget,gpointer data)
name|image_crop_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
name|gimp_image_mask_bounds
argument_list|(
name|gdisp
operator|->
name|gimage
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
block|}
end_function

begin_function
name|void
DECL|function|image_duplicate_cmd_callback (GtkWidget * widget,gpointer data)
name|image_duplicate_cmd_callback
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
literal|0x0101
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|G_OBJECT
argument_list|(
name|new_gimage
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|image_merge_layers_cmd_callback (GtkWidget * widget,gpointer data)
name|image_merge_layers_cmd_callback
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
name|image_layers_merge_query
argument_list|(
name|gimage
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|image_flatten_image_cmd_callback (GtkWidget * widget,gpointer data)
name|image_flatten_image_cmd_callback
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
name|gimp_image_flatten
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
DECL|function|image_layers_merge_query_ok_callback (GtkWidget * widget,gpointer data)
name|image_layers_merge_query_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|LayerMergeOptions
modifier|*
name|options
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|options
operator|=
operator|(
name|LayerMergeOptions
operator|*
operator|)
name|data
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|gimage
operator|=
name|options
operator|->
name|gimage
operator|)
condition|)
return|return;
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
DECL|function|image_layers_merge_query (GimpImage * gimage,gboolean merge_visible)
name|image_layers_merge_query
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
comment|/*  if FALSE, anchor active layer  */
name|gboolean
name|merge_visible
parameter_list|)
block|{
name|LayerMergeOptions
modifier|*
name|options
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
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
literal|"layers_merge_options"
argument_list|,
name|GIMP_STOCK_MERGE_DOWN
argument_list|,
name|_
argument_list|(
literal|"Layers Merge Options"
argument_list|)
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"dialogs/layers/merge_visible_layers.html"
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
name|image_layers_merge_query_ok_callback
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
comment|/*  The main vbox  */
name|vbox
operator|=
name|gtk_vbox_new
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
name|vbox
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
name|vbox
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_radio_group_new2
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
name|GINT_TO_POINTER
argument_list|(
name|options
operator|->
name|merge_type
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Expanded as necessary"
argument_list|)
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|GIMP_EXPAND_AS_NECESSARY
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Clipped to image"
argument_list|)
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|GIMP_CLIP_TO_IMAGE
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Clipped to bottom layer"
argument_list|)
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|GIMP_CLIP_TO_BOTTOM_LAYER
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
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
name|gtk_widget_show
argument_list|(
name|vbox
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
name|gimp_image_resize
argument_list|(
name|image_resize
operator|->
name|gimage
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
decl_stmt|;
name|image_scale
operator|=
operator|(
name|ImageResize
operator|*
operator|)
name|data
expr_stmt|;
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
if|if
condition|(
name|gimp_image_check_scaling
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
argument_list|)
condition|)
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
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|dialog
operator|=
name|gimp_query_boolean_box
argument_list|(
name|_
argument_list|(
literal|"Layer Too Small"
argument_list|)
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"dialogs/scale_layer_warn.html"
argument_list|,
name|GTK_STOCK_DIALOG_QUESTION
argument_list|,
name|_
argument_list|(
literal|"The chosen image size will shrink\n"
literal|"some layers completely away.\n"
literal|"Is this what you want?"
argument_list|)
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
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|image_scale
operator|=
operator|(
name|ImageResize
operator|*
operator|)
name|data
expr_stmt|;
name|gimage
operator|=
name|image_scale
operator|->
name|gimage
expr_stmt|;
if|if
condition|(
name|do_scale
condition|)
comment|/* User doesn't mind losing layers... */
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
init|=
name|NULL
decl_stmt|;
name|gboolean
name|display_flush
init|=
name|FALSE
decl_stmt|;
comment|/* this is a bit ugly:  					we hijack the flush variable  					to check if an undo_group was  					already started */
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
operator|!=
name|gimage
operator|->
name|xresolution
operator|||
name|image_scale
operator|->
name|resize
operator|->
name|resolution_y
operator|!=
name|gimage
operator|->
name|yresolution
condition|)
block|{
name|undo_push_group_start
argument_list|(
name|gimage
argument_list|,
name|IMAGE_SCALE_UNDO_GROUP
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
name|display_flush
operator|=
name|TRUE
expr_stmt|;
block|}
if|if
condition|(
name|image_scale
operator|->
name|resize
operator|->
name|unit
operator|!=
name|gimage
operator|->
name|unit
condition|)
block|{
if|if
condition|(
operator|!
name|display_flush
condition|)
name|undo_push_group_start
argument_list|(
name|gimage
argument_list|,
name|IMAGE_SCALE_UNDO_GROUP
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
name|display_flush
operator|=
name|TRUE
expr_stmt|;
block|}
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
if|if
condition|(
operator|!
name|display_flush
condition|)
name|undo_push_group_start
argument_list|(
name|gimage
argument_list|,
name|IMAGE_SCALE_UNDO_GROUP
argument_list|)
expr_stmt|;
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
name|display_flush
operator|=
name|TRUE
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
if|if
condition|(
name|display_flush
condition|)
block|{
name|undo_push_group_end
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

end_unit

