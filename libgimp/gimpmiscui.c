begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpmiscui.c  * Contains all kinds of miscellaneous routines factored out from different  * plug-ins. They stay here until their API has crystalized a bit and we can  * put them into the file where they belong (Maurits Rijk   *<lpeek.mrijk@consunet.nl> if you want to blame someone for this mess)  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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

begin_ifdef
ifdef|#
directive|ifdef
name|__GNUC__
end_ifdef

begin_warning
warning|#
directive|warning
warning|GTK_DISABLE_DEPRECATED
end_warning

begin_endif
endif|#
directive|endif
end_endif

begin_undef
undef|#
directive|undef
name|GTK_DISABLE_DEPRECATED
end_undef

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimpmiscui.h"
end_include

begin_include
include|#
directive|include
file|"libgimp-intl.h"
end_include

begin_define
DECL|macro|PREVIEW_SIZE
define|#
directive|define
name|PREVIEW_SIZE
value|128
end_define

begin_define
DECL|macro|PREVIEW_BPP
define|#
directive|define
name|PREVIEW_BPP
value|3
end_define

begin_function
specifier|static
name|void
DECL|function|gimp_fixme_preview_put_in_frame (GimpFixMePreview * preview)
name|gimp_fixme_preview_put_in_frame
parameter_list|(
name|GimpFixMePreview
modifier|*
name|preview
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|frame
decl_stmt|,
modifier|*
name|abox
decl_stmt|;
name|preview
operator|->
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|_
argument_list|(
literal|"Preview"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|preview
operator|->
name|frame
argument_list|)
expr_stmt|;
name|abox
operator|=
name|gtk_alignment_new
argument_list|(
literal|0.5
argument_list|,
literal|0.5
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|abox
argument_list|)
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|preview
operator|->
name|frame
argument_list|)
argument_list|,
name|abox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|abox
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_frame_set_shadow_type
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|GTK_SHADOW_IN
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|abox
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
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|preview
operator|->
name|widget
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpFixMePreview
modifier|*
DECL|function|gimp_fixme_preview_new (GimpDrawable * drawable,gboolean has_frame)
name|gimp_fixme_preview_new
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gboolean
name|has_frame
parameter_list|)
block|{
name|GimpFixMePreview
modifier|*
name|preview
init|=
name|g_new0
argument_list|(
name|GimpFixMePreview
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|preview
operator|->
name|widget
operator|=
name|gtk_preview_new
argument_list|(
name|GTK_PREVIEW_COLOR
argument_list|)
expr_stmt|;
name|preview
operator|->
name|is_gray
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|drawable
condition|)
name|gimp_fixme_preview_fill_with_thumb
argument_list|(
name|preview
argument_list|,
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
if|if
condition|(
name|has_frame
condition|)
name|gimp_fixme_preview_put_in_frame
argument_list|(
name|preview
argument_list|)
expr_stmt|;
return|return
name|preview
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_fixme_preview_free (GimpFixMePreview * preview)
name|gimp_fixme_preview_free
parameter_list|(
name|GimpFixMePreview
modifier|*
name|preview
parameter_list|)
block|{
name|g_free
argument_list|(
name|preview
operator|->
name|cmap
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|preview
operator|->
name|even
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|preview
operator|->
name|odd
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|preview
operator|->
name|cache
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|preview
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpFixMePreview
modifier|*
DECL|function|gimp_fixme_preview_new2 (GimpImageType drawable_type,gboolean has_frame)
name|gimp_fixme_preview_new2
parameter_list|(
name|GimpImageType
name|drawable_type
parameter_list|,
name|gboolean
name|has_frame
parameter_list|)
block|{
name|GimpFixMePreview
modifier|*
name|preview
decl_stmt|;
name|guchar
modifier|*
name|buf
init|=
name|NULL
decl_stmt|;
name|gint
name|y
decl_stmt|;
name|preview
operator|=
name|g_new0
argument_list|(
name|GimpFixMePreview
argument_list|,
literal|1
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|drawable_type
condition|)
block|{
case|case
name|GIMP_GRAY_IMAGE
case|:
case|case
name|GIMP_GRAYA_IMAGE
case|:
name|preview
operator|->
name|widget
operator|=
name|gtk_preview_new
argument_list|(
name|GTK_PREVIEW_GRAYSCALE
argument_list|)
expr_stmt|;
name|buf
operator|=
name|g_malloc0
argument_list|(
name|PREVIEW_SIZE
argument_list|)
expr_stmt|;
name|preview
operator|->
name|is_gray
operator|=
name|TRUE
expr_stmt|;
break|break;
case|case
name|GIMP_RGB_IMAGE
case|:
case|case
name|GIMP_RGBA_IMAGE
case|:
name|preview
operator|->
name|widget
operator|=
name|gtk_preview_new
argument_list|(
name|GTK_PREVIEW_COLOR
argument_list|)
expr_stmt|;
name|buf
operator|=
name|g_malloc0
argument_list|(
name|PREVIEW_SIZE
operator|*
literal|3
argument_list|)
expr_stmt|;
name|preview
operator|->
name|is_gray
operator|=
name|FALSE
expr_stmt|;
break|break;
default|default:
name|g_assert_not_reached
argument_list|()
expr_stmt|;
break|break;
block|}
name|gtk_preview_size
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|preview
operator|->
name|widget
argument_list|)
argument_list|,
name|PREVIEW_SIZE
argument_list|,
name|PREVIEW_SIZE
argument_list|)
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|PREVIEW_SIZE
condition|;
name|y
operator|++
control|)
name|gtk_preview_draw_row
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|preview
operator|->
name|widget
argument_list|)
argument_list|,
name|buf
argument_list|,
literal|0
argument_list|,
name|y
argument_list|,
name|PREVIEW_SIZE
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|buf
argument_list|)
expr_stmt|;
if|if
condition|(
name|has_frame
condition|)
name|gimp_fixme_preview_put_in_frame
argument_list|(
name|preview
argument_list|)
expr_stmt|;
name|preview
operator|->
name|buffer
operator|=
name|GTK_PREVIEW
argument_list|(
name|preview
operator|->
name|widget
argument_list|)
operator|->
name|buffer
expr_stmt|;
name|preview
operator|->
name|width
operator|=
name|GTK_PREVIEW
argument_list|(
name|preview
operator|->
name|widget
argument_list|)
operator|->
name|buffer_width
expr_stmt|;
name|preview
operator|->
name|height
operator|=
name|GTK_PREVIEW
argument_list|(
name|preview
operator|->
name|widget
argument_list|)
operator|->
name|buffer_height
expr_stmt|;
name|preview
operator|->
name|rowstride
operator|=
name|preview
operator|->
name|width
operator|*
operator|(
operator|(
name|preview
operator|->
name|is_gray
operator|)
condition|?
literal|1
else|:
literal|3
operator|)
expr_stmt|;
return|return
name|preview
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_fixme_preview_put_pixel (GimpFixMePreview * preview,gint x,gint y,const guchar * pixel)
name|gimp_fixme_preview_put_pixel
parameter_list|(
name|GimpFixMePreview
modifier|*
name|preview
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
name|pixel
parameter_list|)
block|{
name|guchar
modifier|*
name|dest
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|x
operator|>=
literal|0
operator|&&
name|x
operator|<
name|PREVIEW_SIZE
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|y
operator|>=
literal|0
operator|&&
name|y
operator|<
name|PREVIEW_SIZE
argument_list|)
expr_stmt|;
name|dest
operator|=
name|preview
operator|->
name|buffer
operator|+
name|y
operator|*
name|preview
operator|->
name|rowstride
expr_stmt|;
if|if
condition|(
name|preview
operator|->
name|is_gray
condition|)
block|{
name|dest
operator|+=
name|x
expr_stmt|;
name|dest
index|[
literal|0
index|]
operator|=
name|pixel
index|[
literal|0
index|]
expr_stmt|;
block|}
else|else
block|{
name|dest
operator|+=
name|x
operator|*
literal|3
expr_stmt|;
name|dest
index|[
literal|0
index|]
operator|=
name|pixel
index|[
literal|0
index|]
expr_stmt|;
name|dest
index|[
literal|1
index|]
operator|=
name|pixel
index|[
literal|1
index|]
expr_stmt|;
name|dest
index|[
literal|2
index|]
operator|=
name|pixel
index|[
literal|2
index|]
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_fixme_preview_get_pixel (GimpFixMePreview * preview,gint x,gint y,guchar * pixel)
name|gimp_fixme_preview_get_pixel
parameter_list|(
name|GimpFixMePreview
modifier|*
name|preview
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|guchar
modifier|*
name|pixel
parameter_list|)
block|{
specifier|const
name|guchar
modifier|*
name|src
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|x
operator|>=
literal|0
operator|&&
name|x
operator|<
name|PREVIEW_SIZE
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|y
operator|>=
literal|0
operator|&&
name|y
operator|<
name|PREVIEW_SIZE
argument_list|)
expr_stmt|;
name|src
operator|=
name|preview
operator|->
name|buffer
operator|+
name|y
operator|*
name|preview
operator|->
name|rowstride
expr_stmt|;
if|if
condition|(
name|preview
operator|->
name|is_gray
condition|)
block|{
name|src
operator|+=
name|x
expr_stmt|;
name|pixel
index|[
literal|0
index|]
operator|=
name|src
index|[
literal|0
index|]
expr_stmt|;
block|}
else|else
block|{
name|src
operator|+=
name|x
operator|*
literal|3
expr_stmt|;
name|pixel
index|[
literal|0
index|]
operator|=
name|src
index|[
literal|0
index|]
expr_stmt|;
name|pixel
index|[
literal|1
index|]
operator|=
name|src
index|[
literal|1
index|]
expr_stmt|;
name|pixel
index|[
literal|2
index|]
operator|=
name|src
index|[
literal|2
index|]
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_fixme_preview_do_row (GimpFixMePreview * preview,gint row,gint width,const guchar * src)
name|gimp_fixme_preview_do_row
parameter_list|(
name|GimpFixMePreview
modifier|*
name|preview
parameter_list|,
name|gint
name|row
parameter_list|,
name|gint
name|width
parameter_list|,
specifier|const
name|guchar
modifier|*
name|src
parameter_list|)
block|{
name|gint
name|x
decl_stmt|;
name|guchar
modifier|*
name|p0
init|=
name|preview
operator|->
name|even
decl_stmt|;
name|guchar
modifier|*
name|p1
init|=
name|preview
operator|->
name|odd
decl_stmt|;
name|gint
name|bpp
init|=
name|preview
operator|->
name|bpp
decl_stmt|;
name|gint
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|,
name|a
decl_stmt|;
name|gint
name|c0
decl_stmt|,
name|c1
decl_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|width
condition|;
name|x
operator|++
control|)
block|{
switch|switch
condition|(
name|bpp
condition|)
block|{
case|case
literal|4
case|:
name|r
operator|=
name|src
index|[
name|x
operator|*
literal|4
operator|+
literal|0
index|]
expr_stmt|;
name|g
operator|=
name|src
index|[
name|x
operator|*
literal|4
operator|+
literal|1
index|]
expr_stmt|;
name|b
operator|=
name|src
index|[
name|x
operator|*
literal|4
operator|+
literal|2
index|]
expr_stmt|;
name|a
operator|=
name|src
index|[
name|x
operator|*
literal|4
operator|+
literal|3
index|]
expr_stmt|;
break|break;
case|case
literal|3
case|:
name|r
operator|=
name|src
index|[
name|x
operator|*
literal|3
operator|+
literal|0
index|]
expr_stmt|;
name|g
operator|=
name|src
index|[
name|x
operator|*
literal|3
operator|+
literal|1
index|]
expr_stmt|;
name|b
operator|=
name|src
index|[
name|x
operator|*
literal|3
operator|+
literal|2
index|]
expr_stmt|;
name|a
operator|=
literal|255
expr_stmt|;
break|break;
default|default:
if|if
condition|(
name|preview
operator|->
name|cmap
condition|)
block|{
name|gint
name|index
init|=
name|MIN
argument_list|(
name|src
index|[
name|x
operator|*
name|bpp
index|]
argument_list|,
name|preview
operator|->
name|ncolors
operator|-
literal|1
argument_list|)
decl_stmt|;
name|r
operator|=
name|preview
operator|->
name|cmap
index|[
name|index
operator|*
literal|3
operator|+
literal|0
index|]
expr_stmt|;
name|g
operator|=
name|preview
operator|->
name|cmap
index|[
name|index
operator|*
literal|3
operator|+
literal|1
index|]
expr_stmt|;
name|b
operator|=
name|preview
operator|->
name|cmap
index|[
name|index
operator|*
literal|3
operator|+
literal|2
index|]
expr_stmt|;
block|}
else|else
block|{
name|g
operator|=
name|b
operator|=
name|r
operator|=
name|src
index|[
name|x
operator|*
name|bpp
operator|+
literal|0
index|]
expr_stmt|;
block|}
if|if
condition|(
name|bpp
operator|==
literal|2
condition|)
name|a
operator|=
name|src
index|[
name|x
operator|*
literal|2
operator|+
literal|1
index|]
expr_stmt|;
else|else
name|a
operator|=
literal|255
expr_stmt|;
break|break;
block|}
if|if
condition|(
operator|(
name|x
operator|/
name|GIMP_CHECK_SIZE_SM
operator|)
operator|&
literal|1
condition|)
block|{
name|c0
operator|=
name|GIMP_CHECK_LIGHT
operator|*
literal|255
expr_stmt|;
name|c1
operator|=
name|GIMP_CHECK_DARK
operator|*
literal|255
expr_stmt|;
block|}
else|else
block|{
name|c0
operator|=
name|GIMP_CHECK_DARK
operator|*
literal|255
expr_stmt|;
name|c1
operator|=
name|GIMP_CHECK_LIGHT
operator|*
literal|255
expr_stmt|;
block|}
operator|*
name|p0
operator|++
operator|=
name|c0
operator|+
operator|(
name|r
operator|-
name|c0
operator|)
operator|*
name|a
operator|/
literal|255
expr_stmt|;
operator|*
name|p0
operator|++
operator|=
name|c0
operator|+
operator|(
name|g
operator|-
name|c0
operator|)
operator|*
name|a
operator|/
literal|255
expr_stmt|;
operator|*
name|p0
operator|++
operator|=
name|c0
operator|+
operator|(
name|b
operator|-
name|c0
operator|)
operator|*
name|a
operator|/
literal|255
expr_stmt|;
operator|*
name|p1
operator|++
operator|=
name|c1
operator|+
operator|(
name|r
operator|-
name|c1
operator|)
operator|*
name|a
operator|/
literal|255
expr_stmt|;
operator|*
name|p1
operator|++
operator|=
name|c1
operator|+
operator|(
name|g
operator|-
name|c1
operator|)
operator|*
name|a
operator|/
literal|255
expr_stmt|;
operator|*
name|p1
operator|++
operator|=
name|c1
operator|+
operator|(
name|b
operator|-
name|c1
operator|)
operator|*
name|a
operator|/
literal|255
expr_stmt|;
block|}
if|if
condition|(
operator|(
name|row
operator|/
name|GIMP_CHECK_SIZE_SM
operator|)
operator|&
literal|1
condition|)
block|{
name|gtk_preview_draw_row
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|preview
operator|->
name|widget
argument_list|)
argument_list|,
name|preview
operator|->
name|odd
argument_list|,
literal|0
argument_list|,
name|row
argument_list|,
name|width
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_preview_draw_row
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|preview
operator|->
name|widget
argument_list|)
argument_list|,
name|preview
operator|->
name|even
argument_list|,
literal|0
argument_list|,
name|row
argument_list|,
name|width
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_fixme_preview_update (GimpFixMePreview * preview,GimpFixeMePreviewFunc func,gpointer data)
name|gimp_fixme_preview_update
parameter_list|(
name|GimpFixMePreview
modifier|*
name|preview
parameter_list|,
name|GimpFixeMePreviewFunc
name|func
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|guchar
modifier|*
name|buffer
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gint
name|bpp
decl_stmt|;
name|bpp
operator|=
name|preview
operator|->
name|bpp
expr_stmt|;
name|buffer
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|preview
operator|->
name|rowstride
argument_list|)
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|preview
operator|->
name|height
condition|;
name|y
operator|++
control|)
block|{
specifier|const
name|guchar
modifier|*
name|src
init|=
name|preview
operator|->
name|cache
operator|+
name|y
operator|*
name|preview
operator|->
name|rowstride
decl_stmt|;
name|guchar
modifier|*
name|dest
init|=
name|buffer
decl_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|preview
operator|->
name|width
condition|;
name|x
operator|++
control|)
block|{
name|func
argument_list|(
name|src
argument_list|,
name|dest
argument_list|,
name|bpp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|src
operator|+=
name|bpp
expr_stmt|;
name|dest
operator|+=
name|bpp
expr_stmt|;
block|}
name|gimp_fixme_preview_do_row
argument_list|(
name|preview
argument_list|,
name|y
argument_list|,
name|preview
operator|->
name|width
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_queue_draw
argument_list|(
name|preview
operator|->
name|widget
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_fixme_preview_fill_with_thumb (GimpFixMePreview * preview,gint32 drawable_ID)
name|gimp_fixme_preview_fill_with_thumb
parameter_list|(
name|GimpFixMePreview
modifier|*
name|preview
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|)
block|{
specifier|const
name|guchar
modifier|*
name|src
decl_stmt|;
name|gint
name|bpp
decl_stmt|;
name|gint
name|y
decl_stmt|;
name|gint
name|width
init|=
name|PREVIEW_SIZE
decl_stmt|;
name|gint
name|height
init|=
name|PREVIEW_SIZE
decl_stmt|;
name|preview
operator|->
name|cache
operator|=
name|gimp_drawable_get_thumbnail_data
argument_list|(
name|drawable_ID
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|,
operator|&
name|bpp
argument_list|)
expr_stmt|;
if|if
condition|(
name|width
operator|<
literal|1
operator|||
name|height
operator|<
literal|1
condition|)
return|return;
name|preview
operator|->
name|rowstride
operator|=
name|width
operator|*
name|bpp
expr_stmt|;
name|preview
operator|->
name|bpp
operator|=
name|bpp
expr_stmt|;
if|if
condition|(
name|gimp_drawable_is_indexed
argument_list|(
name|drawable_ID
argument_list|)
condition|)
block|{
name|gint32
name|image_ID
init|=
name|gimp_drawable_image
argument_list|(
name|drawable_ID
argument_list|)
decl_stmt|;
name|preview
operator|->
name|cmap
operator|=
name|gimp_image_get_cmap
argument_list|(
name|image_ID
argument_list|,
operator|&
name|preview
operator|->
name|ncolors
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|preview
operator|->
name|cmap
operator|=
name|NULL
expr_stmt|;
block|}
name|gtk_preview_size
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|preview
operator|->
name|widget
argument_list|)
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|preview
operator|->
name|scale_x
operator|=
operator|(
name|gdouble
operator|)
name|width
operator|/
operator|(
name|gdouble
operator|)
name|gimp_drawable_width
argument_list|(
name|drawable_ID
argument_list|)
expr_stmt|;
name|preview
operator|->
name|scale_y
operator|=
operator|(
name|gdouble
operator|)
name|height
operator|/
operator|(
name|gdouble
operator|)
name|gimp_drawable_height
argument_list|(
name|drawable_ID
argument_list|)
expr_stmt|;
name|src
operator|=
name|preview
operator|->
name|cache
expr_stmt|;
name|preview
operator|->
name|even
operator|=
name|g_malloc
argument_list|(
name|width
operator|*
literal|3
argument_list|)
expr_stmt|;
name|preview
operator|->
name|odd
operator|=
name|g_malloc
argument_list|(
name|width
operator|*
literal|3
argument_list|)
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|height
condition|;
name|y
operator|++
control|)
block|{
name|gimp_fixme_preview_do_row
argument_list|(
name|preview
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|src
argument_list|)
expr_stmt|;
name|src
operator|+=
name|width
operator|*
name|bpp
expr_stmt|;
block|}
name|preview
operator|->
name|buffer
operator|=
name|GTK_PREVIEW
argument_list|(
name|preview
operator|->
name|widget
argument_list|)
operator|->
name|buffer
expr_stmt|;
name|preview
operator|->
name|width
operator|=
name|GTK_PREVIEW
argument_list|(
name|preview
operator|->
name|widget
argument_list|)
operator|->
name|buffer_width
expr_stmt|;
name|preview
operator|->
name|height
operator|=
name|GTK_PREVIEW
argument_list|(
name|preview
operator|->
name|widget
argument_list|)
operator|->
name|buffer_height
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_fixme_preview_fill (GimpFixMePreview * preview,GimpDrawable * drawable)
name|gimp_fixme_preview_fill
parameter_list|(
name|GimpFixMePreview
modifier|*
name|preview
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GimpPixelRgn
name|srcPR
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|x2
decl_stmt|,
name|y1
decl_stmt|,
name|y2
decl_stmt|;
name|gint
name|bpp
decl_stmt|;
name|gint
name|y
decl_stmt|;
name|guchar
modifier|*
name|src
decl_stmt|;
name|gimp_drawable_mask_bounds
argument_list|(
name|drawable
operator|->
name|drawable_id
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
expr_stmt|;
if|if
condition|(
name|x2
operator|-
name|x1
operator|>
name|PREVIEW_SIZE
condition|)
name|x2
operator|=
name|x1
operator|+
name|PREVIEW_SIZE
expr_stmt|;
if|if
condition|(
name|y2
operator|-
name|y1
operator|>
name|PREVIEW_SIZE
condition|)
name|y2
operator|=
name|y1
operator|+
name|PREVIEW_SIZE
expr_stmt|;
name|width
operator|=
name|x2
operator|-
name|x1
expr_stmt|;
name|height
operator|=
name|y2
operator|-
name|y1
expr_stmt|;
name|bpp
operator|=
name|gimp_drawable_bpp
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_drawable_is_indexed
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
condition|)
block|{
name|gint32
name|image_ID
init|=
name|gimp_drawable_image
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
decl_stmt|;
name|preview
operator|->
name|cmap
operator|=
name|gimp_image_get_cmap
argument_list|(
name|image_ID
argument_list|,
operator|&
name|preview
operator|->
name|ncolors
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|preview
operator|->
name|cmap
operator|=
name|NULL
expr_stmt|;
block|}
name|gtk_preview_size
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|preview
operator|->
name|widget
argument_list|)
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|drawable
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|preview
operator|->
name|even
operator|=
name|g_malloc
argument_list|(
name|width
operator|*
literal|3
argument_list|)
expr_stmt|;
name|preview
operator|->
name|odd
operator|=
name|g_malloc
argument_list|(
name|width
operator|*
literal|3
argument_list|)
expr_stmt|;
name|src
operator|=
name|g_malloc
argument_list|(
name|width
operator|*
name|bpp
argument_list|)
expr_stmt|;
name|preview
operator|->
name|cache
operator|=
name|g_malloc
argument_list|(
name|width
operator|*
name|bpp
operator|*
name|height
argument_list|)
expr_stmt|;
name|preview
operator|->
name|rowstride
operator|=
name|width
operator|*
name|bpp
expr_stmt|;
name|preview
operator|->
name|bpp
operator|=
name|bpp
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|height
condition|;
name|y
operator|++
control|)
block|{
name|gimp_pixel_rgn_get_row
argument_list|(
operator|&
name|srcPR
argument_list|,
name|src
argument_list|,
name|x1
argument_list|,
name|y
operator|+
name|y1
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|preview
operator|->
name|cache
operator|+
operator|(
name|y
operator|*
name|width
operator|*
name|bpp
operator|)
argument_list|,
name|src
argument_list|,
name|width
operator|*
name|bpp
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|height
condition|;
name|y
operator|++
control|)
block|{
name|gimp_fixme_preview_do_row
argument_list|(
name|preview
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|preview
operator|->
name|cache
operator|+
operator|(
name|y
operator|*
name|width
operator|*
name|bpp
operator|)
argument_list|)
expr_stmt|;
block|}
name|preview
operator|->
name|buffer
operator|=
name|GTK_PREVIEW
argument_list|(
name|preview
operator|->
name|widget
argument_list|)
operator|->
name|buffer
expr_stmt|;
name|preview
operator|->
name|width
operator|=
name|GTK_PREVIEW
argument_list|(
name|preview
operator|->
name|widget
argument_list|)
operator|->
name|buffer_width
expr_stmt|;
name|preview
operator|->
name|height
operator|=
name|GTK_PREVIEW
argument_list|(
name|preview
operator|->
name|widget
argument_list|)
operator|->
name|buffer_height
expr_stmt|;
name|g_free
argument_list|(
name|src
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_fixme_preview_fill_scaled (GimpFixMePreview * preview,GimpDrawable * drawable)
name|gimp_fixme_preview_fill_scaled
parameter_list|(
name|GimpFixMePreview
modifier|*
name|preview
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|gint
name|bpp
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
name|sel_width
decl_stmt|,
name|sel_height
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gdouble
name|px
decl_stmt|,
name|py
decl_stmt|;
name|gdouble
name|dx
decl_stmt|,
name|dy
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|guchar
modifier|*
name|dest
decl_stmt|;
name|GimpPixelFetcher
modifier|*
name|pft
decl_stmt|;
name|gimp_drawable_mask_bounds
argument_list|(
name|drawable
operator|->
name|drawable_id
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
expr_stmt|;
name|sel_width
operator|=
name|x2
operator|-
name|x1
expr_stmt|;
name|sel_height
operator|=
name|y2
operator|-
name|y1
expr_stmt|;
comment|/* Calculate preview size */
if|if
condition|(
name|sel_width
operator|>
name|sel_height
condition|)
block|{
name|width
operator|=
name|MIN
argument_list|(
name|sel_width
argument_list|,
name|PREVIEW_SIZE
argument_list|)
expr_stmt|;
name|height
operator|=
name|sel_height
operator|*
name|width
operator|/
name|sel_width
expr_stmt|;
block|}
else|else
block|{
name|height
operator|=
name|MIN
argument_list|(
name|sel_height
argument_list|,
name|PREVIEW_SIZE
argument_list|)
expr_stmt|;
name|width
operator|=
name|sel_width
operator|*
name|height
operator|/
name|sel_height
expr_stmt|;
block|}
if|if
condition|(
name|width
operator|<
literal|2
condition|)
name|width
operator|=
literal|2
expr_stmt|;
if|if
condition|(
name|height
operator|<
literal|2
condition|)
name|height
operator|=
literal|2
expr_stmt|;
name|bpp
operator|=
name|gimp_drawable_bpp
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_drawable_is_indexed
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
condition|)
block|{
name|gint32
name|image_ID
init|=
name|gimp_drawable_image
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
decl_stmt|;
name|preview
operator|->
name|cmap
operator|=
name|gimp_image_get_cmap
argument_list|(
name|image_ID
argument_list|,
operator|&
name|preview
operator|->
name|ncolors
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|preview
operator|->
name|cmap
operator|=
name|NULL
expr_stmt|;
block|}
name|gtk_preview_size
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|preview
operator|->
name|widget
argument_list|)
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|preview
operator|->
name|even
operator|=
name|g_malloc
argument_list|(
name|width
operator|*
literal|3
argument_list|)
expr_stmt|;
name|preview
operator|->
name|odd
operator|=
name|g_malloc
argument_list|(
name|width
operator|*
literal|3
argument_list|)
expr_stmt|;
name|preview
operator|->
name|cache
operator|=
name|g_malloc
argument_list|(
name|width
operator|*
name|bpp
operator|*
name|height
argument_list|)
expr_stmt|;
name|preview
operator|->
name|rowstride
operator|=
name|width
operator|*
name|bpp
expr_stmt|;
name|preview
operator|->
name|bpp
operator|=
name|bpp
expr_stmt|;
name|dx
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|x2
operator|-
name|x1
operator|-
literal|1
argument_list|)
operator|/
operator|(
name|width
operator|-
literal|1
operator|)
expr_stmt|;
name|dy
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|y2
operator|-
name|y1
operator|-
literal|1
argument_list|)
operator|/
operator|(
name|height
operator|-
literal|1
operator|)
expr_stmt|;
name|py
operator|=
name|y1
expr_stmt|;
name|pft
operator|=
name|gimp_pixel_fetcher_new
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|height
condition|;
name|y
operator|++
control|)
block|{
name|dest
operator|=
name|preview
operator|->
name|cache
operator|+
name|y
operator|*
name|preview
operator|->
name|rowstride
expr_stmt|;
name|px
operator|=
name|x1
expr_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|width
condition|;
name|x
operator|++
control|)
block|{
name|gimp_pixel_fetcher_get_pixel
argument_list|(
name|pft
argument_list|,
operator|(
name|gint
operator|)
name|px
argument_list|,
operator|(
name|gint
operator|)
name|py
argument_list|,
name|dest
argument_list|)
expr_stmt|;
name|dest
operator|+=
name|bpp
expr_stmt|;
name|px
operator|+=
name|dx
expr_stmt|;
block|}
name|gimp_fixme_preview_do_row
argument_list|(
name|preview
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|dest
argument_list|)
expr_stmt|;
name|py
operator|+=
name|dy
expr_stmt|;
block|}
name|gimp_pixel_fetcher_destroy
argument_list|(
name|pft
argument_list|)
expr_stmt|;
name|preview
operator|->
name|buffer
operator|=
name|GTK_PREVIEW
argument_list|(
name|preview
operator|->
name|widget
argument_list|)
operator|->
name|buffer
expr_stmt|;
name|preview
operator|->
name|width
operator|=
name|GTK_PREVIEW
argument_list|(
name|preview
operator|->
name|widget
argument_list|)
operator|->
name|buffer_width
expr_stmt|;
name|preview
operator|->
name|height
operator|=
name|GTK_PREVIEW
argument_list|(
name|preview
operator|->
name|widget
argument_list|)
operator|->
name|buffer_height
expr_stmt|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|gimp_plug_in_get_path (const gchar * path_name,const gchar * dir_name)
name|gimp_plug_in_get_path
parameter_list|(
specifier|const
name|gchar
modifier|*
name|path_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|dir_name
parameter_list|)
block|{
name|gchar
modifier|*
name|path
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|path_name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|dir_name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|path
operator|=
name|gimp_gimprc_query
argument_list|(
name|path_name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|path
condition|)
block|{
name|gchar
modifier|*
name|gimprc
init|=
name|gimp_personal_rc_file
argument_list|(
literal|"gimprc"
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|full_path
decl_stmt|;
name|gchar
modifier|*
name|esc_path
decl_stmt|;
name|full_path
operator|=
name|g_strconcat
argument_list|(
literal|"${gimp_dir}"
argument_list|,
name|G_DIR_SEPARATOR_S
argument_list|,
name|dir_name
argument_list|,
name|G_SEARCHPATH_SEPARATOR_S
argument_list|,
literal|"${gimp_data_dir}"
argument_list|,
name|G_DIR_SEPARATOR_S
argument_list|,
name|dir_name
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|esc_path
operator|=
name|g_strescape
argument_list|(
name|full_path
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|full_path
argument_list|)
expr_stmt|;
name|g_message
argument_list|(
name|_
argument_list|(
literal|"No %s in gimprc:\n"
literal|"You need to add an entry like\n"
literal|"(%s \"%s\")\n"
literal|"to your %s file."
argument_list|)
argument_list|,
name|path_name
argument_list|,
name|path_name
argument_list|,
name|esc_path
argument_list|,
name|gimprc
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|gimprc
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|esc_path
argument_list|)
expr_stmt|;
block|}
return|return
name|path
return|;
block|}
end_function

end_unit

