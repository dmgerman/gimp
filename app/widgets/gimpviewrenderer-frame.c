begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpviewrenderer-frame.c  * Copyright (C) 2004 Sven Neumann<sven@gimp.org>  *  * Contains code taken from eel, the Eazel Extensions Library.  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpviewable.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewrenderer.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewrenderer-frame.h"
end_include

begin_comment
comment|/* utility to stretch a frame to the desired size */
end_comment

begin_function
specifier|static
name|void
DECL|function|draw_frame_row (GdkPixbuf * frame_image,gint target_width,gint source_width,gint source_v_position,gint dest_v_position,GdkPixbuf * result_pixbuf,gint left_offset,gint height)
name|draw_frame_row
parameter_list|(
name|GdkPixbuf
modifier|*
name|frame_image
parameter_list|,
name|gint
name|target_width
parameter_list|,
name|gint
name|source_width
parameter_list|,
name|gint
name|source_v_position
parameter_list|,
name|gint
name|dest_v_position
parameter_list|,
name|GdkPixbuf
modifier|*
name|result_pixbuf
parameter_list|,
name|gint
name|left_offset
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
name|gint
name|remaining_width
init|=
name|target_width
decl_stmt|;
name|gint
name|h_offset
init|=
literal|0
decl_stmt|;
while|while
condition|(
name|remaining_width
operator|>
literal|0
condition|)
block|{
name|gint
name|slab_width
init|=
operator|(
name|remaining_width
operator|>
name|source_width
condition|?
name|source_width
else|:
name|remaining_width
operator|)
decl_stmt|;
name|gdk_pixbuf_copy_area
argument_list|(
name|frame_image
argument_list|,
name|left_offset
argument_list|,
name|source_v_position
argument_list|,
name|slab_width
argument_list|,
name|height
argument_list|,
name|result_pixbuf
argument_list|,
name|left_offset
operator|+
name|h_offset
argument_list|,
name|dest_v_position
argument_list|)
expr_stmt|;
name|remaining_width
operator|-=
name|slab_width
expr_stmt|;
name|h_offset
operator|+=
name|slab_width
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/* utility to draw the middle section of the frame in a loop */
end_comment

begin_function
specifier|static
name|void
DECL|function|draw_frame_column (GdkPixbuf * frame_image,gint target_height,gint source_height,gint source_h_position,gint dest_h_position,GdkPixbuf * result_pixbuf,gint top_offset,int width)
name|draw_frame_column
parameter_list|(
name|GdkPixbuf
modifier|*
name|frame_image
parameter_list|,
name|gint
name|target_height
parameter_list|,
name|gint
name|source_height
parameter_list|,
name|gint
name|source_h_position
parameter_list|,
name|gint
name|dest_h_position
parameter_list|,
name|GdkPixbuf
modifier|*
name|result_pixbuf
parameter_list|,
name|gint
name|top_offset
parameter_list|,
name|int
name|width
parameter_list|)
block|{
name|gint
name|remaining_height
init|=
name|target_height
decl_stmt|;
name|gint
name|v_offset
init|=
literal|0
decl_stmt|;
while|while
condition|(
name|remaining_height
operator|>
literal|0
condition|)
block|{
name|gint
name|slab_height
init|=
operator|(
name|remaining_height
operator|>
name|source_height
condition|?
name|source_height
else|:
name|remaining_height
operator|)
decl_stmt|;
name|gdk_pixbuf_copy_area
argument_list|(
name|frame_image
argument_list|,
name|source_h_position
argument_list|,
name|top_offset
argument_list|,
name|width
argument_list|,
name|slab_height
argument_list|,
name|result_pixbuf
argument_list|,
name|dest_h_position
argument_list|,
name|top_offset
operator|+
name|v_offset
argument_list|)
expr_stmt|;
name|remaining_height
operator|-=
name|slab_height
expr_stmt|;
name|v_offset
operator|+=
name|slab_height
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GdkPixbuf
modifier|*
DECL|function|stretch_frame_image (GdkPixbuf * frame_image,gint left_offset,gint top_offset,gint right_offset,gint bottom_offset,gint dest_width,gint dest_height)
name|stretch_frame_image
parameter_list|(
name|GdkPixbuf
modifier|*
name|frame_image
parameter_list|,
name|gint
name|left_offset
parameter_list|,
name|gint
name|top_offset
parameter_list|,
name|gint
name|right_offset
parameter_list|,
name|gint
name|bottom_offset
parameter_list|,
name|gint
name|dest_width
parameter_list|,
name|gint
name|dest_height
parameter_list|)
block|{
name|GdkPixbuf
modifier|*
name|pixbuf
decl_stmt|;
name|guchar
modifier|*
name|pixels
decl_stmt|;
name|gint
name|frame_width
decl_stmt|,
name|frame_height
decl_stmt|;
name|gint
name|row_stride
decl_stmt|;
name|gint
name|target_width
decl_stmt|,
name|target_frame_width
decl_stmt|;
name|gint
name|target_height
decl_stmt|,
name|target_frame_height
decl_stmt|;
name|frame_width
operator|=
name|gdk_pixbuf_get_width
argument_list|(
name|frame_image
argument_list|)
expr_stmt|;
name|frame_height
operator|=
name|gdk_pixbuf_get_height
argument_list|(
name|frame_image
argument_list|)
expr_stmt|;
name|pixbuf
operator|=
name|gdk_pixbuf_new
argument_list|(
name|GDK_COLORSPACE_RGB
argument_list|,
name|TRUE
argument_list|,
literal|8
argument_list|,
name|dest_width
argument_list|,
name|dest_height
argument_list|)
expr_stmt|;
name|gdk_pixbuf_fill
argument_list|(
name|pixbuf
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|row_stride
operator|=
name|gdk_pixbuf_get_rowstride
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|pixels
operator|=
name|gdk_pixbuf_get_pixels
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|target_width
operator|=
name|dest_width
operator|-
name|left_offset
operator|-
name|right_offset
expr_stmt|;
name|target_height
operator|=
name|dest_height
operator|-
name|top_offset
operator|-
name|bottom_offset
expr_stmt|;
name|target_frame_width
operator|=
name|frame_width
operator|-
name|left_offset
operator|-
name|right_offset
expr_stmt|;
name|target_frame_height
operator|=
name|frame_height
operator|-
name|top_offset
operator|-
name|bottom_offset
expr_stmt|;
name|left_offset
operator|+=
name|MIN
argument_list|(
name|target_width
operator|/
literal|4
argument_list|,
name|target_frame_width
operator|/
literal|4
argument_list|)
expr_stmt|;
name|right_offset
operator|+=
name|MIN
argument_list|(
name|target_width
operator|/
literal|4
argument_list|,
name|target_frame_width
operator|/
literal|4
argument_list|)
expr_stmt|;
name|top_offset
operator|+=
name|MIN
argument_list|(
name|target_height
operator|/
literal|4
argument_list|,
name|target_frame_height
operator|/
literal|4
argument_list|)
expr_stmt|;
name|bottom_offset
operator|+=
name|MIN
argument_list|(
name|target_height
operator|/
literal|4
argument_list|,
name|target_frame_height
operator|/
literal|4
argument_list|)
expr_stmt|;
name|target_width
operator|=
name|dest_width
operator|-
name|left_offset
operator|-
name|right_offset
expr_stmt|;
name|target_height
operator|=
name|dest_height
operator|-
name|top_offset
operator|-
name|bottom_offset
expr_stmt|;
name|target_frame_width
operator|=
name|frame_width
operator|-
name|left_offset
operator|-
name|right_offset
expr_stmt|;
name|target_frame_height
operator|=
name|frame_height
operator|-
name|top_offset
operator|-
name|bottom_offset
expr_stmt|;
comment|/* draw the left top corner  and top row */
name|gdk_pixbuf_copy_area
argument_list|(
name|frame_image
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|left_offset
argument_list|,
name|top_offset
argument_list|,
name|pixbuf
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|draw_frame_row
argument_list|(
name|frame_image
argument_list|,
name|target_width
argument_list|,
name|target_frame_width
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|pixbuf
argument_list|,
name|left_offset
argument_list|,
name|top_offset
argument_list|)
expr_stmt|;
comment|/* draw the right top corner and left column */
name|gdk_pixbuf_copy_area
argument_list|(
name|frame_image
argument_list|,
name|frame_width
operator|-
name|right_offset
argument_list|,
literal|0
argument_list|,
name|right_offset
argument_list|,
name|top_offset
argument_list|,
name|pixbuf
argument_list|,
name|dest_width
operator|-
name|right_offset
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|draw_frame_column
argument_list|(
name|frame_image
argument_list|,
name|target_height
argument_list|,
name|target_frame_height
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|pixbuf
argument_list|,
name|top_offset
argument_list|,
name|left_offset
argument_list|)
expr_stmt|;
comment|/* draw the bottom right corner and bottom row */
name|gdk_pixbuf_copy_area
argument_list|(
name|frame_image
argument_list|,
name|frame_width
operator|-
name|right_offset
argument_list|,
name|frame_height
operator|-
name|bottom_offset
argument_list|,
name|right_offset
argument_list|,
name|bottom_offset
argument_list|,
name|pixbuf
argument_list|,
name|dest_width
operator|-
name|right_offset
argument_list|,
name|dest_height
operator|-
name|bottom_offset
argument_list|)
expr_stmt|;
name|draw_frame_row
argument_list|(
name|frame_image
argument_list|,
name|target_width
argument_list|,
name|target_frame_width
argument_list|,
name|frame_height
operator|-
name|bottom_offset
argument_list|,
name|dest_height
operator|-
name|bottom_offset
argument_list|,
name|pixbuf
argument_list|,
name|left_offset
argument_list|,
name|bottom_offset
argument_list|)
expr_stmt|;
comment|/* draw the bottom left corner and the right column */
name|gdk_pixbuf_copy_area
argument_list|(
name|frame_image
argument_list|,
literal|0
argument_list|,
name|frame_height
operator|-
name|bottom_offset
argument_list|,
name|left_offset
argument_list|,
name|bottom_offset
argument_list|,
name|pixbuf
argument_list|,
literal|0
argument_list|,
name|dest_height
operator|-
name|bottom_offset
argument_list|)
expr_stmt|;
name|draw_frame_column
argument_list|(
name|frame_image
argument_list|,
name|target_height
argument_list|,
name|target_frame_height
argument_list|,
name|frame_width
operator|-
name|right_offset
argument_list|,
name|dest_width
operator|-
name|right_offset
argument_list|,
name|pixbuf
argument_list|,
name|top_offset
argument_list|,
name|right_offset
argument_list|)
expr_stmt|;
return|return
name|pixbuf
return|;
block|}
end_function

begin_function
specifier|static
name|GdkPixbuf
modifier|*
DECL|function|gimp_view_renderer_get_frame (GimpViewRenderer * renderer,gint width,gint height)
name|gimp_view_renderer_get_frame
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
name|GimpViewRendererClass
modifier|*
name|class
init|=
name|GIMP_VIEW_RENDERER_GET_CLASS
argument_list|(
name|renderer
argument_list|)
decl_stmt|;
return|return
name|stretch_frame_image
argument_list|(
name|class
operator|->
name|frame
argument_list|,
name|class
operator|->
name|frame_left
argument_list|,
name|class
operator|->
name|frame_top
argument_list|,
name|class
operator|->
name|frame_right
argument_list|,
name|class
operator|->
name|frame_bottom
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_view_renderer_ensure_frame (GimpViewRenderer * renderer,GtkWidget * widget)
name|gimp_view_renderer_ensure_frame
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|GimpViewRendererClass
modifier|*
name|class
init|=
name|GIMP_VIEW_RENDERER_GET_CLASS
argument_list|(
name|renderer
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|class
operator|->
name|frame
condition|)
block|{
name|class
operator|->
name|frame
operator|=
name|gtk_widget_render_icon
argument_list|(
name|widget
argument_list|,
name|GIMP_STOCK_FRAME
argument_list|,
name|GTK_ICON_SIZE_DIALOG
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  FIXME: shouldn't be hardcoded  */
name|class
operator|->
name|frame_left
operator|=
literal|3
expr_stmt|;
name|class
operator|->
name|frame_top
operator|=
literal|3
expr_stmt|;
name|class
operator|->
name|frame_right
operator|=
literal|5
expr_stmt|;
name|class
operator|->
name|frame_bottom
operator|=
literal|5
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GdkPixbuf
modifier|*
DECL|function|gimp_view_renderer_get_frame_pixbuf (GimpViewRenderer * renderer,GtkWidget * widget,gint width,gint height)
name|gimp_view_renderer_get_frame_pixbuf
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
name|GimpViewRendererClass
modifier|*
name|class
decl_stmt|;
name|GdkPixbuf
modifier|*
name|frame
decl_stmt|;
name|GdkPixbuf
modifier|*
name|pixbuf
decl_stmt|;
name|gint
name|w
decl_stmt|,
name|h
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_VIEW_RENDERER
argument_list|(
name|renderer
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_VIEWABLE
argument_list|(
name|renderer
operator|->
name|viewable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_view_renderer_ensure_frame
argument_list|(
name|renderer
argument_list|,
name|widget
argument_list|)
expr_stmt|;
name|class
operator|=
name|GIMP_VIEW_RENDERER_GET_CLASS
argument_list|(
name|renderer
argument_list|)
expr_stmt|;
name|w
operator|=
name|width
operator|-
name|class
operator|->
name|frame_left
operator|-
name|class
operator|->
name|frame_right
expr_stmt|;
name|h
operator|=
name|height
operator|-
name|class
operator|->
name|frame_top
operator|-
name|class
operator|->
name|frame_bottom
expr_stmt|;
if|if
condition|(
name|w
operator|>
literal|12
operator|&&
name|h
operator|>
literal|12
condition|)
block|{
name|pixbuf
operator|=
name|gimp_viewable_get_pixbuf
argument_list|(
name|renderer
operator|->
name|viewable
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|pixbuf
condition|)
return|return
name|NULL
return|;
name|x
operator|=
name|class
operator|->
name|frame_left
expr_stmt|;
name|y
operator|=
name|class
operator|->
name|frame_top
expr_stmt|;
name|w
operator|=
name|gdk_pixbuf_get_width
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|h
operator|=
name|gdk_pixbuf_get_height
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_view_renderer_get_frame
argument_list|(
name|renderer
argument_list|,
name|w
operator|+
name|x
operator|+
name|class
operator|->
name|frame_right
argument_list|,
name|h
operator|+
name|y
operator|+
name|class
operator|->
name|frame_bottom
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|pixbuf
operator|=
name|gimp_viewable_get_pixbuf
argument_list|(
name|renderer
operator|->
name|viewable
argument_list|,
name|width
operator|-
literal|2
argument_list|,
name|height
operator|-
literal|2
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|pixbuf
condition|)
return|return
name|NULL
return|;
name|x
operator|=
literal|1
expr_stmt|;
name|y
operator|=
literal|1
expr_stmt|;
name|w
operator|=
name|gdk_pixbuf_get_width
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|h
operator|=
name|gdk_pixbuf_get_height
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gdk_pixbuf_new
argument_list|(
name|GDK_COLORSPACE_RGB
argument_list|,
name|FALSE
argument_list|,
literal|8
argument_list|,
name|w
operator|+
literal|2
argument_list|,
name|h
operator|+
literal|2
argument_list|)
expr_stmt|;
name|gdk_pixbuf_fill
argument_list|(
name|frame
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
name|gdk_pixbuf_copy_area
argument_list|(
name|pixbuf
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|w
argument_list|,
name|h
argument_list|,
name|frame
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
return|return
name|frame
return|;
block|}
end_function

end_unit

