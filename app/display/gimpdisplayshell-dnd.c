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
file|"core/gimppattern.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
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
file|"gimp-intl.h"
end_include

begin_function
name|void
DECL|function|gimp_display_shell_drop_drawable (GtkWidget * widget,GimpViewable * viewable,gpointer data)
name|gimp_display_shell_drop_drawable
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
name|GimpLayer
modifier|*
name|new_layer
decl_stmt|;
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|gdisp
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|data
argument_list|)
operator|->
name|gdisp
expr_stmt|;
if|if
condition|(
name|gdisp
operator|->
name|gimage
operator|->
name|gimp
operator|->
name|busy
condition|)
return|return;
name|drawable
operator|=
name|GIMP_DRAWABLE
argument_list|(
name|viewable
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_start
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|GIMP_UNDO_GROUP_EDIT_PASTE
argument_list|,
name|_
argument_list|(
literal|"Drop New Layer"
argument_list|)
argument_list|)
expr_stmt|;
name|new_layer
operator|=
name|gimp_layer_new_from_drawable
argument_list|(
name|drawable
argument_list|,
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|off_x
operator|=
operator|(
name|gdisp
operator|->
name|gimage
operator|->
name|width
operator|-
name|gimp_item_width
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
operator|)
operator|/
literal|2
expr_stmt|;
name|off_y
operator|=
operator|(
name|gdisp
operator|->
name|gimage
operator|->
name|height
operator|-
name|gimp_item_height
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
operator|)
operator|/
literal|2
expr_stmt|;
name|gimp_item_translate
argument_list|(
name|GIMP_ITEM
argument_list|(
name|new_layer
argument_list|)
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
name|gdisp
operator|->
name|gimage
argument_list|,
name|new_layer
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_end
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|gimp_context_set_display
argument_list|(
name|gimp_get_user_context
argument_list|(
name|gdisp
operator|->
name|gimage
operator|->
name|gimp
argument_list|)
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_bucket_fill (GimpImage * gimage,GimpBucketFillMode fill_mode,const GimpRGB * color,GimpPattern * pattern)
name|gimp_display_shell_bucket_fill
parameter_list|(
name|GimpImage
modifier|*
name|gimage
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
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
if|if
condition|(
name|gimage
operator|->
name|gimp
operator|->
name|busy
condition|)
return|return;
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
name|drawable
condition|)
return|return;
comment|/*  Get the bucket fill context  */
name|tool_info
operator|=
operator|(
name|GimpToolInfo
operator|*
operator|)
name|gimp_container_get_child_by_name
argument_list|(
name|gimage
operator|->
name|gimp
operator|->
name|tool_info_list
argument_list|,
literal|"gimp-bucket-fill-tool"
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_info
operator|&&
name|tool_info
operator|->
name|tool_options
condition|)
block|{
name|context
operator|=
name|GIMP_CONTEXT
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|context
operator|=
name|gimp_get_user_context
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|)
expr_stmt|;
block|}
name|gimp_drawable_bucket_fill_full
argument_list|(
name|drawable
argument_list|,
name|fill_mode
argument_list|,
name|gimp_context_get_paint_mode
argument_list|(
name|context
argument_list|)
argument_list|,
name|gimp_context_get_opacity
argument_list|(
name|context
argument_list|)
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
comment|/* fill params */
argument_list|,
name|color
argument_list|,
name|pattern
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
DECL|function|gimp_display_shell_drop_pattern (GtkWidget * widget,GimpViewable * viewable,gpointer data)
name|gimp_display_shell_drop_pattern
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
name|gdisp
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|data
argument_list|)
operator|->
name|gdisp
expr_stmt|;
if|if
condition|(
name|GIMP_IS_PATTERN
argument_list|(
name|viewable
argument_list|)
condition|)
block|{
name|gimp_display_shell_bucket_fill
argument_list|(
name|gdisp
operator|->
name|gimage
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
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_drop_color (GtkWidget * widget,const GimpRGB * color,gpointer data)
name|gimp_display_shell_drop_color
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
name|gdisp
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|data
argument_list|)
operator|->
name|gdisp
expr_stmt|;
name|gimp_display_shell_bucket_fill
argument_list|(
name|gdisp
operator|->
name|gimage
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
name|void
DECL|function|gimp_display_shell_drop_buffer (GtkWidget * widget,GimpViewable * viewable,gpointer data)
name|gimp_display_shell_drop_buffer
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpBuffer
modifier|*
name|buffer
decl_stmt|;
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
name|gdisp
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|data
argument_list|)
operator|->
name|gdisp
expr_stmt|;
if|if
condition|(
name|gdisp
operator|->
name|gimage
operator|->
name|gimp
operator|->
name|busy
condition|)
return|return;
name|buffer
operator|=
name|GIMP_BUFFER
argument_list|(
name|viewable
argument_list|)
expr_stmt|;
comment|/* FIXME: popup a menu for selecting "Paste Into" */
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
name|buffer
argument_list|,
name|FALSE
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

end_unit

