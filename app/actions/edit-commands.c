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
file|"core/gimpbuffer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer.h"
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
file|"core/gimpdrawable-bucket-fill.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpedit.h"
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
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"dialogs.h"
end_include

begin_include
include|#
directive|include
file|"edit-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

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
value|if (GIMP_IS_DISPLAY (data)) \     gdisp = data; \   else if (GIMP_IS_GIMP (data)) \     gdisp = gimp_context_get_display (gimp_get_user_context (GIMP (data))); \   else \     gdisp = NULL; \   if (! gdisp) \     return
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
value|if (GIMP_IS_DISPLAY (data)) \     gimage = ((GimpDisplay *) data)->gimage; \   else if (GIMP_IS_GIMP (data)) \     gimage = gimp_context_get_image (gimp_get_user_context (GIMP (data))); \   else \     gimage = NULL; \   if (! gimage) \     return
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|cut_named_buffer_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gchar
modifier|*
name|name
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|copy_named_buffer_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gchar
modifier|*
name|name
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|edit_undo_cmd_callback (GtkWidget * widget,gpointer data)
name|edit_undo_cmd_callback
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
if|if
condition|(
name|gimp_image_undo
argument_list|(
name|gimage
argument_list|)
condition|)
name|gimp_image_flush
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|edit_redo_cmd_callback (GtkWidget * widget,gpointer data)
name|edit_redo_cmd_callback
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
if|if
condition|(
name|gimp_image_redo
argument_list|(
name|gimage
argument_list|)
condition|)
name|gimp_image_flush
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|edit_cut_cmd_callback (GtkWidget * widget,gpointer data)
name|edit_cut_cmd_callback
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
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_edit_cut
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|gimp_image_active_drawable
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|)
condition|)
block|{
name|gimp_image_flush
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|edit_copy_cmd_callback (GtkWidget * widget,gpointer data)
name|edit_copy_cmd_callback
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
if|if
condition|(
name|gimp_edit_copy
argument_list|(
name|gimage
argument_list|,
name|gimp_image_active_drawable
argument_list|(
name|gimage
argument_list|)
argument_list|)
condition|)
block|{
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
DECL|function|edit_paste_cmd_callback (GtkWidget * widget,gpointer data)
name|edit_paste_cmd_callback
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
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|gdisp
operator|->
name|gimage
operator|->
name|gimp
operator|->
name|global_buffer
condition|)
block|{
if|if
condition|(
name|gimp_edit_paste
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|gimp_image_active_drawable
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|,
name|gdisp
operator|->
name|gimage
operator|->
name|gimp
operator|->
name|global_buffer
argument_list|,
name|FALSE
argument_list|)
condition|)
block|{
name|gimp_image_flush
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|edit_paste_into_cmd_callback (GtkWidget * widget,gpointer data)
name|edit_paste_into_cmd_callback
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
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|gdisp
operator|->
name|gimage
operator|->
name|gimp
operator|->
name|global_buffer
condition|)
block|{
if|if
condition|(
name|gimp_edit_paste
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|gimp_image_active_drawable
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|,
name|gdisp
operator|->
name|gimage
operator|->
name|gimp
operator|->
name|global_buffer
argument_list|,
name|TRUE
argument_list|)
condition|)
block|{
name|gimp_image_flush
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|edit_paste_as_new_cmd_callback (GtkWidget * widget,gpointer data)
name|edit_paste_as_new_cmd_callback
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
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|gdisp
operator|->
name|gimage
operator|->
name|gimp
operator|->
name|global_buffer
condition|)
block|{
name|gimp_edit_paste_as_new
argument_list|(
name|gdisp
operator|->
name|gimage
operator|->
name|gimp
argument_list|,
name|gdisp
operator|->
name|gimage
argument_list|,
name|gdisp
operator|->
name|gimage
operator|->
name|gimp
operator|->
name|global_buffer
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|edit_named_cut_cmd_callback (GtkWidget * widget,gpointer data)
name|edit_named_cut_cmd_callback
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
name|GtkWidget
modifier|*
name|qbox
decl_stmt|;
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|qbox
operator|=
name|gimp_query_string_box
argument_list|(
name|_
argument_list|(
literal|"Cut Named"
argument_list|)
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"dialogs/cut_named.html"
argument_list|,
name|_
argument_list|(
literal|"Enter a name for this buffer"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|G_OBJECT
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|,
literal|"disconnect"
argument_list|,
name|cut_named_buffer_callback
argument_list|,
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|qbox
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|edit_named_copy_cmd_callback (GtkWidget * widget,gpointer data)
name|edit_named_copy_cmd_callback
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
name|GtkWidget
modifier|*
name|qbox
decl_stmt|;
name|return_if_no_image
argument_list|(
name|gimage
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|qbox
operator|=
name|gimp_query_string_box
argument_list|(
name|_
argument_list|(
literal|"Copy Named"
argument_list|)
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"dialogs/copy_named.html"
argument_list|,
name|_
argument_list|(
literal|"Enter a name for this buffer"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|G_OBJECT
argument_list|(
name|gimage
argument_list|)
argument_list|,
literal|"disconnect"
argument_list|,
name|copy_named_buffer_callback
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|qbox
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|edit_named_paste_cmd_callback (GtkWidget * widget,gpointer data)
name|edit_named_paste_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gimp_dialog_factory_dialog_raise
argument_list|(
name|global_dock_factory
argument_list|,
literal|"gimp-buffer-list"
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|edit_clear_cmd_callback (GtkWidget * widget,gpointer data)
name|edit_clear_cmd_callback
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
name|gimp_edit_clear
argument_list|(
name|gimage
argument_list|,
name|gimp_image_active_drawable
argument_list|(
name|gimage
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
DECL|function|edit_fill_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|edit_fill_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|guint
name|action
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpBucketFillMode
name|fill_mode
decl_stmt|;
name|return_if_no_image
argument_list|(
name|gimage
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|fill_mode
operator|=
operator|(
name|GimpBucketFillMode
operator|)
name|action
expr_stmt|;
name|gimp_drawable_bucket_fill
argument_list|(
name|gimp_image_active_drawable
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|fill_mode
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|,
literal|1.0
argument_list|,
name|FALSE
comment|/* no seed fill */
argument_list|,
name|FALSE
argument_list|,
literal|0.0
argument_list|,
name|FALSE
argument_list|,
literal|0.0
argument_list|,
literal|0.0
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
DECL|function|edit_stroke_cmd_callback (GtkWidget * widget,gpointer data)
name|edit_stroke_cmd_callback
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
name|gimp_image_mask_stroke
argument_list|(
name|gimage
argument_list|,
name|gimp_image_active_drawable
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|gimp_get_current_context
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

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|cut_named_buffer_callback (GtkWidget * widget,gchar * name,gpointer data)
name|cut_named_buffer_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gchar
modifier|*
name|name
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpBuffer
modifier|*
name|cut_buffer
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|gimage
operator|=
operator|(
name|GimpImage
operator|*
operator|)
name|data
expr_stmt|;
name|cut_buffer
operator|=
name|gimp_edit_cut
argument_list|(
name|gimage
argument_list|,
name|gimp_image_active_drawable
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|cut_buffer
condition|)
block|{
name|GimpBuffer
modifier|*
name|new_buffer
decl_stmt|;
if|if
condition|(
operator|!
operator|(
name|name
operator|&&
name|strlen
argument_list|(
name|name
argument_list|)
operator|)
condition|)
name|name
operator|=
name|_
argument_list|(
literal|"(Unnamed Buffer)"
argument_list|)
expr_stmt|;
name|new_buffer
operator|=
name|gimp_buffer_new
argument_list|(
name|cut_buffer
operator|->
name|tiles
argument_list|,
name|name
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_container_add
argument_list|(
name|gimage
operator|->
name|gimp
operator|->
name|named_buffers
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|new_buffer
argument_list|)
argument_list|)
expr_stmt|;
block|}
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
DECL|function|copy_named_buffer_callback (GtkWidget * widget,gchar * name,gpointer data)
name|copy_named_buffer_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gchar
modifier|*
name|name
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpBuffer
modifier|*
name|copy_buffer
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|gimage
operator|=
operator|(
name|GimpImage
operator|*
operator|)
name|data
expr_stmt|;
name|copy_buffer
operator|=
name|gimp_edit_copy
argument_list|(
name|gimage
argument_list|,
name|gimp_image_active_drawable
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|copy_buffer
condition|)
block|{
name|GimpBuffer
modifier|*
name|new_buffer
decl_stmt|;
if|if
condition|(
operator|!
operator|(
name|name
operator|&&
name|strlen
argument_list|(
name|name
argument_list|)
operator|)
condition|)
name|name
operator|=
name|_
argument_list|(
literal|"(Unnamed Buffer)"
argument_list|)
expr_stmt|;
name|new_buffer
operator|=
name|gimp_buffer_new
argument_list|(
name|copy_buffer
operator|->
name|tiles
argument_list|,
name|name
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_container_add
argument_list|(
name|gimage
operator|->
name|gimp
operator|->
name|named_buffers
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|new_buffer
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

