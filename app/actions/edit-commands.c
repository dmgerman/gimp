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
file|"core/gimp-edit.h"
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
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-undo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
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
file|"display/gimpdisplayshell-transform.h"
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
file|"stroke-dialog.h"
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

begin_define
DECL|macro|return_if_no_drawable (gimage,drawable,data)
define|#
directive|define
name|return_if_no_drawable
parameter_list|(
name|gimage
parameter_list|,
name|drawable
parameter_list|,
name|data
parameter_list|)
define|\
value|return_if_no_image (gimage, data); \   drawable = gimp_image_active_drawable (gimage); \   if (! drawable) \     return;
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
specifier|const
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
specifier|const
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
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|return_if_no_drawable
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_edit_cut
argument_list|(
name|gimage
argument_list|,
name|drawable
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
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|return_if_no_drawable
argument_list|(
name|gimage
argument_list|,
name|drawable
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
name|drawable
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
DECL|function|edit_paste_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|edit_paste_cmd_callback
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
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
name|gboolean
name|paste_into
decl_stmt|;
name|return_if_no_display
argument_list|(
name|gdisp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|paste_into
operator|=
operator|(
name|gboolean
operator|)
name|action
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
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|width
decl_stmt|,
name|height
decl_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|gimp_display_shell_untransform_viewport
argument_list|(
name|shell
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
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
name|paste_into
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
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
name|gdisp
operator|->
name|shell
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_BUFFER_CUT
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
literal|"Copy Named"
argument_list|)
argument_list|,
name|gdisp
operator|->
name|shell
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_BUFFER_COPY
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
name|copy_named_buffer_callback
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
name|gtk_widget_get_screen
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"gimp-buffer-list|gimp-buffer-grid"
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
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|return_if_no_drawable
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_edit_clear
argument_list|(
name|gimage
argument_list|,
name|drawable
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
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpFillType
name|fill_type
decl_stmt|;
name|return_if_no_drawable
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|fill_type
operator|=
operator|(
name|GimpFillType
operator|)
name|action
expr_stmt|;
name|gimp_edit_fill
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|fill_type
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
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|return_if_no_drawable
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|edit_stroke_selection
argument_list|(
name|GIMP_ITEM
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
argument_list|)
argument_list|,
name|widget
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|edit_stroke_selection (GimpItem * item,GtkWidget * parent)
name|edit_stroke_selection
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpDrawable
modifier|*
name|active_drawable
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ITEM
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|gimage
operator|=
name|gimp_item_get_image
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|active_drawable
operator|=
name|gimp_image_active_drawable
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|active_drawable
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"There is no active layer or channel to stroke to."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|dialog
operator|=
name|stroke_dialog_new
argument_list|(
name|item
argument_list|,
name|GIMP_STOCK_SELECTION_STROKE
argument_list|,
name|GIMP_HELP_SELECTION_STROKE
argument_list|,
name|parent
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
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
DECL|function|cut_named_buffer_callback (GtkWidget * widget,const gchar * name,gpointer data)
name|cut_named_buffer_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
init|=
name|GIMP_IMAGE
argument_list|(
name|data
argument_list|)
decl_stmt|;
specifier|const
name|GimpBuffer
modifier|*
name|cut_buffer
decl_stmt|;
name|GimpDrawable
modifier|*
name|active_drawable
decl_stmt|;
name|active_drawable
operator|=
name|gimp_image_active_drawable
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|active_drawable
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"There is no active layer or channel to cut from."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|cut_buffer
operator|=
name|gimp_edit_cut
argument_list|(
name|gimage
argument_list|,
name|active_drawable
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
name|g_object_unref
argument_list|(
name|new_buffer
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
specifier|static
name|void
DECL|function|copy_named_buffer_callback (GtkWidget * widget,const gchar * name,gpointer data)
name|copy_named_buffer_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
init|=
name|GIMP_IMAGE
argument_list|(
name|data
argument_list|)
decl_stmt|;
specifier|const
name|GimpBuffer
modifier|*
name|copy_buffer
decl_stmt|;
name|GimpDrawable
modifier|*
name|active_drawable
decl_stmt|;
name|active_drawable
operator|=
name|gimp_image_active_drawable
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|active_drawable
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"There is no active layer or channel to copy from."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|copy_buffer
operator|=
name|gimp_edit_copy
argument_list|(
name|gimage
argument_list|,
name|active_drawable
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
name|g_object_unref
argument_list|(
name|new_buffer
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

