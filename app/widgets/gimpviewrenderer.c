begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpPreview Widget  * Copyright (C) 2001 Michael Natterer  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimppreview.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewable.h"
end_include

begin_include
include|#
directive|include
file|"image_render.h"
end_include

begin_include
include|#
directive|include
file|"temp_buf.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimplimits.h"
end_include

begin_define
DECL|macro|PREVIEW_EVENT_MASK
define|#
directive|define
name|PREVIEW_EVENT_MASK
value|(GDK_BUTTON_PRESS_MASK   | \                              GDK_BUTTON_RELEASE_MASK | \                              GDK_ENTER_NOTIFY_MASK   | \                              GDK_LEAVE_NOTIFY_MASK)
end_define

begin_function_decl
specifier|static
name|void
name|gimp_preview_class_init
parameter_list|(
name|GimpPreviewClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_preview_init
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_preview_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_preview_size_allocate
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkAllocation
modifier|*
name|allocation
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|gimp_preview_button_press_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|gimp_preview_button_release_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_preview_paint
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_preview_idle_paint
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GtkPreviewClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GtkType
DECL|function|gimp_preview_get_type (void)
name|gimp_preview_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GtkType
name|preview_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|preview_type
condition|)
block|{
name|GtkTypeInfo
name|preview_info
init|=
block|{
literal|"GimpPreview"
block|,
sizeof|sizeof
argument_list|(
name|GimpPreview
argument_list|)
block|,
sizeof|sizeof
argument_list|(
name|GimpPreviewClass
argument_list|)
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|gimp_preview_class_init
block|,
operator|(
name|GtkObjectInitFunc
operator|)
name|gimp_preview_init
block|,
comment|/* reserved_1 */
name|NULL
block|,
comment|/* reserved_2 */
name|NULL
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|NULL
block|}
decl_stmt|;
name|preview_type
operator|=
name|gtk_type_unique
argument_list|(
name|GTK_TYPE_PREVIEW
argument_list|,
operator|&
name|preview_info
argument_list|)
expr_stmt|;
block|}
return|return
name|preview_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_preview_class_init (GimpPreviewClass * klass)
name|gimp_preview_class_init
parameter_list|(
name|GimpPreviewClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GtkWidgetClass
modifier|*
name|widget_class
decl_stmt|;
name|object_class
operator|=
operator|(
name|GtkObjectClass
operator|*
operator|)
name|klass
expr_stmt|;
name|widget_class
operator|=
operator|(
name|GtkWidgetClass
operator|*
operator|)
name|klass
expr_stmt|;
name|parent_class
operator|=
name|gtk_type_class
argument_list|(
name|GTK_TYPE_PREVIEW
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_preview_destroy
expr_stmt|;
name|widget_class
operator|->
name|size_allocate
operator|=
name|gimp_preview_size_allocate
expr_stmt|;
name|widget_class
operator|->
name|button_press_event
operator|=
name|gimp_preview_button_press_event
expr_stmt|;
name|widget_class
operator|->
name|button_release_event
operator|=
name|gimp_preview_button_release_event
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_preview_init (GimpPreview * preview)
name|gimp_preview_init
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|)
block|{
name|preview
operator|->
name|viewable
operator|=
name|NULL
expr_stmt|;
name|preview
operator|->
name|idle_id
operator|=
literal|0
expr_stmt|;
name|GTK_PREVIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|type
operator|=
name|GTK_PREVIEW_COLOR
expr_stmt|;
name|GTK_PREVIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|bpp
operator|=
literal|3
expr_stmt|;
name|GTK_PREVIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|dither
operator|=
name|GDK_RGB_DITHER_NORMAL
expr_stmt|;
name|gtk_widget_set_events
argument_list|(
name|GTK_WIDGET
argument_list|(
name|preview
argument_list|)
argument_list|,
name|PREVIEW_EVENT_MASK
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_preview_destroy (GtkObject * object)
name|gimp_preview_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
if|if
condition|(
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
condition|)
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_preview_new (GimpViewable * viewable)
name|gimp_preview_new
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
block|{
name|GimpPreview
modifier|*
name|preview
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|viewable
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_VIEWABLE
argument_list|(
name|viewable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|preview
operator|=
name|gtk_type_new
argument_list|(
name|GIMP_TYPE_PREVIEW
argument_list|)
expr_stmt|;
name|preview
operator|->
name|viewable
operator|=
name|viewable
expr_stmt|;
name|gtk_signal_connect_object_while_alive
argument_list|(
name|GTK_OBJECT
argument_list|(
name|viewable
argument_list|)
argument_list|,
literal|"invalidate_preview"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_preview_paint
argument_list|)
argument_list|,
name|GTK_OBJECT
argument_list|(
name|preview
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_preview_size
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|,
literal|32
argument_list|,
literal|32
argument_list|)
expr_stmt|;
name|gtk_preview_set_expand
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|preview
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|gimp_preview_button_press_event (GtkWidget * widget,GdkEventButton * bevent)
name|gimp_preview_button_press_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|)
block|{
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|gimp_preview_button_release_event (GtkWidget * widget,GdkEventButton * bevent)
name|gimp_preview_button_release_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|)
block|{
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_preview_size_allocate (GtkWidget * widget,GtkAllocation * allocation)
name|gimp_preview_size_allocate
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkAllocation
modifier|*
name|allocation
parameter_list|)
block|{
if|if
condition|(
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|size_allocate
condition|)
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|size_allocate
argument_list|(
name|widget
argument_list|,
name|allocation
argument_list|)
expr_stmt|;
name|gimp_preview_paint
argument_list|(
name|GIMP_PREVIEW
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_preview_paint (GimpPreview * preview)
name|gimp_preview_paint
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|)
block|{
if|if
condition|(
name|preview
operator|->
name|idle_id
condition|)
return|return;
name|preview
operator|->
name|idle_id
operator|=
name|g_idle_add_full
argument_list|(
name|G_PRIORITY_LOW
argument_list|,
operator|(
name|GSourceFunc
operator|)
name|gimp_preview_idle_paint
argument_list|,
name|preview
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_preview_idle_paint (GimpPreview * preview)
name|gimp_preview_idle_paint
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|)
block|{
name|TempBuf
modifier|*
name|temp_buf
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gint
name|channel
decl_stmt|;
name|preview
operator|->
name|idle_id
operator|=
literal|0
expr_stmt|;
name|temp_buf
operator|=
name|gimp_viewable_preview_new
argument_list|(
name|preview
operator|->
name|viewable
argument_list|,
name|GTK_WIDGET
argument_list|(
name|preview
argument_list|)
operator|->
name|allocation
operator|.
name|width
argument_list|,
name|GTK_WIDGET
argument_list|(
name|preview
argument_list|)
operator|->
name|allocation
operator|.
name|height
argument_list|)
expr_stmt|;
name|width
operator|=
name|temp_buf
operator|->
name|width
expr_stmt|;
name|height
operator|=
name|temp_buf
operator|->
name|height
expr_stmt|;
name|channel
operator|=
operator|-
literal|1
expr_stmt|;
comment|/*  from layers_dialog.c  */
block|{
name|guchar
modifier|*
name|src
decl_stmt|,
modifier|*
name|s
decl_stmt|;
name|guchar
modifier|*
name|cb
decl_stmt|;
name|guchar
modifier|*
name|buf
decl_stmt|;
name|gint
name|a
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|,
name|b
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
name|gint
name|rowstride
decl_stmt|;
name|gboolean
name|color_buf
decl_stmt|;
name|gboolean
name|color
decl_stmt|;
name|gint
name|alpha
decl_stmt|;
name|gboolean
name|has_alpha
decl_stmt|;
name|gint
name|image_bytes
decl_stmt|;
name|gint
name|offset
decl_stmt|;
name|alpha
operator|=
name|ALPHA_PIX
expr_stmt|;
comment|/*  Here are the different cases this functions handles correctly:      *  1)  Offset temp_buf which does not necessarily cover full image area      *  2)  Color conversion of temp_buf if it is gray and image is color      *  3)  Background check buffer for transparent temp_bufs      *  4)  Using the optional "channel" argument, one channel can be extracted      *      from a multi-channel temp_buf and composited as a grayscale      *  Prereqs:      *  1)  Grayscale temp_bufs have bytes == {1, 2}      *  2)  Color temp_bufs have bytes == {3, 4}      *  3)  If image is gray, then temp_buf should have bytes == {1, 2}      */
name|color_buf
operator|=
operator|(
name|GTK_PREVIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|type
operator|==
name|GTK_PREVIEW_COLOR
operator|)
expr_stmt|;
name|image_bytes
operator|=
operator|(
name|color_buf
operator|)
condition|?
literal|3
else|:
literal|1
expr_stmt|;
name|has_alpha
operator|=
operator|(
name|temp_buf
operator|->
name|bytes
operator|==
literal|2
operator|||
name|temp_buf
operator|->
name|bytes
operator|==
literal|4
operator|)
expr_stmt|;
name|rowstride
operator|=
name|temp_buf
operator|->
name|width
operator|*
name|temp_buf
operator|->
name|bytes
expr_stmt|;
comment|/*  Determine if the preview buf supplied is color      *   Generally, if the bytes == {3, 4}, this is true.      *   However, if the channel argument supplied is not -1, then      *   the preview buf is assumed to be gray despite the number of      *   channels it contains      */
name|color
operator|=
operator|(
operator|(
name|channel
operator|==
operator|-
literal|1
operator|)
operator|&&
operator|(
name|temp_buf
operator|->
name|bytes
operator|==
literal|3
operator|||
name|temp_buf
operator|->
name|bytes
operator|==
literal|4
operator|)
operator|)
expr_stmt|;
if|if
condition|(
name|has_alpha
condition|)
block|{
name|buf
operator|=
name|render_check_buf
expr_stmt|;
name|alpha
operator|=
operator|(
operator|(
name|color
operator|)
condition|?
name|ALPHA_PIX
else|:
operator|(
operator|(
name|channel
operator|!=
operator|-
literal|1
operator|)
condition|?
operator|(
name|temp_buf
operator|->
name|bytes
operator|-
literal|1
operator|)
else|:
name|ALPHA_G_PIX
operator|)
operator|)
expr_stmt|;
block|}
else|else
block|{
name|buf
operator|=
name|render_empty_buf
expr_stmt|;
block|}
name|x1
operator|=
name|CLAMP
argument_list|(
name|temp_buf
operator|->
name|x
argument_list|,
literal|0
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|y1
operator|=
name|CLAMP
argument_list|(
name|temp_buf
operator|->
name|y
argument_list|,
literal|0
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|x2
operator|=
name|CLAMP
argument_list|(
name|temp_buf
operator|->
name|x
operator|+
name|temp_buf
operator|->
name|width
argument_list|,
literal|0
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|y2
operator|=
name|CLAMP
argument_list|(
name|temp_buf
operator|->
name|y
operator|+
name|temp_buf
operator|->
name|height
argument_list|,
literal|0
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|src
operator|=
name|temp_buf_data
argument_list|(
name|temp_buf
argument_list|)
operator|+
operator|(
operator|(
name|y1
operator|-
name|temp_buf
operator|->
name|y
operator|)
operator|*
name|rowstride
operator|+
operator|(
name|x1
operator|-
name|temp_buf
operator|->
name|x
operator|)
operator|*
name|temp_buf
operator|->
name|bytes
operator|)
expr_stmt|;
comment|/*  One last thing for efficiency's sake:  */
if|if
condition|(
name|channel
operator|==
operator|-
literal|1
condition|)
name|channel
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|height
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|i
operator|&
literal|0x4
condition|)
block|{
name|offset
operator|=
literal|4
expr_stmt|;
name|cb
operator|=
name|buf
operator|+
name|offset
operator|*
literal|3
expr_stmt|;
block|}
else|else
block|{
name|offset
operator|=
literal|0
expr_stmt|;
name|cb
operator|=
name|buf
expr_stmt|;
block|}
comment|/*  The interesting stuff between leading& trailing  	 *  vertical transparency 	 */
if|if
condition|(
name|i
operator|>=
name|y1
operator|&&
name|i
operator|<
name|y2
condition|)
block|{
comment|/*  Handle the leading transparency  */
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|x1
condition|;
name|j
operator|++
control|)
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|image_bytes
condition|;
name|b
operator|++
control|)
name|render_temp_buf
index|[
name|j
operator|*
name|image_bytes
operator|+
name|b
index|]
operator|=
name|cb
index|[
name|j
operator|*
literal|3
operator|+
name|b
index|]
expr_stmt|;
comment|/*  The stuff in the middle  */
name|s
operator|=
name|src
expr_stmt|;
for|for
control|(
name|j
operator|=
name|x1
init|;
name|j
operator|<
name|x2
condition|;
name|j
operator|++
control|)
block|{
if|if
condition|(
name|color
condition|)
block|{
if|if
condition|(
name|has_alpha
condition|)
block|{
name|a
operator|=
name|s
index|[
name|alpha
index|]
operator|<<
literal|8
expr_stmt|;
if|if
condition|(
operator|(
name|j
operator|+
name|offset
operator|)
operator|&
literal|0x4
condition|)
block|{
name|render_temp_buf
index|[
name|j
operator|*
literal|3
operator|+
literal|0
index|]
operator|=
name|render_blend_dark_check
index|[
operator|(
name|a
operator||
name|s
index|[
name|RED_PIX
index|]
operator|)
index|]
expr_stmt|;
name|render_temp_buf
index|[
name|j
operator|*
literal|3
operator|+
literal|1
index|]
operator|=
name|render_blend_dark_check
index|[
operator|(
name|a
operator||
name|s
index|[
name|GREEN_PIX
index|]
operator|)
index|]
expr_stmt|;
name|render_temp_buf
index|[
name|j
operator|*
literal|3
operator|+
literal|2
index|]
operator|=
name|render_blend_dark_check
index|[
operator|(
name|a
operator||
name|s
index|[
name|BLUE_PIX
index|]
operator|)
index|]
expr_stmt|;
block|}
else|else
block|{
name|render_temp_buf
index|[
name|j
operator|*
literal|3
operator|+
literal|0
index|]
operator|=
name|render_blend_light_check
index|[
operator|(
name|a
operator||
name|s
index|[
name|RED_PIX
index|]
operator|)
index|]
expr_stmt|;
name|render_temp_buf
index|[
name|j
operator|*
literal|3
operator|+
literal|1
index|]
operator|=
name|render_blend_light_check
index|[
operator|(
name|a
operator||
name|s
index|[
name|GREEN_PIX
index|]
operator|)
index|]
expr_stmt|;
name|render_temp_buf
index|[
name|j
operator|*
literal|3
operator|+
literal|2
index|]
operator|=
name|render_blend_light_check
index|[
operator|(
name|a
operator||
name|s
index|[
name|BLUE_PIX
index|]
operator|)
index|]
expr_stmt|;
block|}
block|}
else|else
block|{
name|render_temp_buf
index|[
name|j
operator|*
literal|3
operator|+
literal|0
index|]
operator|=
name|s
index|[
name|RED_PIX
index|]
expr_stmt|;
name|render_temp_buf
index|[
name|j
operator|*
literal|3
operator|+
literal|1
index|]
operator|=
name|s
index|[
name|GREEN_PIX
index|]
expr_stmt|;
name|render_temp_buf
index|[
name|j
operator|*
literal|3
operator|+
literal|2
index|]
operator|=
name|s
index|[
name|BLUE_PIX
index|]
expr_stmt|;
block|}
block|}
else|else
block|{
if|if
condition|(
name|has_alpha
condition|)
block|{
name|a
operator|=
name|s
index|[
name|alpha
index|]
operator|<<
literal|8
expr_stmt|;
if|if
condition|(
operator|(
name|j
operator|+
name|offset
operator|)
operator|&
literal|0x4
condition|)
block|{
if|if
condition|(
name|color_buf
condition|)
block|{
name|render_temp_buf
index|[
name|j
operator|*
literal|3
operator|+
literal|0
index|]
operator|=
name|render_blend_dark_check
index|[
operator|(
name|a
operator||
name|s
index|[
name|GRAY_PIX
index|]
operator|)
index|]
expr_stmt|;
name|render_temp_buf
index|[
name|j
operator|*
literal|3
operator|+
literal|1
index|]
operator|=
name|render_blend_dark_check
index|[
operator|(
name|a
operator||
name|s
index|[
name|GRAY_PIX
index|]
operator|)
index|]
expr_stmt|;
name|render_temp_buf
index|[
name|j
operator|*
literal|3
operator|+
literal|2
index|]
operator|=
name|render_blend_dark_check
index|[
operator|(
name|a
operator||
name|s
index|[
name|GRAY_PIX
index|]
operator|)
index|]
expr_stmt|;
block|}
else|else
block|{
name|render_temp_buf
index|[
name|j
index|]
operator|=
name|render_blend_dark_check
index|[
operator|(
name|a
operator||
name|s
index|[
name|GRAY_PIX
operator|+
name|channel
index|]
operator|)
index|]
expr_stmt|;
block|}
block|}
else|else
block|{
if|if
condition|(
name|color_buf
condition|)
block|{
name|render_temp_buf
index|[
name|j
operator|*
literal|3
operator|+
literal|0
index|]
operator|=
name|render_blend_light_check
index|[
operator|(
name|a
operator||
name|s
index|[
name|GRAY_PIX
index|]
operator|)
index|]
expr_stmt|;
name|render_temp_buf
index|[
name|j
operator|*
literal|3
operator|+
literal|1
index|]
operator|=
name|render_blend_light_check
index|[
operator|(
name|a
operator||
name|s
index|[
name|GRAY_PIX
index|]
operator|)
index|]
expr_stmt|;
name|render_temp_buf
index|[
name|j
operator|*
literal|3
operator|+
literal|2
index|]
operator|=
name|render_blend_light_check
index|[
operator|(
name|a
operator||
name|s
index|[
name|GRAY_PIX
index|]
operator|)
index|]
expr_stmt|;
block|}
else|else
block|{
name|render_temp_buf
index|[
name|j
index|]
operator|=
name|render_blend_light_check
index|[
operator|(
name|a
operator||
name|s
index|[
name|GRAY_PIX
operator|+
name|channel
index|]
operator|)
index|]
expr_stmt|;
block|}
block|}
block|}
else|else
block|{
if|if
condition|(
name|color_buf
condition|)
block|{
name|render_temp_buf
index|[
name|j
operator|*
literal|3
operator|+
literal|0
index|]
operator|=
name|s
index|[
name|GRAY_PIX
index|]
expr_stmt|;
name|render_temp_buf
index|[
name|j
operator|*
literal|3
operator|+
literal|1
index|]
operator|=
name|s
index|[
name|GRAY_PIX
index|]
expr_stmt|;
name|render_temp_buf
index|[
name|j
operator|*
literal|3
operator|+
literal|2
index|]
operator|=
name|s
index|[
name|GRAY_PIX
index|]
expr_stmt|;
block|}
else|else
block|{
name|render_temp_buf
index|[
name|j
index|]
operator|=
name|s
index|[
name|GRAY_PIX
operator|+
name|channel
index|]
expr_stmt|;
block|}
block|}
block|}
name|s
operator|+=
name|temp_buf
operator|->
name|bytes
expr_stmt|;
block|}
comment|/*  Handle the trailing transparency  */
for|for
control|(
name|j
operator|=
name|x2
init|;
name|j
operator|<
name|width
condition|;
name|j
operator|++
control|)
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|image_bytes
condition|;
name|b
operator|++
control|)
name|render_temp_buf
index|[
name|j
operator|*
name|image_bytes
operator|+
name|b
index|]
operator|=
name|cb
index|[
name|j
operator|*
literal|3
operator|+
name|b
index|]
expr_stmt|;
name|src
operator|+=
name|rowstride
expr_stmt|;
block|}
else|else
block|{
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|width
condition|;
name|j
operator|++
control|)
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|image_bytes
condition|;
name|b
operator|++
control|)
name|render_temp_buf
index|[
name|j
operator|*
name|image_bytes
operator|+
name|b
index|]
operator|=
name|cb
index|[
name|j
operator|*
literal|3
operator|+
name|b
index|]
expr_stmt|;
block|}
name|gtk_preview_draw_row
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|,
name|render_temp_buf
argument_list|,
literal|0
argument_list|,
name|i
argument_list|,
name|width
argument_list|)
expr_stmt|;
block|}
block|}
name|temp_buf_free
argument_list|(
name|temp_buf
argument_list|)
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|GTK_WIDGET
argument_list|(
name|preview
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

end_unit

