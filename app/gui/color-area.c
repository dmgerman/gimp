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
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_comment
comment|/* memcpy */
end_comment

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_STRING_H
end_ifdef

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
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
file|"widgets/gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"color-area.h"
end_include

begin_include
include|#
directive|include
file|"color-notebook.h"
end_include

begin_include
include|#
directive|include
file|"app_procs.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|DISPLAY_FILTERS
end_ifdef

begin_include
include|#
directive|include
file|"gdisplay_color.h"
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* DISPLAY_FILTERS */
end_comment

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon27dae79b0103
block|{
DECL|enumerator|FORE_AREA
name|FORE_AREA
block|,
DECL|enumerator|BACK_AREA
name|BACK_AREA
block|,
DECL|enumerator|SWAP_AREA
name|SWAP_AREA
block|,
DECL|enumerator|DEF_AREA
name|DEF_AREA
block|,
DECL|enumerator|INVALID_AREA
name|INVALID_AREA
DECL|typedef|ColorAreaTarget
block|}
name|ColorAreaTarget
typedef|;
end_typedef

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|color_area_drop_color
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
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|color_area_drag_color
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
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
name|color_area_color_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Global variables  */
end_comment

begin_decl_stmt
DECL|variable|active_color
name|gint
name|active_color
init|=
name|FOREGROUND
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|color_area_gdisp
name|GDisplay
modifier|*
name|color_area_gdisp
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  Static variables  */
end_comment

begin_decl_stmt
DECL|variable|color_area_gc
specifier|static
name|GdkGC
modifier|*
name|color_area_gc
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|mask_gc
specifier|static
name|GdkGC
modifier|*
name|mask_gc
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|color_area
specifier|static
name|GtkWidget
modifier|*
name|color_area
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|color_area_pixmap
specifier|static
name|GdkPixmap
modifier|*
name|color_area_pixmap
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|color_area_mask
specifier|static
name|GdkBitmap
modifier|*
name|color_area_mask
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|default_pixmap
specifier|static
name|GdkPixmap
modifier|*
name|default_pixmap
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|default_mask
specifier|static
name|GdkBitmap
modifier|*
name|default_mask
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|swap_pixmap
specifier|static
name|GdkPixmap
modifier|*
name|swap_pixmap
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|swap_mask
specifier|static
name|GdkBitmap
modifier|*
name|swap_mask
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|color_notebook
specifier|static
name|ColorNotebook
modifier|*
name|color_notebook
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|color_notebook_active
specifier|static
name|gboolean
name|color_notebook_active
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|edit_color
specifier|static
name|gint
name|edit_color
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|revert_fg
specifier|static
name|GimpRGB
name|revert_fg
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|revert_bg
specifier|static
name|GimpRGB
name|revert_bg
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  dnd stuff  */
end_comment

begin_decl_stmt
DECL|variable|color_area_target_table
specifier|static
name|GtkTargetEntry
name|color_area_target_table
index|[]
init|=
block|{
name|GIMP_TARGET_COLOR
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  Local functions  */
end_comment

begin_function
specifier|static
name|ColorAreaTarget
DECL|function|color_area_target (gint x,gint y)
name|color_area_target
parameter_list|(
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
block|{
name|gint
name|rect_w
decl_stmt|,
name|rect_h
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gdk_drawable_get_size
argument_list|(
name|color_area_pixmap
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
name|rect_w
operator|=
name|width
operator|*
literal|0.65
expr_stmt|;
name|rect_h
operator|=
name|height
operator|*
literal|0.65
expr_stmt|;
comment|/*  foreground active  */
if|if
condition|(
name|x
operator|>
literal|0
operator|&&
name|x
operator|<
name|rect_w
operator|&&
name|y
operator|>
literal|0
operator|&&
name|y
operator|<
name|rect_h
condition|)
return|return
name|FORE_AREA
return|;
elseif|else
if|if
condition|(
name|x
operator|>
operator|(
name|width
operator|-
name|rect_w
operator|)
operator|&&
name|x
operator|<
name|width
operator|&&
name|y
operator|>
operator|(
name|height
operator|-
name|rect_h
operator|)
operator|&&
name|y
operator|<
name|height
condition|)
return|return
name|BACK_AREA
return|;
elseif|else
if|if
condition|(
name|x
operator|>
literal|0
operator|&&
name|x
operator|<
operator|(
name|width
operator|-
name|rect_w
operator|)
operator|&&
name|y
operator|>
name|rect_h
operator|&&
name|y
operator|<
name|height
condition|)
return|return
name|DEF_AREA
return|;
elseif|else
if|if
condition|(
name|x
operator|>
name|rect_w
operator|&&
name|x
operator|<
name|width
operator|&&
name|y
operator|>
literal|0
operator|&&
name|y
operator|<
operator|(
name|height
operator|-
name|rect_h
operator|)
condition|)
return|return
name|SWAP_AREA
return|;
else|else
return|return
operator|-
literal|1
return|;
block|}
end_function

begin_function
name|void
DECL|function|color_area_draw_rect (GdkDrawable * drawable,GdkGC * gc,gint x,gint y,gint width,gint height,guchar r,guchar g,guchar b)
name|color_area_draw_rect
parameter_list|(
name|GdkDrawable
modifier|*
name|drawable
parameter_list|,
name|GdkGC
modifier|*
name|gc
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|guchar
name|r
parameter_list|,
name|guchar
name|g
parameter_list|,
name|guchar
name|b
parameter_list|)
block|{
specifier|static
name|guchar
modifier|*
name|color_area_rgb_buf
init|=
name|NULL
decl_stmt|;
specifier|static
name|gint
name|color_area_rgb_buf_size
decl_stmt|;
specifier|static
name|gint
name|rowstride
decl_stmt|;
name|gint
name|xx
decl_stmt|,
name|yy
decl_stmt|;
name|guchar
modifier|*
name|bp
decl_stmt|;
ifdef|#
directive|ifdef
name|DISPLAY_FILTERS
name|GList
modifier|*
name|list
decl_stmt|;
endif|#
directive|endif
comment|/* DISPLAY_FILTERS */
name|rowstride
operator|=
literal|3
operator|*
operator|(
operator|(
name|width
operator|+
literal|3
operator|)
operator|&
operator|-
literal|4
operator|)
expr_stmt|;
if|if
condition|(
name|color_area_rgb_buf
operator|==
name|NULL
operator|||
name|color_area_rgb_buf_size
operator|<
name|height
operator|*
name|rowstride
condition|)
block|{
if|if
condition|(
name|color_area_rgb_buf
condition|)
name|g_free
argument_list|(
name|color_area_rgb_buf
argument_list|)
expr_stmt|;
name|color_area_rgb_buf
operator|=
name|g_malloc
argument_list|(
name|color_area_rgb_buf_size
operator|=
name|rowstride
operator|*
name|height
argument_list|)
expr_stmt|;
block|}
name|bp
operator|=
name|color_area_rgb_buf
expr_stmt|;
for|for
control|(
name|xx
operator|=
literal|0
init|;
name|xx
operator|<
name|width
condition|;
name|xx
operator|++
control|)
block|{
operator|*
name|bp
operator|++
operator|=
name|r
expr_stmt|;
operator|*
name|bp
operator|++
operator|=
name|g
expr_stmt|;
operator|*
name|bp
operator|++
operator|=
name|b
expr_stmt|;
block|}
name|bp
operator|=
name|color_area_rgb_buf
expr_stmt|;
ifdef|#
directive|ifdef
name|DISPLAY_FILTERS
for|for
control|(
name|list
operator|=
name|color_area_gdisp
operator|->
name|cd_list
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
name|ColorDisplayNode
modifier|*
name|node
init|=
operator|(
name|ColorDisplayNode
operator|*
operator|)
name|list
operator|->
name|data
decl_stmt|;
name|node
operator|->
name|cd_convert
argument_list|(
name|node
operator|->
name|cd_ID
argument_list|,
name|bp
argument_list|,
name|width
argument_list|,
literal|1
argument_list|,
literal|3
argument_list|,
name|rowstride
argument_list|)
expr_stmt|;
block|}
endif|#
directive|endif
comment|/* DISPLAY_FILTERS */
for|for
control|(
name|yy
operator|=
literal|1
init|;
name|yy
operator|<
name|height
condition|;
name|yy
operator|++
control|)
block|{
name|bp
operator|+=
name|rowstride
expr_stmt|;
name|memcpy
argument_list|(
name|bp
argument_list|,
name|color_area_rgb_buf
argument_list|,
name|rowstride
argument_list|)
expr_stmt|;
block|}
name|gdk_draw_rgb_image
argument_list|(
name|drawable
argument_list|,
name|gc
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|GDK_RGB_DITHER_MAX
argument_list|,
name|color_area_rgb_buf
argument_list|,
name|rowstride
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|color_area_draw (void)
name|color_area_draw
parameter_list|(
name|void
parameter_list|)
block|{
name|gint
name|rect_w
decl_stmt|,
name|rect_h
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|def_width
decl_stmt|,
name|def_height
decl_stmt|;
name|gint
name|swap_width
decl_stmt|,
name|swap_height
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|guchar
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|;
name|GdkColor
name|mask_pattern
decl_stmt|;
comment|/* Check we haven't gotten initial expose yet,    * no point in drawing anything    */
if|if
condition|(
operator|!
name|color_area_pixmap
operator|||
operator|!
name|color_area_gc
condition|)
return|return;
name|gdk_drawable_get_size
argument_list|(
name|color_area_pixmap
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
name|rect_w
operator|=
name|width
operator|*
literal|0.65
expr_stmt|;
name|rect_h
operator|=
name|height
operator|*
literal|0.65
expr_stmt|;
comment|/*  initialize the mask to transparent  */
name|mask_pattern
operator|.
name|pixel
operator|=
literal|0
expr_stmt|;
name|gdk_gc_set_foreground
argument_list|(
name|mask_gc
argument_list|,
operator|&
name|mask_pattern
argument_list|)
expr_stmt|;
name|gdk_draw_rectangle
argument_list|(
name|color_area_mask
argument_list|,
name|mask_gc
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
operator|-
literal|1
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
comment|/*  set the mask's gc to opaque  */
name|mask_pattern
operator|.
name|pixel
operator|=
literal|1
expr_stmt|;
name|gdk_gc_set_foreground
argument_list|(
name|mask_gc
argument_list|,
operator|&
name|mask_pattern
argument_list|)
expr_stmt|;
comment|/*  draw the background area  */
name|gimp_context_get_background
argument_list|(
name|gimp_get_user_context
argument_list|(
name|the_gimp
argument_list|)
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|gimp_rgb_get_uchar
argument_list|(
operator|&
name|color
argument_list|,
operator|&
name|r
argument_list|,
operator|&
name|g
argument_list|,
operator|&
name|b
argument_list|)
expr_stmt|;
name|color_area_draw_rect
argument_list|(
name|color_area_pixmap
argument_list|,
name|color_area_gc
argument_list|,
operator|(
name|width
operator|-
name|rect_w
operator|)
argument_list|,
operator|(
name|height
operator|-
name|rect_h
operator|)
argument_list|,
name|rect_w
argument_list|,
name|rect_h
argument_list|,
name|r
argument_list|,
name|g
argument_list|,
name|b
argument_list|)
expr_stmt|;
name|gdk_draw_rectangle
argument_list|(
name|color_area_mask
argument_list|,
name|mask_gc
argument_list|,
name|TRUE
argument_list|,
operator|(
name|width
operator|-
name|rect_w
operator|)
argument_list|,
operator|(
name|height
operator|-
name|rect_h
operator|)
argument_list|,
name|rect_w
argument_list|,
name|rect_h
argument_list|)
expr_stmt|;
if|if
condition|(
name|active_color
operator|==
name|FOREGROUND
condition|)
name|gtk_draw_shadow
argument_list|(
name|color_area
operator|->
name|style
argument_list|,
name|color_area_pixmap
argument_list|,
name|GTK_STATE_NORMAL
argument_list|,
name|GTK_SHADOW_OUT
argument_list|,
operator|(
name|width
operator|-
name|rect_w
operator|)
argument_list|,
operator|(
name|height
operator|-
name|rect_h
operator|)
argument_list|,
name|rect_w
argument_list|,
name|rect_h
argument_list|)
expr_stmt|;
else|else
name|gtk_draw_shadow
argument_list|(
name|color_area
operator|->
name|style
argument_list|,
name|color_area_pixmap
argument_list|,
name|GTK_STATE_NORMAL
argument_list|,
name|GTK_SHADOW_IN
argument_list|,
operator|(
name|width
operator|-
name|rect_w
operator|)
argument_list|,
operator|(
name|height
operator|-
name|rect_h
operator|)
argument_list|,
name|rect_w
argument_list|,
name|rect_h
argument_list|)
expr_stmt|;
comment|/*  draw the foreground area  */
name|gimp_context_get_foreground
argument_list|(
name|gimp_get_user_context
argument_list|(
name|the_gimp
argument_list|)
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|gimp_rgb_get_uchar
argument_list|(
operator|&
name|color
argument_list|,
operator|&
name|r
argument_list|,
operator|&
name|g
argument_list|,
operator|&
name|b
argument_list|)
expr_stmt|;
name|color_area_draw_rect
argument_list|(
name|color_area_pixmap
argument_list|,
name|color_area_gc
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|rect_w
argument_list|,
name|rect_h
argument_list|,
name|r
argument_list|,
name|g
argument_list|,
name|b
argument_list|)
expr_stmt|;
name|gdk_draw_rectangle
argument_list|(
name|color_area_mask
argument_list|,
name|mask_gc
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|rect_w
argument_list|,
name|rect_h
argument_list|)
expr_stmt|;
if|if
condition|(
name|active_color
operator|==
name|FOREGROUND
condition|)
name|gtk_draw_shadow
argument_list|(
name|color_area
operator|->
name|style
argument_list|,
name|color_area_pixmap
argument_list|,
name|GTK_STATE_NORMAL
argument_list|,
name|GTK_SHADOW_IN
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|rect_w
argument_list|,
name|rect_h
argument_list|)
expr_stmt|;
else|else
name|gtk_draw_shadow
argument_list|(
name|color_area
operator|->
name|style
argument_list|,
name|color_area_pixmap
argument_list|,
name|GTK_STATE_NORMAL
argument_list|,
name|GTK_SHADOW_OUT
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|rect_w
argument_list|,
name|rect_h
argument_list|)
expr_stmt|;
comment|/*  draw the default pixmap  */
name|gdk_drawable_get_size
argument_list|(
name|default_pixmap
argument_list|,
operator|&
name|def_width
argument_list|,
operator|&
name|def_height
argument_list|)
expr_stmt|;
name|gdk_draw_drawable
argument_list|(
name|color_area_pixmap
argument_list|,
name|color_area_gc
argument_list|,
name|default_pixmap
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|height
operator|-
name|def_height
argument_list|,
name|def_width
argument_list|,
name|def_height
argument_list|)
expr_stmt|;
name|gdk_draw_drawable
argument_list|(
name|color_area_mask
argument_list|,
name|mask_gc
argument_list|,
name|default_mask
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|height
operator|-
name|def_height
argument_list|,
name|def_width
argument_list|,
name|def_height
argument_list|)
expr_stmt|;
comment|/*  draw the swap pixmap  */
name|gdk_drawable_get_size
argument_list|(
name|swap_pixmap
argument_list|,
operator|&
name|swap_width
argument_list|,
operator|&
name|swap_height
argument_list|)
expr_stmt|;
name|gdk_draw_drawable
argument_list|(
name|color_area_pixmap
argument_list|,
name|color_area_gc
argument_list|,
name|swap_pixmap
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
operator|-
name|swap_width
argument_list|,
literal|0
argument_list|,
name|swap_width
argument_list|,
name|swap_height
argument_list|)
expr_stmt|;
name|gdk_draw_drawable
argument_list|(
name|color_area_mask
argument_list|,
name|mask_gc
argument_list|,
name|swap_mask
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
operator|-
name|swap_width
argument_list|,
literal|0
argument_list|,
name|swap_width
argument_list|,
name|swap_height
argument_list|)
expr_stmt|;
comment|/*  draw the widget  */
name|gdk_gc_set_clip_mask
argument_list|(
name|color_area_gc
argument_list|,
name|color_area_mask
argument_list|)
expr_stmt|;
name|gdk_gc_set_clip_origin
argument_list|(
name|color_area_gc
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gdk_draw_drawable
argument_list|(
name|color_area
operator|->
name|window
argument_list|,
name|color_area_gc
argument_list|,
name|color_area_pixmap
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
comment|/*  reset the clip mask  */
name|gdk_gc_set_clip_mask
argument_list|(
name|color_area_gc
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|color_area_select_callback (ColorNotebook * color_notebook,const GimpRGB * color,ColorNotebookState state,gpointer client_data)
name|color_area_select_callback
parameter_list|(
name|ColorNotebook
modifier|*
name|color_notebook
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|ColorNotebookState
name|state
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
if|if
condition|(
name|color_notebook
condition|)
block|{
switch|switch
condition|(
name|state
condition|)
block|{
case|case
name|COLOR_NOTEBOOK_OK
case|:
name|color_notebook_hide
argument_list|(
name|color_notebook
argument_list|)
expr_stmt|;
name|color_notebook_active
operator|=
name|FALSE
expr_stmt|;
comment|/* Fallthrough */
case|case
name|COLOR_NOTEBOOK_UPDATE
case|:
if|if
condition|(
name|edit_color
operator|==
name|FOREGROUND
condition|)
name|gimp_context_set_foreground
argument_list|(
name|gimp_get_user_context
argument_list|(
name|the_gimp
argument_list|)
argument_list|,
name|color
argument_list|)
expr_stmt|;
else|else
name|gimp_context_set_background
argument_list|(
name|gimp_get_user_context
argument_list|(
name|the_gimp
argument_list|)
argument_list|,
name|color
argument_list|)
expr_stmt|;
break|break;
case|case
name|COLOR_NOTEBOOK_CANCEL
case|:
name|color_notebook_hide
argument_list|(
name|color_notebook
argument_list|)
expr_stmt|;
name|color_notebook_active
operator|=
name|FALSE
expr_stmt|;
name|gimp_context_set_foreground
argument_list|(
name|gimp_get_user_context
argument_list|(
name|the_gimp
argument_list|)
argument_list|,
operator|&
name|revert_fg
argument_list|)
expr_stmt|;
name|gimp_context_set_background
argument_list|(
name|gimp_get_user_context
argument_list|(
name|the_gimp
argument_list|)
argument_list|,
operator|&
name|revert_bg
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|color_area_edit (void)
name|color_area_edit
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpContext
modifier|*
name|user_context
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|user_context
operator|=
name|gimp_get_user_context
argument_list|(
name|the_gimp
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|color_notebook_active
condition|)
block|{
name|gimp_context_get_foreground
argument_list|(
name|user_context
argument_list|,
operator|&
name|revert_fg
argument_list|)
expr_stmt|;
name|gimp_context_get_background
argument_list|(
name|user_context
argument_list|,
operator|&
name|revert_bg
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|active_color
operator|==
name|FOREGROUND
condition|)
name|gimp_context_get_foreground
argument_list|(
name|user_context
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
else|else
name|gimp_context_get_background
argument_list|(
name|user_context
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|edit_color
operator|=
name|active_color
expr_stmt|;
if|if
condition|(
operator|!
name|color_notebook
condition|)
block|{
name|color_notebook
operator|=
name|color_notebook_new
argument_list|(
name|_
argument_list|(
literal|"Color Selection"
argument_list|)
argument_list|,
operator|(
specifier|const
name|GimpRGB
operator|*
operator|)
operator|&
name|color
argument_list|,
name|color_area_select_callback
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|color_notebook_active
operator|=
name|TRUE
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
operator|!
name|color_notebook_active
condition|)
block|{
name|color_notebook_show
argument_list|(
name|color_notebook
argument_list|)
expr_stmt|;
name|color_notebook_active
operator|=
name|TRUE
expr_stmt|;
block|}
else|else
block|{
name|color_notebook_show
argument_list|(
name|color_notebook
argument_list|)
expr_stmt|;
block|}
name|color_notebook_set_color
argument_list|(
name|color_notebook
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|color_area_events (GtkWidget * widget,GdkEvent * event)
name|color_area_events
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|)
block|{
name|GdkEventButton
modifier|*
name|bevent
decl_stmt|;
name|ColorAreaTarget
name|target
decl_stmt|;
specifier|static
name|ColorAreaTarget
name|press_target
init|=
name|INVALID_AREA
decl_stmt|;
switch|switch
condition|(
name|event
operator|->
name|type
condition|)
block|{
case|case
name|GDK_CONFIGURE
case|:
if|if
condition|(
name|color_area_pixmap
condition|)
block|{
name|gdk_drawable_unref
argument_list|(
name|color_area_pixmap
argument_list|)
expr_stmt|;
name|gdk_drawable_unref
argument_list|(
name|color_area_mask
argument_list|)
expr_stmt|;
block|}
name|color_area_pixmap
operator|=
name|gdk_pixmap_new
argument_list|(
name|widget
operator|->
name|window
argument_list|,
name|widget
operator|->
name|allocation
operator|.
name|width
argument_list|,
name|widget
operator|->
name|allocation
operator|.
name|height
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|color_area_mask
operator|=
name|gdk_pixmap_new
argument_list|(
name|widget
operator|->
name|window
argument_list|,
name|widget
operator|->
name|allocation
operator|.
name|width
argument_list|,
name|widget
operator|->
name|allocation
operator|.
name|height
argument_list|,
literal|1
argument_list|)
expr_stmt|;
break|break;
case|case
name|GDK_EXPOSE
case|:
if|if
condition|(
name|GTK_WIDGET_DRAWABLE
argument_list|(
name|widget
argument_list|)
condition|)
block|{
if|if
condition|(
operator|!
name|color_area_gc
condition|)
block|{
name|color_area_gc
operator|=
name|gdk_gc_new
argument_list|(
name|widget
operator|->
name|window
argument_list|)
expr_stmt|;
name|mask_gc
operator|=
name|gdk_gc_new
argument_list|(
name|color_area_mask
argument_list|)
expr_stmt|;
block|}
name|color_area_draw
argument_list|()
expr_stmt|;
block|}
break|break;
case|case
name|GDK_BUTTON_PRESS
case|:
name|bevent
operator|=
operator|(
name|GdkEventButton
operator|*
operator|)
name|event
expr_stmt|;
if|if
condition|(
name|bevent
operator|->
name|button
operator|==
literal|1
condition|)
block|{
name|target
operator|=
name|color_area_target
argument_list|(
name|bevent
operator|->
name|x
argument_list|,
name|bevent
operator|->
name|y
argument_list|)
expr_stmt|;
name|press_target
operator|=
name|INVALID_AREA
expr_stmt|;
switch|switch
condition|(
name|target
condition|)
block|{
case|case
name|FORE_AREA
case|:
case|case
name|BACK_AREA
case|:
if|if
condition|(
name|target
operator|!=
name|active_color
condition|)
block|{
name|active_color
operator|=
name|target
expr_stmt|;
name|color_area_draw
argument_list|()
expr_stmt|;
block|}
else|else
block|{
name|press_target
operator|=
name|target
expr_stmt|;
block|}
break|break;
case|case
name|SWAP_AREA
case|:
name|gimp_context_swap_colors
argument_list|(
name|gimp_get_user_context
argument_list|(
name|the_gimp
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|DEF_AREA
case|:
name|gimp_context_set_default_colors
argument_list|(
name|gimp_get_user_context
argument_list|(
name|the_gimp
argument_list|)
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
break|break;
case|case
name|GDK_BUTTON_RELEASE
case|:
name|bevent
operator|=
operator|(
name|GdkEventButton
operator|*
operator|)
name|event
expr_stmt|;
if|if
condition|(
name|bevent
operator|->
name|button
operator|==
literal|1
condition|)
block|{
name|target
operator|=
name|color_area_target
argument_list|(
name|bevent
operator|->
name|x
argument_list|,
name|bevent
operator|->
name|y
argument_list|)
expr_stmt|;
if|if
condition|(
name|target
operator|==
name|press_target
condition|)
block|{
switch|switch
condition|(
name|target
condition|)
block|{
case|case
name|FORE_AREA
case|:
case|case
name|BACK_AREA
case|:
name|color_area_edit
argument_list|()
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
name|press_target
operator|=
name|INVALID_AREA
expr_stmt|;
block|}
break|break;
case|case
name|GDK_LEAVE_NOTIFY
case|:
name|press_target
operator|=
name|INVALID_AREA
expr_stmt|;
break|break;
default|default:
break|break;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|color_area_realize (GtkWidget * widget,gpointer data)
name|color_area_realize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gtk_style_set_background
argument_list|(
name|widget
operator|->
name|style
argument_list|,
name|widget
operator|->
name|window
argument_list|,
name|GTK_STATE_NORMAL
argument_list|)
expr_stmt|;
name|gdk_window_set_back_pixmap
argument_list|(
name|widget
operator|->
name|window
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|color_area_create (gint width,gint height,GdkPixmap * default_pmap,GdkBitmap * default_msk,GdkPixmap * swap_pmap,GdkBitmap * swap_msk)
name|color_area_create
parameter_list|(
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GdkPixmap
modifier|*
name|default_pmap
parameter_list|,
name|GdkBitmap
modifier|*
name|default_msk
parameter_list|,
name|GdkPixmap
modifier|*
name|swap_pmap
parameter_list|,
name|GdkBitmap
modifier|*
name|swap_msk
parameter_list|)
block|{
name|color_area
operator|=
name|gtk_drawing_area_new
argument_list|()
expr_stmt|;
name|gtk_drawing_area_size
argument_list|(
name|GTK_DRAWING_AREA
argument_list|(
name|color_area
argument_list|)
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|gtk_widget_set_events
argument_list|(
name|color_area
argument_list|,
name|GDK_EXPOSURE_MASK
operator||
name|GDK_BUTTON_PRESS_MASK
operator||
name|GDK_BUTTON_RELEASE_MASK
operator||
name|GDK_ENTER_NOTIFY_MASK
operator||
name|GDK_LEAVE_NOTIFY_MASK
argument_list|)
expr_stmt|;
ifndef|#
directive|ifndef
name|GDK_WINDOWING_DIRECTFB
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|color_area
argument_list|)
argument_list|,
literal|"event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|color_area_events
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|color_area
argument_list|)
argument_list|,
literal|"realize"
argument_list|,
name|G_CALLBACK
argument_list|(
name|color_area_realize
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|default_pixmap
operator|=
name|default_pmap
expr_stmt|;
name|default_mask
operator|=
name|default_msk
expr_stmt|;
name|swap_pixmap
operator|=
name|swap_pmap
expr_stmt|;
name|swap_mask
operator|=
name|swap_msk
expr_stmt|;
comment|/*  dnd stuff  */
name|gtk_drag_source_set
argument_list|(
name|color_area
argument_list|,
name|GDK_BUTTON1_MASK
operator||
name|GDK_BUTTON2_MASK
argument_list|,
name|color_area_target_table
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|color_area_target_table
argument_list|)
argument_list|,
name|GDK_ACTION_COPY
operator||
name|GDK_ACTION_MOVE
argument_list|)
expr_stmt|;
name|gimp_dnd_color_source_set
argument_list|(
name|color_area
argument_list|,
name|color_area_drag_color
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_drag_dest_set
argument_list|(
name|color_area
argument_list|,
name|GTK_DEST_DEFAULT_HIGHLIGHT
operator||
name|GTK_DEST_DEFAULT_MOTION
operator||
name|GTK_DEST_DEFAULT_DROP
argument_list|,
name|color_area_target_table
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|color_area_target_table
argument_list|)
argument_list|,
name|GDK_ACTION_COPY
argument_list|)
expr_stmt|;
name|gimp_dnd_color_dest_set
argument_list|(
name|color_area
argument_list|,
name|color_area_drop_color
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp_get_user_context
argument_list|(
name|the_gimp
argument_list|)
argument_list|)
argument_list|,
literal|"foreground_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|color_area_color_changed
argument_list|)
argument_list|,
name|color_area
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp_get_user_context
argument_list|(
name|the_gimp
argument_list|)
argument_list|)
argument_list|,
literal|"background_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|color_area_color_changed
argument_list|)
argument_list|,
name|color_area
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|DISPLAY_FILTERS
comment|/* display filter dummy gdisplay */
name|color_area_gdisp
operator|=
name|g_new
argument_list|(
name|GDisplay
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|color_area_gdisp
operator|->
name|cd_list
operator|=
name|NULL
expr_stmt|;
name|color_area_gdisp
operator|->
name|cd_ui
operator|=
name|NULL
expr_stmt|;
name|color_area_gdisp
operator|->
name|gimage
operator|=
name|g_new
argument_list|(
name|GimpImage
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|color_area_gdisp
operator|->
name|gimage
operator|->
name|base_type
operator|=
name|RGB
expr_stmt|;
endif|#
directive|endif
comment|/* DISPLAY_FILTERS */
return|return
name|color_area
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|color_area_drag_color (GtkWidget * widget,GimpRGB * color,gpointer data)
name|color_area_drag_color
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
if|if
condition|(
name|active_color
operator|==
name|FOREGROUND
condition|)
name|gimp_context_get_foreground
argument_list|(
name|gimp_get_user_context
argument_list|(
name|the_gimp
argument_list|)
argument_list|,
name|color
argument_list|)
expr_stmt|;
else|else
name|gimp_context_get_background
argument_list|(
name|gimp_get_user_context
argument_list|(
name|the_gimp
argument_list|)
argument_list|,
name|color
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|color_area_drop_color (GtkWidget * widget,const GimpRGB * color,gpointer data)
name|color_area_drop_color
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
if|if
condition|(
name|color_notebook_active
operator|&&
name|active_color
operator|==
name|edit_color
condition|)
block|{
name|color_notebook_set_color
argument_list|(
name|color_notebook
argument_list|,
name|color
argument_list|)
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|active_color
operator|==
name|FOREGROUND
condition|)
name|gimp_context_set_foreground
argument_list|(
name|gimp_get_user_context
argument_list|(
name|the_gimp
argument_list|)
argument_list|,
name|color
argument_list|)
expr_stmt|;
else|else
name|gimp_context_set_background
argument_list|(
name|gimp_get_user_context
argument_list|(
name|the_gimp
argument_list|)
argument_list|,
name|color
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|color_area_color_changed (GimpContext * context,GimpRGB * color,gpointer data)
name|color_area_color_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|color_area_draw
argument_list|()
expr_stmt|;
block|}
end_function

end_unit

