begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"display-types.h"
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
file|"core/gimpdrawable-bucket-fill.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-merge.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-undo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayermask.h"
end_include

begin_include
include|#
directive|include
file|"core/gimppattern.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"file/file-open.h"
end_include

begin_include
include|#
directive|include
file|"file/file-utils.h"
end_include

begin_include
include|#
directive|include
file|"text/gimptext.h"
end_include

begin_include
include|#
directive|include
file|"text/gimptextlayer.h"
end_include

begin_include
include|#
directive|include
file|"vectors/gimpvectors.h"
end_include

begin_include
include|#
directive|include
file|"vectors/gimpvectors-import.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-dnd.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-transform.h"
end_include

begin_include
include|#
directive|include
file|"gimp-log.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_drop_drawable
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_drop_vectors
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_drop_svg
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
specifier|const
name|guchar
modifier|*
name|svg_data
parameter_list|,
name|gsize
name|svg_data_length
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_drop_pattern
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_drop_color
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_drop_buffer
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_drop_uri_list
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GList
modifier|*
name|uri_list
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_drop_component
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpChannelType
name|component
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_drop_pixbuf
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GdkPixbuf
modifier|*
name|pixbuf
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
DECL|function|gimp_display_shell_dnd_init (GimpDisplayShell * shell)
name|gimp_display_shell_dnd_init
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_dnd_uri_list_dest_add
argument_list|(
name|GTK_WIDGET
argument_list|(
name|shell
argument_list|)
argument_list|,
name|gimp_display_shell_drop_uri_list
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|gimp_dnd_viewable_dest_add
argument_list|(
name|GTK_WIDGET
argument_list|(
name|shell
argument_list|)
argument_list|,
name|GIMP_TYPE_LAYER
argument_list|,
name|gimp_display_shell_drop_drawable
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|gimp_dnd_viewable_dest_add
argument_list|(
name|GTK_WIDGET
argument_list|(
name|shell
argument_list|)
argument_list|,
name|GIMP_TYPE_LAYER_MASK
argument_list|,
name|gimp_display_shell_drop_drawable
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|gimp_dnd_viewable_dest_add
argument_list|(
name|GTK_WIDGET
argument_list|(
name|shell
argument_list|)
argument_list|,
name|GIMP_TYPE_CHANNEL
argument_list|,
name|gimp_display_shell_drop_drawable
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|gimp_dnd_viewable_dest_add
argument_list|(
name|GTK_WIDGET
argument_list|(
name|shell
argument_list|)
argument_list|,
name|GIMP_TYPE_VECTORS
argument_list|,
name|gimp_display_shell_drop_vectors
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|gimp_dnd_viewable_dest_add
argument_list|(
name|GTK_WIDGET
argument_list|(
name|shell
argument_list|)
argument_list|,
name|GIMP_TYPE_PATTERN
argument_list|,
name|gimp_display_shell_drop_pattern
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|gimp_dnd_viewable_dest_add
argument_list|(
name|GTK_WIDGET
argument_list|(
name|shell
argument_list|)
argument_list|,
name|GIMP_TYPE_BUFFER
argument_list|,
name|gimp_display_shell_drop_buffer
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|gimp_dnd_color_dest_add
argument_list|(
name|GTK_WIDGET
argument_list|(
name|shell
argument_list|)
argument_list|,
name|gimp_display_shell_drop_color
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|gimp_dnd_svg_dest_add
argument_list|(
name|GTK_WIDGET
argument_list|(
name|shell
argument_list|)
argument_list|,
name|gimp_display_shell_drop_svg
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|gimp_dnd_component_dest_add
argument_list|(
name|GTK_WIDGET
argument_list|(
name|shell
argument_list|)
argument_list|,
name|gimp_display_shell_drop_component
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|gimp_dnd_pixbuf_dest_add
argument_list|(
name|GTK_WIDGET
argument_list|(
name|shell
argument_list|)
argument_list|,
name|gimp_display_shell_drop_pixbuf
argument_list|,
name|shell
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
DECL|function|gimp_display_shell_dnd_flush (GimpDisplayShell * shell,GimpImage * image)
name|gimp_display_shell_dnd_flush
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
if|if
condition|(
name|GTK_WIDGET_DRAWABLE
argument_list|(
name|shell
argument_list|)
condition|)
block|{
name|gdk_window_focus
argument_list|(
name|GTK_WIDGET
argument_list|(
name|shell
argument_list|)
operator|->
name|window
argument_list|,
name|gtk_get_current_event_time
argument_list|()
argument_list|)
expr_stmt|;
block|}
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gimp_context_set_display
argument_list|(
name|gimp_get_user_context
argument_list|(
name|shell
operator|->
name|display
operator|->
name|gimp
argument_list|)
argument_list|,
name|shell
operator|->
name|display
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_drop_drawable (GtkWidget * widget,gint x,gint y,GimpViewable * viewable,gpointer data)
name|gimp_display_shell_drop_drawable
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|shell
operator|->
name|display
operator|->
name|image
decl_stmt|;
name|GType
name|new_type
decl_stmt|;
name|GimpItem
modifier|*
name|new_item
decl_stmt|;
name|GIMP_LOG
argument_list|(
name|DND
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|display
operator|->
name|gimp
operator|->
name|busy
condition|)
return|return;
if|if
condition|(
operator|!
name|image
condition|)
return|return;
if|if
condition|(
name|GIMP_IS_LAYER
argument_list|(
name|viewable
argument_list|)
condition|)
name|new_type
operator|=
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|viewable
argument_list|)
expr_stmt|;
else|else
name|new_type
operator|=
name|GIMP_TYPE_LAYER
expr_stmt|;
name|new_item
operator|=
name|gimp_item_convert
argument_list|(
name|GIMP_ITEM
argument_list|(
name|viewable
argument_list|)
argument_list|,
name|image
argument_list|,
name|new_type
argument_list|)
expr_stmt|;
if|if
condition|(
name|new_item
condition|)
block|{
name|GimpLayer
modifier|*
name|new_layer
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
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|new_layer
operator|=
name|GIMP_LAYER
argument_list|(
name|new_item
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_start
argument_list|(
name|image
argument_list|,
name|GIMP_UNDO_GROUP_EDIT_PASTE
argument_list|,
name|_
argument_list|(
literal|"Drop New Layer"
argument_list|)
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
name|gimp_item_offsets
argument_list|(
name|new_item
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
name|off_x
operator|=
name|x
operator|+
operator|(
name|width
operator|-
name|gimp_item_width
argument_list|(
name|new_item
argument_list|)
operator|)
operator|/
literal|2
operator|-
name|off_x
expr_stmt|;
name|off_y
operator|=
name|y
operator|+
operator|(
name|height
operator|-
name|gimp_item_height
argument_list|(
name|new_item
argument_list|)
operator|)
operator|/
literal|2
operator|-
name|off_y
expr_stmt|;
name|gimp_item_translate
argument_list|(
name|new_item
argument_list|,
name|off_x
argument_list|,
name|off_y
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_item_set_visible
argument_list|(
name|new_item
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_item_set_linked
argument_list|(
name|new_item
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_image_add_layer
argument_list|(
name|image
argument_list|,
name|new_layer
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_end
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gimp_display_shell_dnd_flush
argument_list|(
name|shell
argument_list|,
name|image
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_drop_vectors (GtkWidget * widget,gint x,gint y,GimpViewable * viewable,gpointer data)
name|gimp_display_shell_drop_vectors
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|shell
operator|->
name|display
operator|->
name|image
decl_stmt|;
name|GimpItem
modifier|*
name|new_item
decl_stmt|;
name|GIMP_LOG
argument_list|(
name|DND
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|display
operator|->
name|gimp
operator|->
name|busy
condition|)
return|return;
if|if
condition|(
operator|!
name|image
condition|)
return|return;
name|new_item
operator|=
name|gimp_item_convert
argument_list|(
name|GIMP_ITEM
argument_list|(
name|viewable
argument_list|)
argument_list|,
name|image
argument_list|,
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|viewable
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|new_item
condition|)
block|{
name|GimpVectors
modifier|*
name|new_vectors
init|=
name|GIMP_VECTORS
argument_list|(
name|new_item
argument_list|)
decl_stmt|;
name|gimp_image_undo_group_start
argument_list|(
name|image
argument_list|,
name|GIMP_UNDO_GROUP_EDIT_PASTE
argument_list|,
name|_
argument_list|(
literal|"Drop New Path"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_add_vectors
argument_list|(
name|image
argument_list|,
name|new_vectors
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_end
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gimp_display_shell_dnd_flush
argument_list|(
name|shell
argument_list|,
name|image
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_drop_svg (GtkWidget * widget,gint x,gint y,const guchar * svg_data,gsize svg_data_len,gpointer data)
name|gimp_display_shell_drop_svg
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
specifier|const
name|guchar
modifier|*
name|svg_data
parameter_list|,
name|gsize
name|svg_data_len
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|shell
operator|->
name|display
operator|->
name|image
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|GIMP_LOG
argument_list|(
name|DND
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|display
operator|->
name|gimp
operator|->
name|busy
condition|)
return|return;
if|if
condition|(
operator|!
name|image
condition|)
return|return;
if|if
condition|(
operator|!
name|gimp_vectors_import_buffer
argument_list|(
name|image
argument_list|,
operator|(
specifier|const
name|gchar
operator|*
operator|)
name|svg_data
argument_list|,
name|svg_data_len
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|gimp_message
argument_list|(
name|shell
operator|->
name|display
operator|->
name|gimp
argument_list|,
name|G_OBJECT
argument_list|(
name|shell
operator|->
name|display
argument_list|)
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
literal|"%s"
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_display_shell_dnd_flush
argument_list|(
name|shell
argument_list|,
name|image
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_dnd_bucket_fill (GimpDisplayShell * shell,GimpBucketFillMode fill_mode,const GimpRGB * color,GimpPattern * pattern)
name|gimp_display_shell_dnd_bucket_fill
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpBucketFillMode
name|fill_mode
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|GimpPattern
modifier|*
name|pattern
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|shell
operator|->
name|display
operator|->
name|image
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
if|if
condition|(
name|shell
operator|->
name|display
operator|->
name|gimp
operator|->
name|busy
condition|)
return|return;
if|if
condition|(
operator|!
name|image
condition|)
return|return;
name|drawable
operator|=
name|gimp_image_get_active_drawable
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|drawable
condition|)
return|return;
comment|/* FIXME: there should be a virtual method for this that the    *        GimpTextLayer can override.    */
if|if
condition|(
name|color
operator|&&
name|gimp_drawable_is_text_layer
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
name|gimp_text_layer_set
argument_list|(
name|GIMP_TEXT_LAYER
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|NULL
argument_list|,
literal|"color"
argument_list|,
name|color
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_drawable_bucket_fill_full
argument_list|(
name|drawable
argument_list|,
name|fill_mode
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|,
name|FALSE
argument_list|,
comment|/* no seed fill */
name|FALSE
argument_list|,
comment|/* don't fill transp */
name|GIMP_SELECT_CRITERION_COMPOSITE
argument_list|,
literal|0.0
argument_list|,
name|FALSE
argument_list|,
comment|/* fill params  */
literal|0.0
argument_list|,
literal|0.0
argument_list|,
comment|/* ignored      */
name|color
argument_list|,
name|pattern
argument_list|)
expr_stmt|;
block|}
name|gimp_display_shell_dnd_flush
argument_list|(
name|shell
argument_list|,
name|image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_drop_pattern (GtkWidget * widget,gint x,gint y,GimpViewable * viewable,gpointer data)
name|gimp_display_shell_drop_pattern
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GIMP_LOG
argument_list|(
name|DND
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_PATTERN
argument_list|(
name|viewable
argument_list|)
condition|)
name|gimp_display_shell_dnd_bucket_fill
argument_list|(
name|GIMP_DISPLAY_SHELL
argument_list|(
name|data
argument_list|)
argument_list|,
name|GIMP_PATTERN_BUCKET_FILL
argument_list|,
name|NULL
argument_list|,
name|GIMP_PATTERN
argument_list|(
name|viewable
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_drop_color (GtkWidget * widget,gint x,gint y,const GimpRGB * color,gpointer data)
name|gimp_display_shell_drop_color
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GIMP_LOG
argument_list|(
name|DND
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_display_shell_dnd_bucket_fill
argument_list|(
name|GIMP_DISPLAY_SHELL
argument_list|(
name|data
argument_list|)
argument_list|,
name|GIMP_FG_BUCKET_FILL
argument_list|,
name|color
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_drop_buffer (GtkWidget * widget,gint drop_x,gint drop_y,GimpViewable * viewable,gpointer data)
name|gimp_display_shell_drop_buffer
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|drop_x
parameter_list|,
name|gint
name|drop_y
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|shell
operator|->
name|display
operator|->
name|image
decl_stmt|;
name|GimpBuffer
modifier|*
name|buffer
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
name|GIMP_LOG
argument_list|(
name|DND
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|display
operator|->
name|gimp
operator|->
name|busy
condition|)
return|return;
if|if
condition|(
operator|!
name|image
condition|)
return|return;
name|buffer
operator|=
name|GIMP_BUFFER
argument_list|(
name|viewable
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
comment|/* FIXME: popup a menu for selecting "Paste Into" */
name|gimp_edit_paste
argument_list|(
name|image
argument_list|,
name|gimp_image_get_active_drawable
argument_list|(
name|image
argument_list|)
argument_list|,
name|buffer
argument_list|,
name|FALSE
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|gimp_display_shell_dnd_flush
argument_list|(
name|shell
argument_list|,
name|image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_drop_uri_list (GtkWidget * widget,gint x,gint y,GList * uri_list,gpointer data)
name|gimp_display_shell_drop_uri_list
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GList
modifier|*
name|uri_list
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|shell
operator|->
name|display
operator|->
name|image
decl_stmt|;
name|GimpContext
modifier|*
name|context
init|=
name|gimp_get_user_context
argument_list|(
name|shell
operator|->
name|display
operator|->
name|gimp
argument_list|)
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|GIMP_LOG
argument_list|(
name|DND
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|uri_list
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
specifier|const
name|gchar
modifier|*
name|uri
init|=
name|list
operator|->
name|data
decl_stmt|;
name|GimpPDBStatusType
name|status
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|gboolean
name|warn
init|=
name|FALSE
decl_stmt|;
if|if
condition|(
operator|!
name|shell
operator|->
name|display
operator|->
name|image
condition|)
block|{
name|image
operator|=
name|file_open_with_display
argument_list|(
name|shell
operator|->
name|display
operator|->
name|gimp
argument_list|,
name|context
argument_list|,
name|GIMP_PROGRESS
argument_list|(
name|shell
operator|->
name|display
argument_list|)
argument_list|,
name|uri
argument_list|,
name|FALSE
argument_list|,
operator|&
name|status
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|image
operator|&&
name|status
operator|!=
name|GIMP_PDB_CANCEL
condition|)
name|warn
operator|=
name|TRUE
expr_stmt|;
block|}
else|else
block|{
name|GList
modifier|*
name|new_layers
decl_stmt|;
name|new_layers
operator|=
name|file_open_layers
argument_list|(
name|shell
operator|->
name|display
operator|->
name|gimp
argument_list|,
name|context
argument_list|,
name|GIMP_PROGRESS
argument_list|(
name|shell
operator|->
name|display
argument_list|)
argument_list|,
name|image
argument_list|,
name|FALSE
argument_list|,
name|uri
argument_list|,
name|GIMP_RUN_INTERACTIVE
argument_list|,
name|NULL
argument_list|,
operator|&
name|status
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|new_layers
condition|)
block|{
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
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
name|gimp_image_add_layers
argument_list|(
name|image
argument_list|,
name|new_layers
argument_list|,
operator|-
literal|1
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|_
argument_list|(
literal|"Drop layers"
argument_list|)
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|new_layers
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|status
operator|!=
name|GIMP_PDB_CANCEL
condition|)
block|{
name|warn
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
if|if
condition|(
name|warn
condition|)
block|{
name|gchar
modifier|*
name|filename
init|=
name|file_utils_uri_display_name
argument_list|(
name|uri
argument_list|)
decl_stmt|;
name|gimp_message
argument_list|(
name|shell
operator|->
name|display
operator|->
name|gimp
argument_list|,
name|G_OBJECT
argument_list|(
name|shell
operator|->
name|display
argument_list|)
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
name|_
argument_list|(
literal|"Opening '%s' failed:\n\n%s"
argument_list|)
argument_list|,
name|filename
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
block|}
name|gimp_display_shell_dnd_flush
argument_list|(
name|shell
argument_list|,
name|image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_drop_component (GtkWidget * widget,gint x,gint y,GimpImage * image,GimpChannelType component,gpointer data)
name|gimp_display_shell_drop_component
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpChannelType
name|component
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|dest_image
init|=
name|shell
operator|->
name|display
operator|->
name|image
decl_stmt|;
name|GimpChannel
modifier|*
name|channel
decl_stmt|;
name|GimpItem
modifier|*
name|new_item
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|desc
decl_stmt|;
name|GIMP_LOG
argument_list|(
name|DND
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|display
operator|->
name|gimp
operator|->
name|busy
condition|)
return|return;
if|if
condition|(
operator|!
name|dest_image
condition|)
return|return;
name|channel
operator|=
name|gimp_channel_new_from_component
argument_list|(
name|image
argument_list|,
name|component
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|new_item
operator|=
name|gimp_item_convert
argument_list|(
name|GIMP_ITEM
argument_list|(
name|channel
argument_list|)
argument_list|,
name|dest_image
argument_list|,
name|GIMP_TYPE_LAYER
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|channel
argument_list|)
expr_stmt|;
if|if
condition|(
name|new_item
condition|)
block|{
name|GimpLayer
modifier|*
name|new_layer
init|=
name|GIMP_LAYER
argument_list|(
name|new_item
argument_list|)
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
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|gimp_enum_get_value
argument_list|(
name|GIMP_TYPE_CHANNEL_TYPE
argument_list|,
name|component
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|desc
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_object_take_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|new_layer
argument_list|)
argument_list|,
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"%s Channel Copy"
argument_list|)
argument_list|,
name|desc
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_start
argument_list|(
name|dest_image
argument_list|,
name|GIMP_UNDO_GROUP_EDIT_PASTE
argument_list|,
name|_
argument_list|(
literal|"Drop New Layer"
argument_list|)
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
name|gimp_item_offsets
argument_list|(
name|new_item
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
name|off_x
operator|=
name|x
operator|+
operator|(
name|width
operator|-
name|gimp_item_width
argument_list|(
name|new_item
argument_list|)
operator|)
operator|/
literal|2
operator|-
name|off_x
expr_stmt|;
name|off_y
operator|=
name|y
operator|+
operator|(
name|height
operator|-
name|gimp_item_height
argument_list|(
name|new_item
argument_list|)
operator|)
operator|/
literal|2
operator|-
name|off_y
expr_stmt|;
name|gimp_item_translate
argument_list|(
name|new_item
argument_list|,
name|off_x
argument_list|,
name|off_y
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_image_add_layer
argument_list|(
name|dest_image
argument_list|,
name|new_layer
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_end
argument_list|(
name|dest_image
argument_list|)
expr_stmt|;
name|gimp_display_shell_dnd_flush
argument_list|(
name|shell
argument_list|,
name|dest_image
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_drop_pixbuf (GtkWidget * widget,gint x,gint y,GdkPixbuf * pixbuf,gpointer data)
name|gimp_display_shell_drop_pixbuf
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GdkPixbuf
modifier|*
name|pixbuf
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|shell
operator|->
name|display
operator|->
name|image
decl_stmt|;
name|GimpLayer
modifier|*
name|new_layer
decl_stmt|;
name|GIMP_LOG
argument_list|(
name|DND
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|display
operator|->
name|gimp
operator|->
name|busy
condition|)
return|return;
if|if
condition|(
operator|!
name|image
condition|)
return|return;
name|new_layer
operator|=
name|gimp_layer_new_from_pixbuf
argument_list|(
name|pixbuf
argument_list|,
name|image
argument_list|,
name|gimp_image_base_type_with_alpha
argument_list|(
name|image
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Dropped Buffer"
argument_list|)
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|)
expr_stmt|;
if|if
condition|(
name|new_layer
condition|)
block|{
name|GimpItem
modifier|*
name|new_item
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
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|new_item
operator|=
name|GIMP_ITEM
argument_list|(
name|new_layer
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_start
argument_list|(
name|image
argument_list|,
name|GIMP_UNDO_GROUP_EDIT_PASTE
argument_list|,
name|_
argument_list|(
literal|"Drop New Layer"
argument_list|)
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
name|gimp_item_offsets
argument_list|(
name|new_item
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
name|off_x
operator|=
name|x
operator|+
operator|(
name|width
operator|-
name|gimp_item_width
argument_list|(
name|new_item
argument_list|)
operator|)
operator|/
literal|2
operator|-
name|off_x
expr_stmt|;
name|off_y
operator|=
name|y
operator|+
operator|(
name|height
operator|-
name|gimp_item_height
argument_list|(
name|new_item
argument_list|)
operator|)
operator|/
literal|2
operator|-
name|off_y
expr_stmt|;
name|gimp_item_translate
argument_list|(
name|new_item
argument_list|,
name|off_x
argument_list|,
name|off_y
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_image_add_layer
argument_list|(
name|image
argument_list|,
name|new_layer
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_end
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gimp_display_shell_dnd_flush
argument_list|(
name|shell
argument_list|,
name|image
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

