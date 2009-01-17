begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
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
file|"libgimpmath/gimpmath.h"
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
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"splash.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  #define STARTUP_TIMER 1  */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c3d71860108
block|{
DECL|member|window
name|GtkWidget
modifier|*
name|window
decl_stmt|;
DECL|member|area
name|GtkWidget
modifier|*
name|area
decl_stmt|;
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|height
name|gint
name|height
decl_stmt|;
DECL|member|progress
name|GtkWidget
modifier|*
name|progress
decl_stmt|;
DECL|member|gc
name|GdkGC
modifier|*
name|gc
decl_stmt|;
DECL|member|upper
name|PangoLayout
modifier|*
name|upper
decl_stmt|;
DECL|member|upper_x
name|gint
name|upper_x
decl_stmt|;
DECL|member|upper_y
name|gint
name|upper_y
decl_stmt|;
DECL|member|lower
name|PangoLayout
modifier|*
name|lower
decl_stmt|;
DECL|member|lower_x
name|gint
name|lower_x
decl_stmt|;
DECL|member|lower_y
name|gint
name|lower_y
decl_stmt|;
ifdef|#
directive|ifdef
name|STARTUP_TIMER
DECL|member|timer
name|GTimer
modifier|*
name|timer
decl_stmt|;
DECL|member|last_time
name|gdouble
name|last_time
decl_stmt|;
DECL|member|text1
name|gchar
modifier|*
name|text1
decl_stmt|;
DECL|member|text2
name|gchar
modifier|*
name|text2
decl_stmt|;
endif|#
directive|endif
DECL|typedef|GimpSplash
block|}
name|GimpSplash
typedef|;
end_typedef

begin_decl_stmt
DECL|variable|splash
specifier|static
name|GimpSplash
modifier|*
name|splash
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|static
name|void
name|splash_position_layouts
parameter_list|(
name|GimpSplash
modifier|*
name|splash
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text1
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text2
parameter_list|,
name|GdkRectangle
modifier|*
name|area
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|splash_area_expose
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventExpose
modifier|*
name|event
parameter_list|,
name|GimpSplash
modifier|*
name|splash
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|splash_rectangle_union
parameter_list|(
name|GdkRectangle
modifier|*
name|dest
parameter_list|,
name|PangoRectangle
modifier|*
name|pango_rect
parameter_list|,
name|gint
name|offset_x
parameter_list|,
name|gint
name|offset_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|splash_average_text_area
parameter_list|(
name|GimpSplash
modifier|*
name|splash
parameter_list|,
name|GdkPixbuf
modifier|*
name|pixbuf
parameter_list|,
name|GdkColor
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GdkPixbufAnimation
modifier|*
name|splash_image_load
parameter_list|(
name|gboolean
name|be_verbose
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GdkPixbufAnimation
modifier|*
name|splash_image_pick_from_dir
parameter_list|(
specifier|const
name|gchar
modifier|*
name|dirname
parameter_list|,
name|gboolean
name|be_verbose
parameter_list|)
function_decl|;
end_function_decl

begin_ifdef
ifdef|#
directive|ifdef
name|STARTUP_TIMER
end_ifdef

begin_function_decl
specifier|static
name|void
name|splash_timer_elapsed
parameter_list|(
specifier|const
name|gchar
modifier|*
name|text1
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text2
parameter_list|,
name|gdouble
name|percentage
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|splash_create (gboolean be_verbose)
name|splash_create
parameter_list|(
name|gboolean
name|be_verbose
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GdkPixbufAnimation
modifier|*
name|pixbuf
decl_stmt|;
name|GdkScreen
modifier|*
name|screen
decl_stmt|;
name|GdkGCValues
name|values
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|splash
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|pixbuf
operator|=
name|splash_image_load
argument_list|(
name|be_verbose
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|pixbuf
condition|)
return|return;
name|splash
operator|=
name|g_slice_new0
argument_list|(
name|GimpSplash
argument_list|)
expr_stmt|;
name|splash
operator|->
name|window
operator|=
name|g_object_new
argument_list|(
name|GTK_TYPE_WINDOW
argument_list|,
literal|"type"
argument_list|,
name|GTK_WINDOW_TOPLEVEL
argument_list|,
literal|"type-hint"
argument_list|,
name|GDK_WINDOW_TYPE_HINT_SPLASHSCREEN
argument_list|,
literal|"title"
argument_list|,
name|_
argument_list|(
literal|"GIMP Startup"
argument_list|)
argument_list|,
literal|"role"
argument_list|,
literal|"gimp-startup"
argument_list|,
literal|"window-position"
argument_list|,
name|GTK_WIN_POS_CENTER
argument_list|,
literal|"resizable"
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|splash
operator|->
name|window
argument_list|,
literal|"delete-event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|exit
argument_list|)
argument_list|,
name|GINT_TO_POINTER
argument_list|(
literal|0
argument_list|)
argument_list|)
expr_stmt|;
name|screen
operator|=
name|gtk_widget_get_screen
argument_list|(
name|splash
operator|->
name|window
argument_list|)
expr_stmt|;
name|splash
operator|->
name|width
operator|=
name|MIN
argument_list|(
name|gdk_pixbuf_animation_get_width
argument_list|(
name|pixbuf
argument_list|)
argument_list|,
name|gdk_screen_get_width
argument_list|(
name|screen
argument_list|)
argument_list|)
expr_stmt|;
name|splash
operator|->
name|height
operator|=
name|MIN
argument_list|(
name|gdk_pixbuf_animation_get_height
argument_list|(
name|pixbuf
argument_list|)
argument_list|,
name|gdk_screen_get_height
argument_list|(
name|screen
argument_list|)
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
name|GTK_SHADOW_OUT
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|splash
operator|->
name|window
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
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
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
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
comment|/*  If the splash image is static, we use a drawing area and set the    *  image as back pixmap, otherwise a GtkImage is being used.    */
if|if
condition|(
name|gdk_pixbuf_animation_is_static_image
argument_list|(
name|pixbuf
argument_list|)
condition|)
block|{
name|splash
operator|->
name|area
operator|=
name|gtk_drawing_area_new
argument_list|()
expr_stmt|;
block|}
else|else
block|{
name|splash
operator|->
name|area
operator|=
name|gtk_image_new_from_animation
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
block|}
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|splash
operator|->
name|area
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|splash
operator|->
name|area
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|splash
operator|->
name|area
argument_list|,
name|splash
operator|->
name|width
argument_list|,
name|splash
operator|->
name|height
argument_list|)
expr_stmt|;
comment|/*  create the pango layouts  */
name|splash
operator|->
name|upper
operator|=
name|gtk_widget_create_pango_layout
argument_list|(
name|splash
operator|->
name|area
argument_list|,
literal|""
argument_list|)
expr_stmt|;
name|splash
operator|->
name|lower
operator|=
name|gtk_widget_create_pango_layout
argument_list|(
name|splash
operator|->
name|area
argument_list|,
literal|""
argument_list|)
expr_stmt|;
name|gimp_pango_layout_set_scale
argument_list|(
name|splash
operator|->
name|lower
argument_list|,
name|PANGO_SCALE_SMALL
argument_list|)
expr_stmt|;
comment|/*  this sets the initial layout positions  */
name|splash_position_layouts
argument_list|(
name|splash
argument_list|,
literal|""
argument_list|,
literal|""
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|splash_average_text_area
argument_list|(
name|splash
argument_list|,
name|gdk_pixbuf_animation_get_static_image
argument_list|(
name|pixbuf
argument_list|)
argument_list|,
operator|&
name|values
operator|.
name|foreground
argument_list|)
expr_stmt|;
name|gtk_widget_realize
argument_list|(
name|splash
operator|->
name|area
argument_list|)
expr_stmt|;
name|splash
operator|->
name|gc
operator|=
name|gdk_gc_new_with_values
argument_list|(
name|splash
operator|->
name|area
operator|->
name|window
argument_list|,
operator|&
name|values
argument_list|,
name|GDK_GC_FOREGROUND
argument_list|)
expr_stmt|;
if|if
condition|(
name|gdk_pixbuf_animation_is_static_image
argument_list|(
name|pixbuf
argument_list|)
condition|)
block|{
name|GdkPixmap
modifier|*
name|pixmap
init|=
name|gdk_pixmap_new
argument_list|(
name|splash
operator|->
name|area
operator|->
name|window
argument_list|,
name|splash
operator|->
name|width
argument_list|,
name|splash
operator|->
name|height
argument_list|,
operator|-
literal|1
argument_list|)
decl_stmt|;
name|gdk_draw_pixbuf
argument_list|(
name|pixmap
argument_list|,
name|splash
operator|->
name|gc
argument_list|,
name|gdk_pixbuf_animation_get_static_image
argument_list|(
name|pixbuf
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|splash
operator|->
name|width
argument_list|,
name|splash
operator|->
name|height
argument_list|,
name|GDK_RGB_DITHER_NORMAL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gdk_window_set_back_pixmap
argument_list|(
name|splash
operator|->
name|area
operator|->
name|window
argument_list|,
name|pixmap
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|pixmap
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|g_signal_connect_after
argument_list|(
name|splash
operator|->
name|area
argument_list|,
literal|"expose-event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|splash_area_expose
argument_list|)
argument_list|,
name|splash
argument_list|)
expr_stmt|;
comment|/*  add a progress bar  */
name|splash
operator|->
name|progress
operator|=
name|gtk_progress_bar_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|splash
operator|->
name|progress
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|splash
operator|->
name|progress
argument_list|)
expr_stmt|;
name|gtk_widget_show_now
argument_list|(
name|splash
operator|->
name|window
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|STARTUP_TIMER
name|splash
operator|->
name|timer
operator|=
name|g_timer_new
argument_list|()
expr_stmt|;
endif|#
directive|endif
block|}
end_function

begin_function
name|void
DECL|function|splash_destroy (void)
name|splash_destroy
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
operator|!
name|splash
condition|)
return|return;
name|gtk_widget_destroy
argument_list|(
name|splash
operator|->
name|window
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|splash
operator|->
name|gc
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|splash
operator|->
name|upper
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|splash
operator|->
name|lower
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|STARTUP_TIMER
name|g_timer_destroy
argument_list|(
name|splash
operator|->
name|timer
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|splash
operator|->
name|text1
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|splash
operator|->
name|text2
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|g_slice_free
argument_list|(
name|GimpSplash
argument_list|,
name|splash
argument_list|)
expr_stmt|;
name|splash
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|splash_update (const gchar * text1,const gchar * text2,gdouble percentage)
name|splash_update
parameter_list|(
specifier|const
name|gchar
modifier|*
name|text1
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text2
parameter_list|,
name|gdouble
name|percentage
parameter_list|)
block|{
name|GdkRectangle
name|expose
init|=
block|{
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|}
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|percentage
operator|>=
literal|0.0
operator|&&
name|percentage
operator|<=
literal|1.0
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|splash
condition|)
return|return;
ifdef|#
directive|ifdef
name|STARTUP_TIMER
name|splash_timer_elapsed
argument_list|(
name|text1
argument_list|,
name|text2
argument_list|,
name|percentage
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|splash_position_layouts
argument_list|(
name|splash
argument_list|,
name|text1
argument_list|,
name|text2
argument_list|,
operator|&
name|expose
argument_list|)
expr_stmt|;
if|if
condition|(
name|expose
operator|.
name|width
operator|>
literal|0
operator|&&
name|expose
operator|.
name|height
operator|>
literal|0
condition|)
name|gtk_widget_queue_draw_area
argument_list|(
name|splash
operator|->
name|area
argument_list|,
name|expose
operator|.
name|x
argument_list|,
name|expose
operator|.
name|y
argument_list|,
name|expose
operator|.
name|width
argument_list|,
name|expose
operator|.
name|height
argument_list|)
expr_stmt|;
name|gtk_progress_bar_set_fraction
argument_list|(
name|GTK_PROGRESS_BAR
argument_list|(
name|splash
operator|->
name|progress
argument_list|)
argument_list|,
name|percentage
argument_list|)
expr_stmt|;
if|if
condition|(
name|gtk_events_pending
argument_list|()
condition|)
name|gtk_main_iteration
argument_list|()
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|splash_area_expose (GtkWidget * widget,GdkEventExpose * event,GimpSplash * splash)
name|splash_area_expose
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventExpose
modifier|*
name|event
parameter_list|,
name|GimpSplash
modifier|*
name|splash
parameter_list|)
block|{
name|gdk_gc_set_clip_region
argument_list|(
name|splash
operator|->
name|gc
argument_list|,
name|event
operator|->
name|region
argument_list|)
expr_stmt|;
name|gdk_draw_layout
argument_list|(
name|widget
operator|->
name|window
argument_list|,
name|splash
operator|->
name|gc
argument_list|,
name|splash
operator|->
name|upper_x
argument_list|,
name|splash
operator|->
name|upper_y
argument_list|,
name|splash
operator|->
name|upper
argument_list|)
expr_stmt|;
name|gdk_draw_layout
argument_list|(
name|widget
operator|->
name|window
argument_list|,
name|splash
operator|->
name|gc
argument_list|,
name|splash
operator|->
name|lower_x
argument_list|,
name|splash
operator|->
name|lower_y
argument_list|,
name|splash
operator|->
name|lower
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_comment
comment|/* area returns the union of the previous and new ink rectangles */
end_comment

begin_function
specifier|static
name|void
DECL|function|splash_position_layouts (GimpSplash * splash,const gchar * text1,const gchar * text2,GdkRectangle * area)
name|splash_position_layouts
parameter_list|(
name|GimpSplash
modifier|*
name|splash
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text1
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text2
parameter_list|,
name|GdkRectangle
modifier|*
name|area
parameter_list|)
block|{
name|PangoRectangle
name|ink
decl_stmt|;
name|PangoRectangle
name|logical
decl_stmt|;
if|if
condition|(
name|text1
condition|)
block|{
name|pango_layout_get_pixel_extents
argument_list|(
name|splash
operator|->
name|upper
argument_list|,
operator|&
name|ink
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|area
condition|)
name|splash_rectangle_union
argument_list|(
name|area
argument_list|,
operator|&
name|ink
argument_list|,
name|splash
operator|->
name|upper_x
argument_list|,
name|splash
operator|->
name|upper_y
argument_list|)
expr_stmt|;
name|pango_layout_set_text
argument_list|(
name|splash
operator|->
name|upper
argument_list|,
name|text1
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|pango_layout_get_pixel_extents
argument_list|(
name|splash
operator|->
name|upper
argument_list|,
operator|&
name|ink
argument_list|,
operator|&
name|logical
argument_list|)
expr_stmt|;
name|splash
operator|->
name|upper_x
operator|=
operator|(
name|splash
operator|->
name|width
operator|-
name|logical
operator|.
name|width
operator|)
operator|/
literal|2
expr_stmt|;
name|splash
operator|->
name|upper_y
operator|=
name|splash
operator|->
name|height
operator|-
operator|(
literal|2
operator|*
name|logical
operator|.
name|height
operator|+
literal|6
operator|)
expr_stmt|;
if|if
condition|(
name|area
condition|)
name|splash_rectangle_union
argument_list|(
name|area
argument_list|,
operator|&
name|ink
argument_list|,
name|splash
operator|->
name|upper_x
argument_list|,
name|splash
operator|->
name|upper_y
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|text2
condition|)
block|{
name|pango_layout_get_pixel_extents
argument_list|(
name|splash
operator|->
name|lower
argument_list|,
operator|&
name|ink
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|area
condition|)
name|splash_rectangle_union
argument_list|(
name|area
argument_list|,
operator|&
name|ink
argument_list|,
name|splash
operator|->
name|lower_x
argument_list|,
name|splash
operator|->
name|lower_y
argument_list|)
expr_stmt|;
name|pango_layout_set_text
argument_list|(
name|splash
operator|->
name|lower
argument_list|,
name|text2
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|pango_layout_get_pixel_extents
argument_list|(
name|splash
operator|->
name|lower
argument_list|,
operator|&
name|ink
argument_list|,
operator|&
name|logical
argument_list|)
expr_stmt|;
name|splash
operator|->
name|lower_x
operator|=
operator|(
name|splash
operator|->
name|width
operator|-
name|logical
operator|.
name|width
operator|)
operator|/
literal|2
expr_stmt|;
name|splash
operator|->
name|lower_y
operator|=
name|splash
operator|->
name|height
operator|-
operator|(
name|logical
operator|.
name|height
operator|+
literal|6
operator|)
expr_stmt|;
if|if
condition|(
name|area
condition|)
name|splash_rectangle_union
argument_list|(
name|area
argument_list|,
operator|&
name|ink
argument_list|,
name|splash
operator|->
name|lower_x
argument_list|,
name|splash
operator|->
name|lower_y
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|splash_rectangle_union (GdkRectangle * dest,PangoRectangle * pango_rect,gint offset_x,gint offset_y)
name|splash_rectangle_union
parameter_list|(
name|GdkRectangle
modifier|*
name|dest
parameter_list|,
name|PangoRectangle
modifier|*
name|pango_rect
parameter_list|,
name|gint
name|offset_x
parameter_list|,
name|gint
name|offset_y
parameter_list|)
block|{
name|GdkRectangle
name|rect
decl_stmt|;
name|rect
operator|.
name|x
operator|=
name|pango_rect
operator|->
name|x
operator|+
name|offset_x
expr_stmt|;
name|rect
operator|.
name|y
operator|=
name|pango_rect
operator|->
name|y
operator|+
name|offset_y
expr_stmt|;
name|rect
operator|.
name|width
operator|=
name|pango_rect
operator|->
name|width
expr_stmt|;
name|rect
operator|.
name|height
operator|=
name|pango_rect
operator|->
name|height
expr_stmt|;
if|if
condition|(
name|dest
operator|->
name|width
operator|>
literal|0
operator|&&
name|dest
operator|->
name|height
operator|>
literal|0
condition|)
name|gdk_rectangle_union
argument_list|(
name|dest
argument_list|,
operator|&
name|rect
argument_list|,
name|dest
argument_list|)
expr_stmt|;
else|else
operator|*
name|dest
operator|=
name|rect
expr_stmt|;
block|}
end_function

begin_comment
comment|/* This function chooses a gray value for the text color, based on  * the average luminance of the text area of the splash image.  */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|splash_average_text_area (GimpSplash * splash,GdkPixbuf * pixbuf,GdkColor * color)
name|splash_average_text_area
parameter_list|(
name|GimpSplash
modifier|*
name|splash
parameter_list|,
name|GdkPixbuf
modifier|*
name|pixbuf
parameter_list|,
name|GdkColor
modifier|*
name|color
parameter_list|)
block|{
specifier|const
name|guchar
modifier|*
name|pixels
decl_stmt|;
name|gint
name|rowstride
decl_stmt|;
name|gint
name|channels
decl_stmt|;
name|gint
name|luminance
init|=
literal|0
decl_stmt|;
name|guint
name|sum
index|[
literal|3
index|]
init|=
block|{
literal|0
block|,
literal|0
block|,
literal|0
block|}
decl_stmt|;
name|GdkRectangle
name|image
init|=
block|{
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|}
decl_stmt|;
name|GdkRectangle
name|area
init|=
block|{
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|}
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GDK_IS_PIXBUF
argument_list|(
name|pixbuf
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gdk_pixbuf_get_bits_per_sample
argument_list|(
name|pixbuf
argument_list|)
operator|==
literal|8
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|image
operator|.
name|width
operator|=
name|gdk_pixbuf_get_width
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|image
operator|.
name|height
operator|=
name|gdk_pixbuf_get_height
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|rowstride
operator|=
name|gdk_pixbuf_get_rowstride
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|channels
operator|=
name|gdk_pixbuf_get_n_channels
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
name|splash_position_layouts
argument_list|(
name|splash
argument_list|,
literal|"Short text"
argument_list|,
literal|"Somewhat longer text"
argument_list|,
operator|&
name|area
argument_list|)
expr_stmt|;
name|splash_position_layouts
argument_list|(
name|splash
argument_list|,
literal|""
argument_list|,
literal|""
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gdk_rectangle_intersect
argument_list|(
operator|&
name|image
argument_list|,
operator|&
name|area
argument_list|,
operator|&
name|area
argument_list|)
condition|)
block|{
specifier|const
name|gint
name|count
init|=
name|area
operator|.
name|width
operator|*
name|area
operator|.
name|height
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|pixels
operator|+=
name|area
operator|.
name|x
operator|*
name|channels
expr_stmt|;
name|pixels
operator|+=
name|area
operator|.
name|y
operator|*
name|rowstride
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|area
operator|.
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
name|pixels
decl_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|area
operator|.
name|width
condition|;
name|x
operator|++
control|)
block|{
name|sum
index|[
literal|0
index|]
operator|+=
name|src
index|[
literal|0
index|]
expr_stmt|;
name|sum
index|[
literal|1
index|]
operator|+=
name|src
index|[
literal|1
index|]
expr_stmt|;
name|sum
index|[
literal|2
index|]
operator|+=
name|src
index|[
literal|2
index|]
expr_stmt|;
name|src
operator|+=
name|channels
expr_stmt|;
block|}
name|pixels
operator|+=
name|rowstride
expr_stmt|;
block|}
name|luminance
operator|=
name|GIMP_RGB_LUMINANCE
argument_list|(
name|sum
index|[
literal|0
index|]
operator|/
name|count
argument_list|,
name|sum
index|[
literal|1
index|]
operator|/
name|count
argument_list|,
name|sum
index|[
literal|2
index|]
operator|/
name|count
argument_list|)
expr_stmt|;
name|luminance
operator|=
name|CLAMP0255
argument_list|(
name|luminance
operator|>
literal|127
condition|?
name|luminance
operator|-
literal|223
else|:
name|luminance
operator|+
literal|223
argument_list|)
expr_stmt|;
block|}
name|color
operator|->
name|red
operator|=
name|color
operator|->
name|green
operator|=
name|color
operator|->
name|blue
operator|=
operator|(
name|luminance
operator|<<
literal|8
operator||
name|luminance
operator|)
expr_stmt|;
return|return
name|gdk_colormap_alloc_color
argument_list|(
name|gtk_widget_get_colormap
argument_list|(
name|splash
operator|->
name|area
argument_list|)
argument_list|,
name|color
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GdkPixbufAnimation
modifier|*
DECL|function|splash_image_load (gboolean be_verbose)
name|splash_image_load
parameter_list|(
name|gboolean
name|be_verbose
parameter_list|)
block|{
name|GdkPixbufAnimation
modifier|*
name|pixbuf
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|filename
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"gimp-splash.png"
argument_list|)
expr_stmt|;
if|if
condition|(
name|be_verbose
condition|)
name|g_printerr
argument_list|(
literal|"Trying splash '%s' ... "
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|pixbuf
operator|=
name|gdk_pixbuf_animation_new_from_file
argument_list|(
name|filename
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
name|be_verbose
condition|)
name|g_printerr
argument_list|(
name|pixbuf
condition|?
literal|"OK\n"
else|:
literal|"failed\n"
argument_list|)
expr_stmt|;
if|if
condition|(
name|pixbuf
condition|)
return|return
name|pixbuf
return|;
name|filename
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"splashes"
argument_list|)
expr_stmt|;
name|pixbuf
operator|=
name|splash_image_pick_from_dir
argument_list|(
name|filename
argument_list|,
name|be_verbose
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
name|pixbuf
condition|)
return|return
name|pixbuf
return|;
name|filename
operator|=
name|g_build_filename
argument_list|(
name|gimp_data_directory
argument_list|()
argument_list|,
literal|"images"
argument_list|,
literal|"gimp-splash.png"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|be_verbose
condition|)
name|g_printerr
argument_list|(
literal|"Trying splash '%s' ... "
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|pixbuf
operator|=
name|gdk_pixbuf_animation_new_from_file
argument_list|(
name|filename
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
name|be_verbose
condition|)
name|g_printerr
argument_list|(
name|pixbuf
condition|?
literal|"OK\n"
else|:
literal|"failed\n"
argument_list|)
expr_stmt|;
if|if
condition|(
name|pixbuf
condition|)
return|return
name|pixbuf
return|;
name|filename
operator|=
name|g_build_filename
argument_list|(
name|gimp_data_directory
argument_list|()
argument_list|,
literal|"splashes"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|pixbuf
operator|=
name|splash_image_pick_from_dir
argument_list|(
name|filename
argument_list|,
name|be_verbose
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
return|return
name|pixbuf
return|;
block|}
end_function

begin_function
specifier|static
name|GdkPixbufAnimation
modifier|*
DECL|function|splash_image_pick_from_dir (const gchar * dirname,gboolean be_verbose)
name|splash_image_pick_from_dir
parameter_list|(
specifier|const
name|gchar
modifier|*
name|dirname
parameter_list|,
name|gboolean
name|be_verbose
parameter_list|)
block|{
name|GdkPixbufAnimation
modifier|*
name|pixbuf
init|=
name|NULL
decl_stmt|;
name|GDir
modifier|*
name|dir
init|=
name|g_dir_open
argument_list|(
name|dirname
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
if|if
condition|(
name|dir
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|entry
decl_stmt|;
name|GList
modifier|*
name|splashes
init|=
name|NULL
decl_stmt|;
while|while
condition|(
operator|(
name|entry
operator|=
name|g_dir_read_name
argument_list|(
name|dir
argument_list|)
operator|)
condition|)
name|splashes
operator|=
name|g_list_prepend
argument_list|(
name|splashes
argument_list|,
name|g_strdup
argument_list|(
name|entry
argument_list|)
argument_list|)
expr_stmt|;
name|g_dir_close
argument_list|(
name|dir
argument_list|)
expr_stmt|;
if|if
condition|(
name|splashes
condition|)
block|{
name|gint32
name|i
init|=
name|g_random_int_range
argument_list|(
literal|0
argument_list|,
name|g_list_length
argument_list|(
name|splashes
argument_list|)
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|filename
init|=
name|g_build_filename
argument_list|(
name|dirname
argument_list|,
name|g_list_nth_data
argument_list|(
name|splashes
argument_list|,
name|i
argument_list|)
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
if|if
condition|(
name|be_verbose
condition|)
name|g_printerr
argument_list|(
literal|"Trying splash '%s' ... "
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|pixbuf
operator|=
name|gdk_pixbuf_animation_new_from_file
argument_list|(
name|filename
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
name|be_verbose
condition|)
name|g_printerr
argument_list|(
name|pixbuf
condition|?
literal|"OK\n"
else|:
literal|"failed\n"
argument_list|)
expr_stmt|;
name|g_list_foreach
argument_list|(
name|splashes
argument_list|,
operator|(
name|GFunc
operator|)
name|g_free
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|splashes
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|pixbuf
return|;
block|}
end_function

begin_ifdef
ifdef|#
directive|ifdef
name|STARTUP_TIMER
end_ifdef

begin_function
specifier|static
name|void
DECL|function|splash_timer_elapsed (const gchar * text1,const gchar * text2,gdouble percentage)
name|splash_timer_elapsed
parameter_list|(
specifier|const
name|gchar
modifier|*
name|text1
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text2
parameter_list|,
name|gdouble
name|percentage
parameter_list|)
block|{
name|gdouble
name|elapsed
init|=
name|g_timer_elapsed
argument_list|(
name|splash
operator|->
name|timer
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
if|if
condition|(
name|text1
condition|)
block|{
name|g_free
argument_list|(
name|splash
operator|->
name|text1
argument_list|)
expr_stmt|;
name|splash
operator|->
name|text1
operator|=
name|g_strdup
argument_list|(
name|text1
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|text2
condition|)
block|{
name|g_free
argument_list|(
name|splash
operator|->
name|text2
argument_list|)
expr_stmt|;
name|splash
operator|->
name|text2
operator|=
name|g_strdup
argument_list|(
name|text2
argument_list|)
expr_stmt|;
block|}
name|g_printerr
argument_list|(
literal|"%8g  %8g  -  %s %g%%  -  %s\n"
argument_list|,
name|elapsed
argument_list|,
name|elapsed
operator|-
name|splash
operator|->
name|last_time
argument_list|,
name|splash
operator|->
name|text1
condition|?
name|splash
operator|->
name|text1
else|:
literal|""
argument_list|,
name|percentage
operator|*
literal|100.0
argument_list|,
name|splash
operator|->
name|text2
condition|?
name|splash
operator|->
name|text2
else|:
literal|""
argument_list|)
expr_stmt|;
name|splash
operator|->
name|last_time
operator|=
name|elapsed
expr_stmt|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

end_unit

