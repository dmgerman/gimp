begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<time.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpfeatures.h"
end_include

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpenv.h"
end_include

begin_include
include|#
directive|include
file|"about_dialog.h"
end_include

begin_define
DECL|macro|ANIMATION_STEPS
define|#
directive|define
name|ANIMATION_STEPS
value|16
end_define

begin_define
DECL|macro|ANIMATION_SIZE
define|#
directive|define
name|ANIMATION_SIZE
value|2
end_define

begin_function_decl
specifier|static
name|int
name|about_dialog_load_logo
parameter_list|(
name|GtkWidget
modifier|*
name|window
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|about_dialog_destroy
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|about_dialog_unmap
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|int
name|about_dialog_logo_expose
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventExpose
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|int
name|about_dialog_button
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|int
name|about_dialog_timer
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|about_dialog
specifier|static
name|GtkWidget
modifier|*
name|about_dialog
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|logo_area
specifier|static
name|GtkWidget
modifier|*
name|logo_area
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|scroll_area
specifier|static
name|GtkWidget
modifier|*
name|scroll_area
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|logo_pixmap
specifier|static
name|GdkPixmap
modifier|*
name|logo_pixmap
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|scroll_pixmap
specifier|static
name|GdkPixmap
modifier|*
name|scroll_pixmap
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|dissolve_map
specifier|static
name|unsigned
name|char
modifier|*
name|dissolve_map
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|dissolve_width
specifier|static
name|int
name|dissolve_width
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|dissolve_height
specifier|static
name|int
name|dissolve_height
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|logo_width
specifier|static
name|int
name|logo_width
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|logo_height
specifier|static
name|int
name|logo_height
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|do_animation
specifier|static
name|int
name|do_animation
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|do_scrolling
specifier|static
name|int
name|do_scrolling
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|scroll_state
specifier|static
name|int
name|scroll_state
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|frame
specifier|static
name|int
name|frame
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|offset
specifier|static
name|int
name|offset
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|timer
specifier|static
name|int
name|timer
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|scroll_text
specifier|static
name|char
modifier|*
name|scroll_text
index|[]
init|=
block|{
literal|"Lauri Alanko"
block|,
literal|"Shawn Amundson"
block|,
literal|"John Beale"
block|,
literal|"Zach Beane"
block|,
literal|"Tom Bech"
block|,
literal|"Marc Bless"
block|,
literal|"Edward Blevins"
block|,
literal|"Roberto Boyd"
block|,
literal|"Seth Burgess"
block|,
literal|"Brent Burton"
block|,
literal|"Francisco Bustamante"
block|,
literal|"Ed Connel"
block|,
literal|"Jay Cox"
block|,
literal|"Andreas Dilger"
block|,
literal|"Austin Donnelly"
block|,
literal|"Misha Dynin"
block|,
literal|"Larry Ewing"
block|,
literal|"Nick Fetchak"
block|,
literal|"David Forsyth"
block|,
literal|"Jim Geuther"
block|,
literal|"Scott Goehring"
block|,
literal|"Heiko Goller"
block|,
literal|"Michael Hammel"
block|,
literal|"Christoph Hoegl"
block|,
literal|"Jan Hubicka"
block|,
literal|"Simon Janes"
block|,
literal|"Tim Janik"
block|,
literal|"Tuomas Kuosmanen"
block|,
literal|"Peter Kirchgessner"
block|,
literal|"Nick Lamb"
block|,
literal|"Karl LaRocca"
block|,
literal|"Jens Lautenbacher"
block|,
literal|"Laramie Leavitt"
block|,
literal|"Elliot Lee"
block|,
literal|"Raph Levien"
block|,
literal|"Adrian Likins"
block|,
literal|"Ingo Luetkebohle"
block|,
literal|"Josh MacDonald"
block|,
literal|"Ed Mackey"
block|,
literal|"Marcelo Malheiros"
block|,
literal|"Ian Main"
block|,
literal|"Torsten Martinsen"
block|,
literal|"Federico Mena"
block|,
literal|"Adam D. Moss"
block|,
literal|"Shuji Narazaki"
block|,
literal|"Sven Neumann"
block|,
literal|"Stephen Robert Norris"
block|,
literal|"Erik Nygren"
block|,
literal|"Miles O'Neal"
block|,
literal|"Jay Painter"
block|,
literal|"Mike Phillips"
block|,
literal|"Raphael Quinet"
block|,
literal|"James Robinson"
block|,
literal|"Mike Schaeffer"
block|,
literal|"Tracy Scott"
block|,
literal|"Manish Singh"
block|,
literal|"Nathan Summers"
block|,
literal|"Mike Sweet"
block|,
literal|"Eiichi Takamori"
block|,
literal|"Tristan Tarrant"
block|,
literal|"Owen Taylor"
block|,
literal|"Ian Tester"
block|,
literal|"Andy Thomas"
block|,
literal|"James Wang"
block|,
literal|"Kris Wehner"
block|,
literal|"Matthew Wilson"
block|, }
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|nscroll_texts
specifier|static
name|int
name|nscroll_texts
init|=
sizeof|sizeof
argument_list|(
name|scroll_text
argument_list|)
operator|/
sizeof|sizeof
argument_list|(
name|scroll_text
index|[
literal|0
index|]
argument_list|)
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|scroll_text_widths
specifier|static
name|int
name|scroll_text_widths
index|[
literal|100
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|cur_scroll_text
specifier|static
name|int
name|cur_scroll_text
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|cur_scroll_index
specifier|static
name|int
name|cur_scroll_index
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|shuffle_array
specifier|static
name|int
name|shuffle_array
index|[
sizeof|sizeof
argument_list|(
name|scroll_text
argument_list|)
operator|/
sizeof|sizeof
argument_list|(
name|scroll_text
index|[
literal|0
index|]
argument_list|)
index|]
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|about_dialog_create (int timeout)
name|about_dialog_create
parameter_list|(
name|int
name|timeout
parameter_list|)
block|{
name|GtkStyle
modifier|*
name|style
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|aboutframe
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|alignment
decl_stmt|;
name|gint
name|max_width
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gchar
modifier|*
name|label_text
decl_stmt|;
if|if
condition|(
operator|!
name|about_dialog
condition|)
block|{
name|about_dialog
operator|=
name|gtk_window_new
argument_list|(
name|GTK_WINDOW_DIALOG
argument_list|)
expr_stmt|;
name|gtk_window_set_wmclass
argument_list|(
name|GTK_WINDOW
argument_list|(
name|about_dialog
argument_list|)
argument_list|,
literal|"about_dialog"
argument_list|,
literal|"Gimp"
argument_list|)
expr_stmt|;
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|about_dialog
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"About the GIMP"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_window_set_policy
argument_list|(
name|GTK_WINDOW
argument_list|(
name|about_dialog
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_window_position
argument_list|(
name|GTK_WINDOW
argument_list|(
name|about_dialog
argument_list|)
argument_list|,
name|GTK_WIN_POS_CENTER
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|about_dialog
argument_list|)
argument_list|,
literal|"destroy"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|about_dialog_destroy
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|about_dialog
argument_list|)
argument_list|,
literal|"unmap_event"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|about_dialog_unmap
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|about_dialog
argument_list|)
argument_list|,
literal|"button_press_event"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|about_dialog_button
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_set_events
argument_list|(
name|about_dialog
argument_list|,
name|GDK_BUTTON_PRESS_MASK
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|about_dialog_load_logo
argument_list|(
name|about_dialog
argument_list|)
condition|)
block|{
name|gtk_widget_destroy
argument_list|(
name|about_dialog
argument_list|)
expr_stmt|;
name|about_dialog
operator|=
name|NULL
expr_stmt|;
return|return;
block|}
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_container_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|about_dialog
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
name|aboutframe
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
name|aboutframe
argument_list|)
argument_list|,
name|GTK_SHADOW_IN
argument_list|)
expr_stmt|;
name|gtk_container_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|aboutframe
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|aboutframe
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
name|aboutframe
argument_list|)
expr_stmt|;
name|logo_area
operator|=
name|gtk_drawing_area_new
argument_list|()
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|logo_area
argument_list|)
argument_list|,
literal|"expose_event"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|about_dialog_logo_expose
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_drawing_area_size
argument_list|(
name|GTK_DRAWING_AREA
argument_list|(
name|logo_area
argument_list|)
argument_list|,
name|logo_width
argument_list|,
name|logo_height
argument_list|)
expr_stmt|;
name|gtk_widget_set_events
argument_list|(
name|logo_area
argument_list|,
name|GDK_EXPOSURE_MASK
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|aboutframe
argument_list|)
argument_list|,
name|logo_area
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|logo_area
argument_list|)
expr_stmt|;
name|gtk_widget_realize
argument_list|(
name|logo_area
argument_list|)
expr_stmt|;
name|gdk_window_set_background
argument_list|(
name|logo_area
operator|->
name|window
argument_list|,
operator|&
name|logo_area
operator|->
name|style
operator|->
name|black
argument_list|)
expr_stmt|;
name|style
operator|=
name|gtk_style_new
argument_list|()
expr_stmt|;
name|gdk_font_unref
argument_list|(
name|style
operator|->
name|font
argument_list|)
expr_stmt|;
name|style
operator|->
name|font
operator|=
name|gdk_font_load
argument_list|(
name|_
argument_list|(
literal|"-Adobe-Helvetica-Medium-R-Normal--*-140-*-*-*-*-*-*"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_push_style
argument_list|(
name|style
argument_list|)
expr_stmt|;
name|label_text
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s%s%s"
argument_list|,
name|_
argument_list|(
literal|"Version "
argument_list|)
argument_list|,
name|GIMP_VERSION
argument_list|,
name|_
argument_list|(
literal|" brought to you by"
argument_list|)
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|label_text
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|label_text
argument_list|)
expr_stmt|;
name|label_text
operator|=
name|NULL
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|label
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Spencer Kimball& Peter Mattis"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|label
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|gtk_widget_pop_style
argument_list|()
expr_stmt|;
name|alignment
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
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|alignment
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|alignment
argument_list|)
expr_stmt|;
name|aboutframe
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
name|aboutframe
argument_list|)
argument_list|,
name|GTK_SHADOW_IN
argument_list|)
expr_stmt|;
name|gtk_container_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|aboutframe
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|alignment
argument_list|)
argument_list|,
name|aboutframe
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|aboutframe
argument_list|)
expr_stmt|;
name|max_width
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
name|nscroll_texts
condition|;
name|i
operator|++
control|)
block|{
name|scroll_text_widths
index|[
name|i
index|]
operator|=
name|gdk_string_width
argument_list|(
name|aboutframe
operator|->
name|style
operator|->
name|font
argument_list|,
name|scroll_text
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|max_width
operator|=
name|MAX
argument_list|(
name|max_width
argument_list|,
name|scroll_text_widths
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
name|scroll_area
operator|=
name|gtk_drawing_area_new
argument_list|()
expr_stmt|;
name|gtk_drawing_area_size
argument_list|(
name|GTK_DRAWING_AREA
argument_list|(
name|scroll_area
argument_list|)
argument_list|,
name|max_width
operator|+
literal|10
argument_list|,
name|aboutframe
operator|->
name|style
operator|->
name|font
operator|->
name|ascent
operator|+
name|aboutframe
operator|->
name|style
operator|->
name|font
operator|->
name|descent
argument_list|)
expr_stmt|;
name|gtk_widget_set_events
argument_list|(
name|scroll_area
argument_list|,
name|GDK_BUTTON_PRESS_MASK
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|aboutframe
argument_list|)
argument_list|,
name|scroll_area
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|scroll_area
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Please visit http://www.gimp.org/ for more info"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|label
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|gtk_widget_realize
argument_list|(
name|scroll_area
argument_list|)
expr_stmt|;
name|gdk_window_set_background
argument_list|(
name|scroll_area
operator|->
name|window
argument_list|,
operator|&
name|scroll_area
operator|->
name|style
operator|->
name|white
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|GTK_WIDGET_VISIBLE
argument_list|(
name|about_dialog
argument_list|)
condition|)
block|{
name|gtk_widget_show
argument_list|(
name|about_dialog
argument_list|)
expr_stmt|;
name|do_animation
operator|=
name|TRUE
expr_stmt|;
name|do_scrolling
operator|=
name|FALSE
expr_stmt|;
name|scroll_state
operator|=
literal|0
expr_stmt|;
name|frame
operator|=
literal|0
expr_stmt|;
name|offset
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
name|nscroll_texts
condition|;
name|i
operator|++
control|)
block|{
name|shuffle_array
index|[
name|i
index|]
operator|=
name|i
expr_stmt|;
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|nscroll_texts
condition|;
name|i
operator|++
control|)
block|{
name|int
name|j
decl_stmt|,
name|k
decl_stmt|;
name|j
operator|=
name|rand
argument_list|()
operator|%
name|nscroll_texts
expr_stmt|;
name|k
operator|=
name|rand
argument_list|()
operator|%
name|nscroll_texts
expr_stmt|;
if|if
condition|(
name|j
operator|!=
name|k
condition|)
block|{
name|int
name|t
decl_stmt|;
name|t
operator|=
name|shuffle_array
index|[
name|j
index|]
expr_stmt|;
name|shuffle_array
index|[
name|j
index|]
operator|=
name|shuffle_array
index|[
name|k
index|]
expr_stmt|;
name|shuffle_array
index|[
name|k
index|]
operator|=
name|t
expr_stmt|;
block|}
block|}
block|}
else|else
block|{
name|gdk_window_raise
argument_list|(
name|about_dialog
operator|->
name|window
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|int
DECL|function|about_dialog_load_logo (GtkWidget * window)
name|about_dialog_load_logo
parameter_list|(
name|GtkWidget
modifier|*
name|window
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
name|GdkGC
modifier|*
name|gc
decl_stmt|;
name|char
name|buf
index|[
literal|1024
index|]
decl_stmt|;
name|unsigned
name|char
modifier|*
name|pixelrow
decl_stmt|;
name|FILE
modifier|*
name|fp
decl_stmt|;
name|int
name|count
decl_stmt|;
name|int
name|i
decl_stmt|,
name|j
decl_stmt|,
name|k
decl_stmt|;
if|if
condition|(
name|logo_pixmap
condition|)
return|return
name|TRUE
return|;
name|g_snprintf
argument_list|(
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
literal|"%s"
name|G_DIR_SEPARATOR_S
literal|"gimp_logo.ppm"
argument_list|,
name|gimp_data_directory
argument_list|()
argument_list|)
expr_stmt|;
name|fp
operator|=
name|fopen
argument_list|(
name|buf
argument_list|,
literal|"rb"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|fp
condition|)
return|return
literal|0
return|;
name|fgets
argument_list|(
name|buf
argument_list|,
literal|1024
argument_list|,
name|fp
argument_list|)
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|buf
argument_list|,
literal|"P6\n"
argument_list|)
operator|!=
literal|0
condition|)
block|{
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
return|return
literal|0
return|;
block|}
name|fgets
argument_list|(
name|buf
argument_list|,
literal|1024
argument_list|,
name|fp
argument_list|)
expr_stmt|;
name|fgets
argument_list|(
name|buf
argument_list|,
literal|1024
argument_list|,
name|fp
argument_list|)
expr_stmt|;
name|sscanf
argument_list|(
name|buf
argument_list|,
literal|"%d %d"
argument_list|,
operator|&
name|logo_width
argument_list|,
operator|&
name|logo_height
argument_list|)
expr_stmt|;
name|fgets
argument_list|(
name|buf
argument_list|,
literal|1024
argument_list|,
name|fp
argument_list|)
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|buf
argument_list|,
literal|"255\n"
argument_list|)
operator|!=
literal|0
condition|)
block|{
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
return|return
literal|0
return|;
block|}
name|preview
operator|=
name|gtk_preview_new
argument_list|(
name|GTK_PREVIEW_COLOR
argument_list|)
expr_stmt|;
name|gtk_preview_size
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|,
name|logo_width
argument_list|,
name|logo_height
argument_list|)
expr_stmt|;
name|pixelrow
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|logo_width
operator|*
literal|3
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|logo_height
condition|;
name|i
operator|++
control|)
block|{
name|count
operator|=
name|fread
argument_list|(
name|pixelrow
argument_list|,
expr|sizeof
operator|(
name|unsigned
name|char
operator|)
argument_list|,
name|logo_width
operator|*
literal|3
argument_list|,
name|fp
argument_list|)
expr_stmt|;
if|if
condition|(
name|count
operator|!=
operator|(
name|logo_width
operator|*
literal|3
operator|)
condition|)
block|{
name|gtk_widget_destroy
argument_list|(
name|preview
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pixelrow
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
return|return
literal|0
return|;
block|}
name|gtk_preview_draw_row
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|,
name|pixelrow
argument_list|,
literal|0
argument_list|,
name|i
argument_list|,
name|logo_width
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_realize
argument_list|(
name|window
argument_list|)
expr_stmt|;
name|logo_pixmap
operator|=
name|gdk_pixmap_new
argument_list|(
name|window
operator|->
name|window
argument_list|,
name|logo_width
argument_list|,
name|logo_height
argument_list|,
name|gtk_preview_get_visual
argument_list|()
operator|->
name|depth
argument_list|)
expr_stmt|;
name|gc
operator|=
name|gdk_gc_new
argument_list|(
name|logo_pixmap
argument_list|)
expr_stmt|;
name|gtk_preview_put
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|,
name|logo_pixmap
argument_list|,
name|gc
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|logo_width
argument_list|,
name|logo_height
argument_list|)
expr_stmt|;
name|gdk_gc_destroy
argument_list|(
name|gc
argument_list|)
expr_stmt|;
name|gtk_widget_unref
argument_list|(
name|preview
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pixelrow
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
name|dissolve_width
operator|=
operator|(
name|logo_width
operator|/
name|ANIMATION_SIZE
operator|)
operator|+
operator|(
name|logo_width
operator|%
name|ANIMATION_SIZE
operator|==
literal|0
condition|?
literal|0
else|:
literal|1
operator|)
expr_stmt|;
name|dissolve_height
operator|=
operator|(
name|logo_height
operator|/
name|ANIMATION_SIZE
operator|)
operator|+
operator|(
name|logo_height
operator|%
name|ANIMATION_SIZE
operator|==
literal|0
condition|?
literal|0
else|:
literal|1
operator|)
expr_stmt|;
name|dissolve_map
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|dissolve_width
operator|*
name|dissolve_height
argument_list|)
expr_stmt|;
name|srand
argument_list|(
name|time
argument_list|(
name|NULL
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
operator|,
name|k
operator|=
literal|0
init|;
name|i
operator|<
name|dissolve_height
condition|;
name|i
operator|++
control|)
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|dissolve_width
condition|;
name|j
operator|++
operator|,
name|k
operator|++
control|)
name|dissolve_map
index|[
name|k
index|]
operator|=
name|rand
argument_list|()
operator|%
name|ANIMATION_STEPS
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|about_dialog_destroy ()
name|about_dialog_destroy
parameter_list|()
block|{
name|about_dialog
operator|=
name|NULL
expr_stmt|;
name|about_dialog_unmap
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|about_dialog_unmap ()
name|about_dialog_unmap
parameter_list|()
block|{
if|if
condition|(
name|timer
condition|)
block|{
name|gtk_timeout_remove
argument_list|(
name|timer
argument_list|)
expr_stmt|;
name|timer
operator|=
literal|0
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|int
DECL|function|about_dialog_logo_expose (GtkWidget * widget,GdkEventExpose * event)
name|about_dialog_logo_expose
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
if|if
condition|(
name|do_animation
condition|)
block|{
if|if
condition|(
operator|!
name|timer
condition|)
block|{
name|about_dialog_timer
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|timer
operator|=
name|gtk_timeout_add
argument_list|(
literal|75
argument_list|,
name|about_dialog_timer
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
comment|/* If we draw beyond the boundaries of the pixmap, then X 	 will generate an expose area for those areas, starting 	 an infinite cycle. We now set allow_grow = FALSE, so 	 the drawing area can never be bigger than the preview.          Otherwise, it would be necessary to intersect event->area          with the pixmap boundary rectangle. */
name|gdk_draw_pixmap
argument_list|(
name|widget
operator|->
name|window
argument_list|,
name|widget
operator|->
name|style
operator|->
name|black_gc
argument_list|,
name|logo_pixmap
argument_list|,
name|event
operator|->
name|area
operator|.
name|x
argument_list|,
name|event
operator|->
name|area
operator|.
name|y
argument_list|,
name|event
operator|->
name|area
operator|.
name|x
argument_list|,
name|event
operator|->
name|area
operator|.
name|y
argument_list|,
name|event
operator|->
name|area
operator|.
name|width
argument_list|,
name|event
operator|->
name|area
operator|.
name|height
argument_list|)
expr_stmt|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|int
DECL|function|about_dialog_button (GtkWidget * widget,GdkEventButton * event)
name|about_dialog_button
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|)
block|{
if|if
condition|(
name|timer
condition|)
name|gtk_timeout_remove
argument_list|(
name|timer
argument_list|)
expr_stmt|;
name|timer
operator|=
literal|0
expr_stmt|;
name|frame
operator|=
literal|0
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|about_dialog
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|int
DECL|function|about_dialog_timer (gpointer data)
name|about_dialog_timer
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|,
name|k
decl_stmt|;
name|gint
name|return_val
decl_stmt|;
name|return_val
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|do_animation
condition|)
block|{
if|if
condition|(
name|logo_area
operator|->
name|allocation
operator|.
name|width
operator|!=
literal|1
condition|)
block|{
for|for
control|(
name|i
operator|=
literal|0
operator|,
name|k
operator|=
literal|0
init|;
name|i
operator|<
name|dissolve_height
condition|;
name|i
operator|++
control|)
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|dissolve_width
condition|;
name|j
operator|++
operator|,
name|k
operator|++
control|)
if|if
condition|(
name|frame
operator|==
name|dissolve_map
index|[
name|k
index|]
condition|)
block|{
name|gdk_draw_pixmap
argument_list|(
name|logo_area
operator|->
name|window
argument_list|,
name|logo_area
operator|->
name|style
operator|->
name|black_gc
argument_list|,
name|logo_pixmap
argument_list|,
name|j
operator|*
name|ANIMATION_SIZE
argument_list|,
name|i
operator|*
name|ANIMATION_SIZE
argument_list|,
name|j
operator|*
name|ANIMATION_SIZE
argument_list|,
name|i
operator|*
name|ANIMATION_SIZE
argument_list|,
name|ANIMATION_SIZE
argument_list|,
name|ANIMATION_SIZE
argument_list|)
expr_stmt|;
block|}
name|frame
operator|+=
literal|1
expr_stmt|;
if|if
condition|(
name|frame
operator|==
name|ANIMATION_STEPS
condition|)
block|{
name|do_animation
operator|=
name|FALSE
expr_stmt|;
name|do_scrolling
operator|=
name|TRUE
expr_stmt|;
name|frame
operator|=
literal|0
expr_stmt|;
name|timer
operator|=
name|gtk_timeout_add
argument_list|(
literal|75
argument_list|,
name|about_dialog_timer
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
block|}
block|}
if|if
condition|(
name|do_scrolling
condition|)
block|{
if|if
condition|(
operator|!
name|scroll_pixmap
condition|)
name|scroll_pixmap
operator|=
name|gdk_pixmap_new
argument_list|(
name|scroll_area
operator|->
name|window
argument_list|,
name|scroll_area
operator|->
name|allocation
operator|.
name|width
argument_list|,
name|scroll_area
operator|->
name|allocation
operator|.
name|height
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|scroll_state
condition|)
block|{
case|case
literal|1
case|:
name|scroll_state
operator|=
literal|2
expr_stmt|;
name|timer
operator|=
name|gtk_timeout_add
argument_list|(
literal|700
argument_list|,
name|about_dialog_timer
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|return_val
operator|=
name|FALSE
expr_stmt|;
break|break;
case|case
literal|2
case|:
name|scroll_state
operator|=
literal|3
expr_stmt|;
name|timer
operator|=
name|gtk_timeout_add
argument_list|(
literal|75
argument_list|,
name|about_dialog_timer
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|return_val
operator|=
name|FALSE
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|offset
operator|>
operator|(
name|scroll_text_widths
index|[
name|cur_scroll_text
index|]
operator|+
name|scroll_area
operator|->
name|allocation
operator|.
name|width
operator|)
condition|)
block|{
name|scroll_state
operator|=
literal|0
expr_stmt|;
name|cur_scroll_index
operator|+=
literal|1
expr_stmt|;
if|if
condition|(
name|cur_scroll_index
operator|==
name|nscroll_texts
condition|)
name|cur_scroll_index
operator|=
literal|0
expr_stmt|;
name|cur_scroll_text
operator|=
name|shuffle_array
index|[
name|cur_scroll_index
index|]
expr_stmt|;
name|offset
operator|=
literal|0
expr_stmt|;
block|}
name|gdk_draw_rectangle
argument_list|(
name|scroll_pixmap
argument_list|,
name|scroll_area
operator|->
name|style
operator|->
name|white_gc
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|scroll_area
operator|->
name|allocation
operator|.
name|width
argument_list|,
name|scroll_area
operator|->
name|allocation
operator|.
name|height
argument_list|)
expr_stmt|;
name|gdk_draw_string
argument_list|(
name|scroll_pixmap
argument_list|,
name|scroll_area
operator|->
name|style
operator|->
name|font
argument_list|,
name|scroll_area
operator|->
name|style
operator|->
name|black_gc
argument_list|,
name|scroll_area
operator|->
name|allocation
operator|.
name|width
operator|-
name|offset
argument_list|,
name|scroll_area
operator|->
name|style
operator|->
name|font
operator|->
name|ascent
argument_list|,
name|scroll_text
index|[
name|cur_scroll_text
index|]
argument_list|)
expr_stmt|;
name|gdk_draw_pixmap
argument_list|(
name|scroll_area
operator|->
name|window
argument_list|,
name|scroll_area
operator|->
name|style
operator|->
name|black_gc
argument_list|,
name|scroll_pixmap
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|scroll_area
operator|->
name|allocation
operator|.
name|width
argument_list|,
name|scroll_area
operator|->
name|allocation
operator|.
name|height
argument_list|)
expr_stmt|;
name|offset
operator|+=
literal|15
expr_stmt|;
if|if
condition|(
name|scroll_state
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|offset
operator|>
operator|(
operator|(
name|scroll_area
operator|->
name|allocation
operator|.
name|width
operator|+
name|scroll_text_widths
index|[
name|cur_scroll_text
index|]
operator|)
operator|/
literal|2
operator|)
condition|)
block|{
name|scroll_state
operator|=
literal|1
expr_stmt|;
name|offset
operator|=
operator|(
name|scroll_area
operator|->
name|allocation
operator|.
name|width
operator|+
name|scroll_text_widths
index|[
name|cur_scroll_text
index|]
operator|)
operator|/
literal|2
expr_stmt|;
block|}
block|}
block|}
return|return
name|return_val
return|;
block|}
end_function

end_unit

