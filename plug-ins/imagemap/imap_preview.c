begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for the GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-2003 Maurits Rijk  lpeek.mrijk@consunet.nl  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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
file|"libgimp/gimp.h"
end_include

begin_include
include|#
directive|include
file|"imap_commands.h"
end_include

begin_include
include|#
directive|include
file|"imap_grid.h"
end_include

begin_include
include|#
directive|include
file|"imap_main.h"
end_include

begin_include
include|#
directive|include
file|"imap_popup.h"
end_include

begin_include
include|#
directive|include
file|"imap_preview.h"
end_include

begin_define
DECL|macro|PREVIEW_MASK
define|#
directive|define
name|PREVIEW_MASK
value|(GDK_EXPOSURE_MASK       | \ 		       GDK_POINTER_MOTION_MASK | \                        GDK_BUTTON_PRESS_MASK   | \ 		       GDK_BUTTON_RELEASE_MASK | \ 		       GDK_BUTTON_MOTION_MASK  | \ 		       GDK_KEY_PRESS_MASK      | \ 		       GDK_KEY_RELEASE_MASK    | \ 		       GDK_ENTER_NOTIFY_MASK   | \ 		       GDK_LEAVE_NOTIFY_MASK)
end_define

begin_define
DECL|macro|PREVIEW_SIZE
define|#
directive|define
name|PREVIEW_SIZE
value|400
end_define

begin_comment
comment|/*====================================================================== 		Preview Rendering Util routine =======================================================================*/
end_comment

begin_define
DECL|macro|CHECKWIDTH
define|#
directive|define
name|CHECKWIDTH
value|4
end_define

begin_define
DECL|macro|LIGHTCHECK
define|#
directive|define
name|LIGHTCHECK
value|192
end_define

begin_define
DECL|macro|DARKCHECK
define|#
directive|define
name|DARKCHECK
value|128
end_define

begin_ifndef
ifndef|#
directive|ifndef
name|OPAQUE
end_ifndef

begin_define
DECL|macro|OPAQUE
define|#
directive|define
name|OPAQUE
value|255
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_function
specifier|static
name|Preview_t
modifier|*
DECL|function|preview_user_data (GtkWidget * preview)
name|preview_user_data
parameter_list|(
name|GtkWidget
modifier|*
name|preview
parameter_list|)
block|{
return|return
operator|(
name|Preview_t
operator|*
operator|)
name|gtk_object_get_user_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|preview
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
name|gint
DECL|function|preview_get_width (GtkWidget * preview)
name|preview_get_width
parameter_list|(
name|GtkWidget
modifier|*
name|preview
parameter_list|)
block|{
return|return
name|preview_user_data
argument_list|(
name|preview
argument_list|)
operator|->
name|width
return|;
block|}
end_function

begin_function
name|gint
DECL|function|preview_get_height (GtkWidget * preview)
name|preview_get_height
parameter_list|(
name|GtkWidget
modifier|*
name|preview
parameter_list|)
block|{
return|return
name|preview_user_data
argument_list|(
name|preview
argument_list|)
operator|->
name|height
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|render_gray_image (GtkWidget * preview,GimpPixelRgn * srcrgn)
name|render_gray_image
parameter_list|(
name|GtkWidget
modifier|*
name|preview
parameter_list|,
name|GimpPixelRgn
modifier|*
name|srcrgn
parameter_list|)
block|{
name|guchar
modifier|*
name|src_row
decl_stmt|,
modifier|*
name|dest_row
decl_stmt|,
modifier|*
name|src
decl_stmt|,
modifier|*
name|dest
decl_stmt|;
name|gint
name|row
decl_stmt|,
name|col
decl_stmt|;
name|gint
name|bpp
decl_stmt|,
name|dwidth
decl_stmt|,
name|dheight
decl_stmt|,
name|pwidth
decl_stmt|,
name|pheight
decl_stmt|;
name|gint
modifier|*
name|src_col
decl_stmt|;
name|dwidth
operator|=
name|srcrgn
operator|->
name|w
expr_stmt|;
name|dheight
operator|=
name|srcrgn
operator|->
name|h
expr_stmt|;
if|if
condition|(
name|GTK_PREVIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|buffer
condition|)
block|{
name|pwidth
operator|=
name|GTK_PREVIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|buffer_width
expr_stmt|;
name|pheight
operator|=
name|GTK_PREVIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|buffer_height
expr_stmt|;
block|}
else|else
block|{
name|pwidth
operator|=
name|preview
operator|->
name|requisition
operator|.
name|width
expr_stmt|;
name|pheight
operator|=
name|preview
operator|->
name|requisition
operator|.
name|height
expr_stmt|;
block|}
name|bpp
operator|=
name|srcrgn
operator|->
name|bpp
expr_stmt|;
name|src_row
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|dwidth
operator|*
name|bpp
argument_list|)
expr_stmt|;
name|dest_row
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|pwidth
operator|*
literal|3
argument_list|)
expr_stmt|;
name|src_col
operator|=
name|g_new
argument_list|(
name|gint
argument_list|,
name|pwidth
argument_list|)
expr_stmt|;
for|for
control|(
name|col
operator|=
literal|0
init|;
name|col
operator|<
name|pwidth
condition|;
name|col
operator|++
control|)
name|src_col
index|[
name|col
index|]
operator|=
operator|(
name|col
operator|*
name|dwidth
operator|/
name|pwidth
operator|)
operator|*
name|bpp
expr_stmt|;
for|for
control|(
name|row
operator|=
literal|0
init|;
name|row
operator|<
name|pheight
condition|;
name|row
operator|++
control|)
block|{
name|gimp_pixel_rgn_get_row
argument_list|(
name|srcrgn
argument_list|,
name|src_row
argument_list|,
literal|0
argument_list|,
name|row
operator|*
name|dheight
operator|/
name|pheight
argument_list|,
name|dwidth
argument_list|)
expr_stmt|;
name|dest
operator|=
name|dest_row
expr_stmt|;
name|src
operator|=
name|src_row
expr_stmt|;
for|for
control|(
name|col
operator|=
literal|0
init|;
name|col
operator|<
name|pwidth
condition|;
name|col
operator|++
control|)
block|{
name|src
operator|=
operator|&
name|src_row
index|[
name|src_col
index|[
name|col
index|]
index|]
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
operator|*
name|src
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
operator|*
name|src
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
operator|*
name|src
expr_stmt|;
block|}
name|gtk_preview_draw_row
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|,
name|dest_row
argument_list|,
literal|0
argument_list|,
name|row
argument_list|,
name|pwidth
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|src_col
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|src_row
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|dest_row
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|render_indexed_image (GtkWidget * preview,GimpPixelRgn * srcrgn)
name|render_indexed_image
parameter_list|(
name|GtkWidget
modifier|*
name|preview
parameter_list|,
name|GimpPixelRgn
modifier|*
name|srcrgn
parameter_list|)
block|{
name|guchar
modifier|*
name|src_row
decl_stmt|,
modifier|*
name|dest_row
decl_stmt|,
modifier|*
name|src
decl_stmt|,
modifier|*
name|dest
decl_stmt|;
name|gint
name|row
decl_stmt|,
name|col
decl_stmt|;
name|gint
name|dwidth
decl_stmt|,
name|dheight
decl_stmt|,
name|pwidth
decl_stmt|,
name|pheight
decl_stmt|;
name|gint
modifier|*
name|src_col
decl_stmt|;
name|gint
name|bpp
decl_stmt|,
name|alpha
decl_stmt|,
name|has_alpha
decl_stmt|;
name|guchar
modifier|*
name|cmap
decl_stmt|,
modifier|*
name|colour
decl_stmt|;
name|gint
name|ncols
decl_stmt|;
name|gboolean
name|gray
init|=
name|get_map_info
argument_list|()
operator|->
name|show_gray
decl_stmt|;
name|dwidth
operator|=
name|srcrgn
operator|->
name|w
expr_stmt|;
name|dheight
operator|=
name|srcrgn
operator|->
name|h
expr_stmt|;
if|if
condition|(
name|GTK_PREVIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|buffer
condition|)
block|{
name|pwidth
operator|=
name|GTK_PREVIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|buffer_width
expr_stmt|;
name|pheight
operator|=
name|GTK_PREVIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|buffer_height
expr_stmt|;
block|}
else|else
block|{
name|pwidth
operator|=
name|preview
operator|->
name|requisition
operator|.
name|width
expr_stmt|;
name|pheight
operator|=
name|preview
operator|->
name|requisition
operator|.
name|height
expr_stmt|;
block|}
name|bpp
operator|=
name|srcrgn
operator|->
name|bpp
expr_stmt|;
name|alpha
operator|=
name|bpp
expr_stmt|;
name|has_alpha
operator|=
name|gimp_drawable_has_alpha
argument_list|(
name|srcrgn
operator|->
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
if|if
condition|(
name|has_alpha
condition|)
name|alpha
operator|--
expr_stmt|;
name|cmap
operator|=
name|gimp_image_get_cmap
argument_list|(
name|gimp_drawable_image_id
argument_list|(
name|srcrgn
operator|->
name|drawable
operator|->
name|drawable_id
argument_list|)
argument_list|,
operator|&
name|ncols
argument_list|)
expr_stmt|;
name|src_row
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|dwidth
operator|*
name|bpp
argument_list|)
expr_stmt|;
name|dest_row
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|pwidth
operator|*
literal|3
argument_list|)
expr_stmt|;
name|src_col
operator|=
name|g_new
argument_list|(
name|gint
argument_list|,
name|pwidth
argument_list|)
expr_stmt|;
for|for
control|(
name|col
operator|=
literal|0
init|;
name|col
operator|<
name|pwidth
condition|;
name|col
operator|++
control|)
name|src_col
index|[
name|col
index|]
operator|=
operator|(
name|col
operator|*
name|dwidth
operator|/
name|pwidth
operator|)
operator|*
name|bpp
expr_stmt|;
for|for
control|(
name|row
operator|=
literal|0
init|;
name|row
operator|<
name|pheight
condition|;
name|row
operator|++
control|)
block|{
name|gimp_pixel_rgn_get_row
argument_list|(
name|srcrgn
argument_list|,
name|src_row
argument_list|,
literal|0
argument_list|,
name|row
operator|*
name|dheight
operator|/
name|pheight
argument_list|,
name|dwidth
argument_list|)
expr_stmt|;
name|dest
operator|=
name|dest_row
expr_stmt|;
for|for
control|(
name|col
operator|=
literal|0
init|;
name|col
operator|<
name|pwidth
condition|;
name|col
operator|++
control|)
block|{
name|src
operator|=
operator|&
name|src_row
index|[
name|src_col
index|[
name|col
index|]
index|]
expr_stmt|;
name|colour
operator|=
name|cmap
operator|+
literal|3
operator|*
call|(
name|int
call|)
argument_list|(
operator|*
name|src
argument_list|)
expr_stmt|;
if|if
condition|(
name|gray
condition|)
block|{
name|guchar
name|avg
init|=
operator|(
literal|299
operator|*
name|colour
index|[
literal|0
index|]
operator|+
literal|587
operator|*
name|colour
index|[
literal|1
index|]
operator|+
literal|114
operator|*
name|colour
index|[
literal|2
index|]
operator|)
operator|/
literal|1000
decl_stmt|;
operator|*
name|dest
operator|++
operator|=
name|avg
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
name|avg
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
name|avg
expr_stmt|;
block|}
else|else
block|{
operator|*
name|dest
operator|++
operator|=
name|colour
index|[
literal|0
index|]
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
name|colour
index|[
literal|1
index|]
expr_stmt|;
operator|*
name|dest
operator|++
operator|=
name|colour
index|[
literal|2
index|]
expr_stmt|;
block|}
block|}
name|gtk_preview_draw_row
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|,
name|dest_row
argument_list|,
literal|0
argument_list|,
name|row
argument_list|,
name|pwidth
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|src_col
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|src_row
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|dest_row
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|render_rgb_image (GtkWidget * preview,GimpPixelRgn * srcrgn)
name|render_rgb_image
parameter_list|(
name|GtkWidget
modifier|*
name|preview
parameter_list|,
name|GimpPixelRgn
modifier|*
name|srcrgn
parameter_list|)
block|{
name|guchar
modifier|*
name|src_row
decl_stmt|,
modifier|*
name|dest_row
decl_stmt|,
modifier|*
name|src
decl_stmt|,
modifier|*
name|dest
decl_stmt|;
name|gint
name|row
decl_stmt|,
name|col
decl_stmt|;
name|gint
name|dwidth
decl_stmt|,
name|dheight
decl_stmt|,
name|pwidth
decl_stmt|,
name|pheight
decl_stmt|;
name|gint
modifier|*
name|src_col
decl_stmt|;
name|gint
name|bpp
decl_stmt|,
name|alpha
decl_stmt|,
name|has_alpha
decl_stmt|,
name|b
decl_stmt|;
name|guchar
name|check
decl_stmt|;
name|gboolean
name|gray
init|=
name|get_map_info
argument_list|()
operator|->
name|show_gray
decl_stmt|;
name|dwidth
operator|=
name|srcrgn
operator|->
name|w
expr_stmt|;
name|dheight
operator|=
name|srcrgn
operator|->
name|h
expr_stmt|;
if|if
condition|(
name|GTK_PREVIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|buffer
condition|)
block|{
name|pwidth
operator|=
name|GTK_PREVIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|buffer_width
expr_stmt|;
name|pheight
operator|=
name|GTK_PREVIEW
argument_list|(
name|preview
argument_list|)
operator|->
name|buffer_height
expr_stmt|;
block|}
else|else
block|{
name|pwidth
operator|=
name|preview
operator|->
name|requisition
operator|.
name|width
expr_stmt|;
name|pheight
operator|=
name|preview
operator|->
name|requisition
operator|.
name|height
expr_stmt|;
block|}
name|bpp
operator|=
name|srcrgn
operator|->
name|bpp
expr_stmt|;
name|alpha
operator|=
name|bpp
expr_stmt|;
name|has_alpha
operator|=
name|gimp_drawable_has_alpha
argument_list|(
name|srcrgn
operator|->
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
if|if
condition|(
name|has_alpha
condition|)
name|alpha
operator|--
expr_stmt|;
name|src_row
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|dwidth
operator|*
name|bpp
argument_list|)
expr_stmt|;
name|dest_row
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|pwidth
operator|*
name|bpp
argument_list|)
expr_stmt|;
name|src_col
operator|=
name|g_new
argument_list|(
name|gint
argument_list|,
name|pwidth
argument_list|)
expr_stmt|;
for|for
control|(
name|col
operator|=
literal|0
init|;
name|col
operator|<
name|pwidth
condition|;
name|col
operator|++
control|)
name|src_col
index|[
name|col
index|]
operator|=
operator|(
name|col
operator|*
name|dwidth
operator|/
name|pwidth
operator|)
operator|*
name|bpp
expr_stmt|;
for|for
control|(
name|row
operator|=
literal|0
init|;
name|row
operator|<
name|pheight
condition|;
name|row
operator|++
control|)
block|{
name|gimp_pixel_rgn_get_row
argument_list|(
name|srcrgn
argument_list|,
name|src_row
argument_list|,
literal|0
argument_list|,
name|row
operator|*
name|dheight
operator|/
name|pheight
argument_list|,
name|dwidth
argument_list|)
expr_stmt|;
name|dest
operator|=
name|dest_row
expr_stmt|;
for|for
control|(
name|col
operator|=
literal|0
init|;
name|col
operator|<
name|pwidth
condition|;
name|col
operator|++
control|)
block|{
name|src
operator|=
operator|&
name|src_row
index|[
name|src_col
index|[
name|col
index|]
index|]
expr_stmt|;
if|if
condition|(
operator|!
name|has_alpha
operator|||
name|src
index|[
name|alpha
index|]
operator|==
name|OPAQUE
condition|)
block|{
comment|/* no alpha channel or opaque -- simple way */
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|alpha
condition|;
name|b
operator|++
control|)
name|dest
index|[
name|b
index|]
operator|=
name|src
index|[
name|b
index|]
expr_stmt|;
block|}
else|else
block|{
comment|/* more or less transparent */
if|if
condition|(
operator|(
name|col
operator|%
operator|(
name|CHECKWIDTH
operator|*
literal|2
operator|)
operator|<
name|CHECKWIDTH
operator|)
operator|^
operator|(
name|row
operator|%
operator|(
name|CHECKWIDTH
operator|*
literal|2
operator|)
operator|<
name|CHECKWIDTH
operator|)
condition|)
name|check
operator|=
name|LIGHTCHECK
expr_stmt|;
else|else
name|check
operator|=
name|DARKCHECK
expr_stmt|;
if|if
condition|(
name|src
index|[
name|alpha
index|]
operator|==
literal|0
condition|)
block|{
comment|/* full transparent -- check */
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|alpha
condition|;
name|b
operator|++
control|)
name|dest
index|[
name|b
index|]
operator|=
name|check
expr_stmt|;
block|}
else|else
block|{
comment|/* middlemost transparent -- mix check and src */
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|alpha
condition|;
name|b
operator|++
control|)
name|dest
index|[
name|b
index|]
operator|=
operator|(
name|src
index|[
name|b
index|]
operator|*
name|src
index|[
name|alpha
index|]
operator|+
name|check
operator|*
operator|(
name|OPAQUE
operator|-
name|src
index|[
name|alpha
index|]
operator|)
operator|)
operator|/
name|OPAQUE
expr_stmt|;
block|}
block|}
if|if
condition|(
name|gray
condition|)
block|{
name|guchar
name|avg
decl_stmt|;
name|avg
operator|=
operator|(
literal|299
operator|*
name|dest
index|[
literal|0
index|]
operator|+
literal|587
operator|*
name|dest
index|[
literal|1
index|]
operator|+
literal|114
operator|*
name|dest
index|[
literal|2
index|]
operator|)
operator|/
literal|1000
expr_stmt|;
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|alpha
condition|;
name|b
operator|++
control|)
name|dest
index|[
name|b
index|]
operator|=
name|avg
expr_stmt|;
block|}
name|dest
operator|+=
name|alpha
expr_stmt|;
block|}
name|gtk_preview_draw_row
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|,
name|dest_row
argument_list|,
literal|0
argument_list|,
name|row
argument_list|,
name|pwidth
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|src_col
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|src_row
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|dest_row
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|render_preview (GtkWidget * preview,GimpPixelRgn * srcrgn)
name|render_preview
parameter_list|(
name|GtkWidget
modifier|*
name|preview
parameter_list|,
name|GimpPixelRgn
modifier|*
name|srcrgn
parameter_list|)
block|{
switch|switch
condition|(
name|gimp_drawable_type
argument_list|(
name|srcrgn
operator|->
name|drawable
operator|->
name|drawable_id
argument_list|)
condition|)
block|{
case|case
name|GIMP_RGB_IMAGE
case|:
case|case
name|GIMP_RGBA_IMAGE
case|:
name|render_rgb_image
argument_list|(
name|preview
argument_list|,
name|srcrgn
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_GRAY_IMAGE
case|:
case|case
name|GIMP_GRAYA_IMAGE
case|:
name|render_gray_image
argument_list|(
name|preview
argument_list|,
name|srcrgn
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_INDEXED_IMAGE
case|:
case|case
name|GIMP_INDEXEDA_IMAGE
case|:
name|render_indexed_image
argument_list|(
name|preview
argument_list|,
name|srcrgn
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|arrow_cb (GtkWidget * widget,GdkEventButton * event,gpointer data)
name|arrow_cb
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
if|if
condition|(
name|event
operator|->
name|button
operator|==
literal|1
condition|)
name|do_main_popup_menu
argument_list|(
name|event
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|preview_expose (GtkWidget * widget,GdkEventExpose * event)
name|preview_expose
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventExpose
modifier|*
name|event
parameter_list|)
block|{
name|draw_grid
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|draw_shapes
argument_list|(
name|widget
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|void
DECL|function|add_preview_motion_event (Preview_t * preview,GCallback func)
name|add_preview_motion_event
parameter_list|(
name|Preview_t
modifier|*
name|preview
parameter_list|,
name|GCallback
name|func
parameter_list|)
block|{
name|g_signal_connect
argument_list|(
name|preview
operator|->
name|preview
argument_list|,
literal|"motion_notify_event"
argument_list|,
name|func
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|add_enter_notify_event (Preview_t * preview,GCallback func)
name|add_enter_notify_event
parameter_list|(
name|Preview_t
modifier|*
name|preview
parameter_list|,
name|GCallback
name|func
parameter_list|)
block|{
name|g_signal_connect
argument_list|(
name|preview
operator|->
name|preview
argument_list|,
literal|"enter_notify_event"
argument_list|,
name|func
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|add_leave_notify_event (Preview_t * preview,GCallback func)
name|add_leave_notify_event
parameter_list|(
name|Preview_t
modifier|*
name|preview
parameter_list|,
name|GCallback
name|func
parameter_list|)
block|{
name|g_signal_connect
argument_list|(
name|preview
operator|->
name|preview
argument_list|,
literal|"leave_notify_event"
argument_list|,
name|func
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|add_preview_button_press_event (Preview_t * preview,GCallback func)
name|add_preview_button_press_event
parameter_list|(
name|Preview_t
modifier|*
name|preview
parameter_list|,
name|GCallback
name|func
parameter_list|)
block|{
name|g_signal_connect
argument_list|(
name|preview
operator|->
name|preview
argument_list|,
literal|"button_press_event"
argument_list|,
name|func
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|preview_redraw (Preview_t * preview)
name|preview_redraw
parameter_list|(
name|Preview_t
modifier|*
name|preview
parameter_list|)
block|{
name|gtk_widget_queue_draw
argument_list|(
name|preview
operator|->
name|preview
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|preview_zoom (Preview_t * preview,gint zoom_factor)
name|preview_zoom
parameter_list|(
name|Preview_t
modifier|*
name|preview
parameter_list|,
name|gint
name|zoom_factor
parameter_list|)
block|{
name|gint
name|pwidth
init|=
name|preview
operator|->
name|width
operator|*
name|zoom_factor
decl_stmt|;
name|gint
name|pheight
init|=
name|preview
operator|->
name|height
operator|*
name|zoom_factor
decl_stmt|;
name|gtk_preview_size
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|preview
operator|->
name|preview
argument_list|)
argument_list|,
name|pwidth
argument_list|,
name|pheight
argument_list|)
expr_stmt|;
name|gtk_widget_queue_resize
argument_list|(
name|preview
operator|->
name|window
argument_list|)
expr_stmt|;
name|render_preview
argument_list|(
name|preview
operator|->
name|preview
argument_list|,
operator|&
name|preview
operator|->
name|src_rgn
argument_list|)
expr_stmt|;
name|preview_redraw
argument_list|(
name|preview
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GdkCursorType
DECL|function|preview_set_cursor (Preview_t * preview,GdkCursorType cursor_type)
name|preview_set_cursor
parameter_list|(
name|Preview_t
modifier|*
name|preview
parameter_list|,
name|GdkCursorType
name|cursor_type
parameter_list|)
block|{
name|GdkCursorType
name|prev_cursor
init|=
name|preview
operator|->
name|cursor
decl_stmt|;
name|GdkCursor
modifier|*
name|cursor
init|=
name|gdk_cursor_new
argument_list|(
name|cursor_type
argument_list|)
decl_stmt|;
name|gdk_window_set_cursor
argument_list|(
name|preview
operator|->
name|window
operator|->
name|window
argument_list|,
name|cursor
argument_list|)
expr_stmt|;
name|gdk_cursor_unref
argument_list|(
name|cursor
argument_list|)
expr_stmt|;
name|gdk_flush
argument_list|()
expr_stmt|;
name|preview
operator|->
name|cursor
operator|=
name|cursor_type
expr_stmt|;
return|return
name|prev_cursor
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|target_table
specifier|static
name|GtkTargetEntry
name|target_table
index|[]
init|=
block|{
block|{
literal|"STRING"
block|,
literal|0
block|,
literal|1
block|}
block|,
block|{
literal|"text/plain"
block|,
literal|0
block|,
literal|2
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|handle_drop (GtkWidget * widget,GdkDragContext * context,gint x,gint y,GtkSelectionData * data,guint info,guint time)
name|handle_drop
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GtkSelectionData
modifier|*
name|data
parameter_list|,
name|guint
name|info
parameter_list|,
name|guint
name|time
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|FALSE
decl_stmt|;
if|if
condition|(
name|data
operator|->
name|length
operator|>=
literal|0
operator|&&
name|data
operator|->
name|format
operator|==
literal|8
condition|)
block|{
name|ObjectList_t
modifier|*
name|list
init|=
name|get_shapes
argument_list|()
decl_stmt|;
name|Object_t
modifier|*
name|obj
decl_stmt|;
name|x
operator|=
name|get_real_coord
argument_list|(
name|x
argument_list|)
expr_stmt|;
name|y
operator|=
name|get_real_coord
argument_list|(
name|y
argument_list|)
expr_stmt|;
name|obj
operator|=
name|object_list_find
argument_list|(
name|list
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
if|if
condition|(
name|obj
operator|&&
operator|!
name|obj
operator|->
name|locked
condition|)
block|{
name|command_list_add
argument_list|(
name|edit_object_command_new
argument_list|(
name|obj
argument_list|)
argument_list|)
expr_stmt|;
name|object_set_url
argument_list|(
name|obj
argument_list|,
name|data
operator|->
name|data
argument_list|)
expr_stmt|;
name|object_emit_update_signal
argument_list|(
name|obj
argument_list|)
expr_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
name|gtk_drag_finish
argument_list|(
name|context
argument_list|,
name|success
argument_list|,
name|FALSE
argument_list|,
name|time
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|Preview_t
modifier|*
DECL|function|make_preview (GimpDrawable * drawable)
name|make_preview
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|Preview_t
modifier|*
name|data
init|=
name|g_new
argument_list|(
name|Preview_t
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
name|GtkWidget
modifier|*
name|window
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|,
modifier|*
name|arrow
decl_stmt|;
name|GtkWidget
modifier|*
name|ruler
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|data
operator|->
name|drawable
operator|=
name|drawable
expr_stmt|;
name|data
operator|->
name|preview
operator|=
name|preview
operator|=
name|gtk_preview_new
argument_list|(
name|GTK_PREVIEW_COLOR
argument_list|)
expr_stmt|;
name|gtk_object_set_user_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|preview
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gtk_widget_set_events
argument_list|(
name|GTK_WIDGET
argument_list|(
name|preview
argument_list|)
argument_list|,
name|PREVIEW_MASK
argument_list|)
expr_stmt|;
name|g_signal_connect_after
argument_list|(
name|preview
argument_list|,
literal|"expose_event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|preview_expose
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
comment|/* Handle drop of links in preview widget */
name|gtk_drag_dest_set
argument_list|(
name|preview
argument_list|,
name|GTK_DEST_DEFAULT_ALL
argument_list|,
name|target_table
argument_list|,
literal|2
argument_list|,
name|GDK_ACTION_COPY
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|preview
argument_list|,
literal|"drag_data_received"
argument_list|,
name|G_CALLBACK
argument_list|(
name|handle_drop
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|data
operator|->
name|width
operator|=
name|gimp_drawable_width
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
name|data
operator|->
name|height
operator|=
name|gimp_drawable_height
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
name|gtk_preview_size
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|,
name|data
operator|->
name|width
argument_list|,
name|data
operator|->
name|height
argument_list|)
expr_stmt|;
name|data
operator|->
name|window
operator|=
name|window
operator|=
name|gtk_scrolled_window_new
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|width
operator|=
operator|(
name|data
operator|->
name|width
operator|>
literal|600
operator|)
condition|?
literal|600
else|:
name|data
operator|->
name|width
expr_stmt|;
name|height
operator|=
operator|(
name|data
operator|->
name|height
operator|>
literal|400
operator|)
condition|?
literal|400
else|:
name|data
operator|->
name|height
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|window
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|gtk_scrolled_window_set_policy
argument_list|(
name|GTK_SCROLLED_WINDOW
argument_list|(
name|window
argument_list|)
argument_list|,
name|GTK_POLICY_AUTOMATIC
argument_list|,
name|GTK_POLICY_AUTOMATIC
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|window
argument_list|)
expr_stmt|;
name|data
operator|->
name|frame
operator|=
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_scrolled_window_add_with_viewport
argument_list|(
name|GTK_SCROLLED_WINDOW
argument_list|(
name|window
argument_list|)
argument_list|,
name|frame
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
comment|/* The main table */
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|3
argument_list|,
literal|3
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|preview
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
name|GTK_FILL
argument_list|,
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|table
argument_list|)
expr_stmt|;
comment|/* Create button with arrow */
name|button
operator|=
name|gtk_button_new
argument_list|()
expr_stmt|;
name|GTK_WIDGET_UNSET_FLAGS
argument_list|(
name|button
argument_list|,
name|GTK_CAN_FOCUS
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|button
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|GTK_FILL
argument_list|,
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_set_events
argument_list|(
name|button
argument_list|,
name|GDK_BUTTON_PRESS_MASK
operator||
name|GDK_BUTTON_RELEASE_MASK
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|button
argument_list|,
literal|"button_press_event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|arrow_cb
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|arrow
operator|=
name|gtk_arrow_new
argument_list|(
name|GTK_ARROW_RIGHT
argument_list|,
name|GTK_SHADOW_OUT
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|button
argument_list|)
argument_list|,
name|arrow
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|arrow
argument_list|)
expr_stmt|;
comment|/* Create horizontal ruler */
name|data
operator|->
name|hruler
operator|=
name|ruler
operator|=
name|gtk_hruler_new
argument_list|()
expr_stmt|;
name|gtk_ruler_set_range
argument_list|(
name|GTK_RULER
argument_list|(
name|ruler
argument_list|)
argument_list|,
literal|0
argument_list|,
name|data
operator|->
name|width
argument_list|,
literal|0
argument_list|,
name|PREVIEW_SIZE
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|preview
argument_list|,
literal|"motion_notify_event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|GTK_WIDGET_GET_CLASS
argument_list|(
name|ruler
argument_list|)
operator|->
name|motion_notify_event
argument_list|)
argument_list|,
name|ruler
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|ruler
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|GTK_FILL
argument_list|,
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|ruler
argument_list|)
expr_stmt|;
comment|/* Create vertical ruler */
name|data
operator|->
name|vruler
operator|=
name|ruler
operator|=
name|gtk_vruler_new
argument_list|()
expr_stmt|;
name|gtk_ruler_set_range
argument_list|(
name|GTK_RULER
argument_list|(
name|ruler
argument_list|)
argument_list|,
literal|0
argument_list|,
name|data
operator|->
name|height
argument_list|,
literal|0
argument_list|,
name|PREVIEW_SIZE
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|preview
argument_list|,
literal|"motion_notify_event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|GTK_WIDGET_GET_CLASS
argument_list|(
name|ruler
argument_list|)
operator|->
name|motion_notify_event
argument_list|)
argument_list|,
name|ruler
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|ruler
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
name|GTK_FILL
argument_list|,
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|ruler
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|data
operator|->
name|src_rgn
argument_list|,
name|drawable
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|data
operator|->
name|width
argument_list|,
name|data
operator|->
name|height
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|render_preview
argument_list|(
name|preview
argument_list|,
operator|&
name|data
operator|->
name|src_rgn
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|preview
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
return|return
name|data
return|;
block|}
end_function

end_unit

