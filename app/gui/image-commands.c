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
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable-desaturate.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable-equalize.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-duplicate.h"
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
file|"pdb/procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay-foreach.h"
end_include

begin_include
include|#
directive|include
file|"convert-dialog.h"
end_include

begin_include
include|#
directive|include
file|"offset-dialog.h"
end_include

begin_include
include|#
directive|include
file|"resize-dialog.h"
end_include

begin_include
include|#
directive|include
file|"gimpprogress.h"
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
DECL|struct|__anon29631e800108
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
DECL|function|image_desaturate_cmd_callback (GtkWidget * widget,gpointer data)
name|image_desaturate_cmd_callback
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
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|return_if_no_image
argument_list|(
name|gimage
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|gimp_image_active_drawable
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_drawable_is_rgb
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Desaturate operates only on RGB color drawables."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|gimp_drawable_desaturate
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|gdisplays_flush
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|image_invert_cmd_callback (GtkWidget * widget,gpointer data)
name|image_invert_cmd_callback
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
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|Argument
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|return_if_no_image
argument_list|(
name|gimage
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|gimp_image_active_drawable
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_drawable_is_indexed
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Invert does not operate on indexed drawables."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|return_vals
operator|=
name|procedural_db_run_proc
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|,
literal|"gimp_invert"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_DRAWABLE
argument_list|,
name|gimp_drawable_get_ID
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|return_vals
operator|||
name|return_vals
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|!=
name|GIMP_PDB_SUCCESS
condition|)
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Invert operation failed."
argument_list|)
argument_list|)
expr_stmt|;
name|procedural_db_destroy_args
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
name|gdisplays_flush
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|image_equalize_cmd_callback (GtkWidget * widget,gpointer data)
name|image_equalize_cmd_callback
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
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|return_if_no_image
argument_list|(
name|gimage
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|gimp_image_active_drawable
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_drawable_is_indexed
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Equalize does not operate on indexed drawables."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|gimp_drawable_equalize
argument_list|(
name|drawable
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gdisplays_flush
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|image_offset_cmd_callback (GtkWidget * widget,gpointer data)
name|image_offset_cmd_callback
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
name|offset_dialog_create
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
name|gdisp
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
name|gdisp
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
name|gdisplays_flush
argument_list|()
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
name|FALSE
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
name|IMAGE_SCALE_UNDO
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
name|IMAGE_SCALE_UNDO
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
name|IMAGE_SCALE_UNDO
argument_list|)
expr_stmt|;
name|progress
operator|=
name|progress_start
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
name|progress_update_and_flush
argument_list|,
name|progress
argument_list|)
expr_stmt|;
name|progress_end
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
name|gdisplays_flush
argument_list|()
expr_stmt|;
block|}
block|}
end_function

end_unit

