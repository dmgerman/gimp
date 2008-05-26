begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This is a plug-in for GIMP.  *  * Generates images containing vector type drawings.  *  * Copyright (C) 1997 Andy Thomas  alt@picnic.demon.co.uk  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpui.h>
end_include

begin_include
include|#
directive|include
file|"gfig.h"
end_include

begin_include
include|#
directive|include
file|"gfig-grid.h"
end_include

begin_include
include|#
directive|include
file|"gfig-dobject.h"
end_include

begin_include
include|#
directive|include
file|"gfig-preview.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_define
DECL|macro|PREVIEW_MASK
define|#
directive|define
name|PREVIEW_MASK
value|(GDK_EXPOSURE_MASK       | \                        GDK_POINTER_MOTION_MASK | \                        GDK_BUTTON_PRESS_MASK   | \                        GDK_BUTTON_RELEASE_MASK | \                        GDK_BUTTON_MOTION_MASK  | \                        GDK_KEY_PRESS_MASK      | \                        GDK_KEY_RELEASE_MASK)
end_define

begin_decl_stmt
DECL|variable|x_pos_val
specifier|static
name|gint
name|x_pos_val
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|y_pos_val
specifier|static
name|gint
name|y_pos_val
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|pos_tag
specifier|static
name|gint
name|pos_tag
init|=
operator|-
literal|1
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|status_label_dname
name|GtkWidget
modifier|*
name|status_label_dname
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|status_label_fname
name|GtkWidget
modifier|*
name|status_label_fname
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|pos_label
specifier|static
name|GtkWidget
modifier|*
name|pos_label
decl_stmt|;
end_decl_stmt

begin_comment
DECL|variable|pos_label
comment|/* XY pos marker */
end_comment

begin_function_decl
specifier|static
name|void
name|gfig_preview_realize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gfig_preview_events
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|gfig_invscale_x
parameter_list|(
name|gint
name|x
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|gfig_invscale_y
parameter_list|(
name|gint
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|gfig_pos_labels
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|make_pos_info
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gfig_pos_update
parameter_list|(
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gfig_pos_update_labels
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|GtkWidget
modifier|*
DECL|function|make_preview (void)
name|make_preview
parameter_list|(
name|void
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
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|ruler
decl_stmt|;
name|gfig_context
operator|->
name|preview
operator|=
name|gtk_drawing_area_new
argument_list|()
expr_stmt|;
name|gtk_widget_set_events
argument_list|(
name|GTK_WIDGET
argument_list|(
name|gfig_context
operator|->
name|preview
argument_list|)
argument_list|,
name|PREVIEW_MASK
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gfig_context
operator|->
name|preview
argument_list|,
literal|"realize"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gfig_preview_realize
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gfig_context
operator|->
name|preview
argument_list|,
literal|"event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gfig_preview_events
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect_after
argument_list|(
name|gfig_context
operator|->
name|preview
argument_list|,
literal|"expose-event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gfig_preview_expose
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|gfig_context
operator|->
name|preview
argument_list|,
name|preview_width
argument_list|,
name|preview_height
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
name|gfig_context
operator|->
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
name|ruler
operator|=
name|gimp_hruler_new
argument_list|()
expr_stmt|;
name|gimp_ruler_set_range
argument_list|(
name|GIMP_RULER
argument_list|(
name|ruler
argument_list|)
argument_list|,
literal|0
argument_list|,
name|preview_width
argument_list|,
literal|0
argument_list|,
name|PREVIEW_SIZE
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|gfig_context
operator|->
name|preview
argument_list|,
literal|"motion-notify-event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|GTK_WIDGET_CLASS
argument_list|(
name|G_OBJECT_GET_CLASS
argument_list|(
name|ruler
argument_list|)
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
name|ruler
operator|=
name|gimp_vruler_new
argument_list|()
expr_stmt|;
name|gimp_ruler_set_range
argument_list|(
name|GIMP_RULER
argument_list|(
name|ruler
argument_list|)
argument_list|,
literal|0
argument_list|,
name|preview_height
argument_list|,
literal|0
argument_list|,
name|PREVIEW_SIZE
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|gfig_context
operator|->
name|preview
argument_list|,
literal|"motion-notify-event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|GTK_WIDGET_CLASS
argument_list|(
name|G_OBJECT_GET_CLASS
argument_list|(
name|ruler
argument_list|)
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
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|frame
argument_list|,
name|FALSE
argument_list|,
name|FALSE
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
name|hbox
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|frame
operator|=
name|make_pos_info
argument_list|()
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|frame
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
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
return|return
name|vbox
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gfig_preview_realize (GtkWidget * widget)
name|gfig_preview_realize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|GdkDisplay
modifier|*
name|display
init|=
name|gtk_widget_get_display
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|gdk_window_set_cursor
argument_list|(
name|gfig_context
operator|->
name|preview
operator|->
name|window
argument_list|,
name|gdk_cursor_new_for_display
argument_list|(
name|display
argument_list|,
name|GDK_CROSSHAIR
argument_list|)
argument_list|)
expr_stmt|;
name|gfig_grid_colours
argument_list|(
name|widget
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|draw_background (void)
name|draw_background
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
operator|!
name|back_pixbuf
condition|)
name|back_pixbuf
operator|=
name|gimp_image_get_thumbnail
argument_list|(
name|gfig_context
operator|->
name|image_id
argument_list|,
name|preview_width
argument_list|,
name|preview_height
argument_list|,
name|GIMP_PIXBUF_LARGE_CHECKS
argument_list|)
expr_stmt|;
if|if
condition|(
name|back_pixbuf
condition|)
name|gdk_draw_pixbuf
argument_list|(
name|gfig_context
operator|->
name|preview
operator|->
name|window
argument_list|,
name|gfig_context
operator|->
name|preview
operator|->
name|style
operator|->
name|fg_gc
index|[
name|GTK_STATE_NORMAL
index|]
argument_list|,
name|back_pixbuf
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|gdk_pixbuf_get_width
argument_list|(
name|back_pixbuf
argument_list|)
argument_list|,
name|gdk_pixbuf_get_height
argument_list|(
name|back_pixbuf
argument_list|)
argument_list|,
name|GDK_RGB_DITHER_NONE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gfig_preview_expose (GtkWidget * widget,GdkEvent * event)
name|gfig_preview_expose
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
name|gdk_window_clear
argument_list|(
name|gfig_context
operator|->
name|preview
operator|->
name|window
argument_list|)
expr_stmt|;
if|if
condition|(
name|gfig_context
operator|->
name|show_background
condition|)
name|draw_background
argument_list|()
expr_stmt|;
name|draw_grid
argument_list|()
expr_stmt|;
name|draw_objects
argument_list|(
name|gfig_context
operator|->
name|current_obj
operator|->
name|obj_list
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gfig_preview_events (GtkWidget * widget,GdkEvent * event)
name|gfig_preview_events
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
name|GdkEventMotion
modifier|*
name|mevent
decl_stmt|;
name|GdkPoint
name|point
decl_stmt|;
specifier|static
name|gint
name|tmp_show_single
init|=
literal|0
decl_stmt|;
switch|switch
condition|(
name|event
operator|->
name|type
condition|)
block|{
case|case
name|GDK_EXPOSE
case|:
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
name|point
operator|.
name|x
operator|=
name|bevent
operator|->
name|x
expr_stmt|;
name|point
operator|.
name|y
operator|=
name|bevent
operator|->
name|y
expr_stmt|;
name|g_assert
argument_list|(
name|need_to_scale
operator|==
literal|0
argument_list|)
expr_stmt|;
comment|/* If not out of step some how */
comment|/* Start drawing of object */
if|if
condition|(
name|selvals
operator|.
name|otype
operator|>=
name|MOVE_OBJ
condition|)
block|{
if|if
condition|(
operator|!
name|selvals
operator|.
name|scaletoimage
condition|)
block|{
name|point
operator|.
name|x
operator|=
name|gfig_invscale_x
argument_list|(
name|point
operator|.
name|x
argument_list|)
expr_stmt|;
name|point
operator|.
name|y
operator|=
name|gfig_invscale_y
argument_list|(
name|point
operator|.
name|y
argument_list|)
expr_stmt|;
block|}
name|object_operation_start
argument_list|(
operator|&
name|point
argument_list|,
name|bevent
operator|->
name|state
operator|&
name|GDK_SHIFT_MASK
argument_list|)
expr_stmt|;
comment|/* If constraining save start pnt */
if|if
condition|(
name|selvals
operator|.
name|opts
operator|.
name|snap2grid
condition|)
block|{
comment|/* Save point to constained point ... if button 3 down */
if|if
condition|(
name|bevent
operator|->
name|button
operator|==
literal|3
condition|)
block|{
name|find_grid_pos
argument_list|(
operator|&
name|point
argument_list|,
operator|&
name|point
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
block|}
else|else
block|{
if|if
condition|(
name|selvals
operator|.
name|opts
operator|.
name|snap2grid
condition|)
block|{
if|if
condition|(
name|bevent
operator|->
name|button
operator|==
literal|3
condition|)
block|{
name|find_grid_pos
argument_list|(
operator|&
name|point
argument_list|,
operator|&
name|point
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|find_grid_pos
argument_list|(
operator|&
name|point
argument_list|,
operator|&
name|point
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
name|object_start
argument_list|(
operator|&
name|point
argument_list|,
name|bevent
operator|->
name|state
operator|&
name|GDK_SHIFT_MASK
argument_list|)
expr_stmt|;
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
name|point
operator|.
name|x
operator|=
name|bevent
operator|->
name|x
expr_stmt|;
name|point
operator|.
name|y
operator|=
name|bevent
operator|->
name|y
expr_stmt|;
if|if
condition|(
name|selvals
operator|.
name|opts
operator|.
name|snap2grid
condition|)
name|find_grid_pos
argument_list|(
operator|&
name|point
argument_list|,
operator|&
name|point
argument_list|,
name|bevent
operator|->
name|button
operator|==
literal|3
argument_list|)
expr_stmt|;
comment|/* Still got shift down ?*/
if|if
condition|(
name|selvals
operator|.
name|otype
operator|>=
name|MOVE_OBJ
condition|)
block|{
if|if
condition|(
operator|!
name|selvals
operator|.
name|scaletoimage
condition|)
block|{
name|point
operator|.
name|x
operator|=
name|gfig_invscale_x
argument_list|(
name|point
operator|.
name|x
argument_list|)
expr_stmt|;
name|point
operator|.
name|y
operator|=
name|gfig_invscale_y
argument_list|(
name|point
operator|.
name|y
argument_list|)
expr_stmt|;
block|}
name|object_operation_end
argument_list|(
operator|&
name|point
argument_list|,
name|bevent
operator|->
name|state
operator|&
name|GDK_SHIFT_MASK
argument_list|)
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|obj_creating
condition|)
block|{
name|object_end
argument_list|(
operator|&
name|point
argument_list|,
name|bevent
operator|->
name|state
operator|&
name|GDK_SHIFT_MASK
argument_list|)
expr_stmt|;
block|}
else|else
break|break;
block|}
name|gfig_paint_callback
argument_list|()
expr_stmt|;
break|break;
case|case
name|GDK_MOTION_NOTIFY
case|:
name|mevent
operator|=
operator|(
name|GdkEventMotion
operator|*
operator|)
name|event
expr_stmt|;
name|point
operator|.
name|x
operator|=
name|mevent
operator|->
name|x
expr_stmt|;
name|point
operator|.
name|y
operator|=
name|mevent
operator|->
name|y
expr_stmt|;
if|if
condition|(
name|selvals
operator|.
name|opts
operator|.
name|snap2grid
condition|)
name|find_grid_pos
argument_list|(
operator|&
name|point
argument_list|,
operator|&
name|point
argument_list|,
name|mevent
operator|->
name|state
operator|&
name|GDK_BUTTON3_MASK
argument_list|)
expr_stmt|;
if|if
condition|(
name|selvals
operator|.
name|otype
operator|>=
name|MOVE_OBJ
condition|)
block|{
comment|/* Moving objects around */
if|if
condition|(
operator|!
name|selvals
operator|.
name|scaletoimage
condition|)
block|{
name|point
operator|.
name|x
operator|=
name|gfig_invscale_x
argument_list|(
name|point
operator|.
name|x
argument_list|)
expr_stmt|;
name|point
operator|.
name|y
operator|=
name|gfig_invscale_y
argument_list|(
name|point
operator|.
name|y
argument_list|)
expr_stmt|;
block|}
name|object_operation
argument_list|(
operator|&
name|point
argument_list|,
name|mevent
operator|->
name|state
operator|&
name|GDK_SHIFT_MASK
argument_list|)
expr_stmt|;
name|gfig_pos_update
argument_list|(
name|point
operator|.
name|x
argument_list|,
name|point
operator|.
name|y
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
if|if
condition|(
name|obj_creating
condition|)
block|{
name|obj_creating
operator|->
name|class
operator|->
name|update
argument_list|(
operator|&
name|point
argument_list|)
expr_stmt|;
block|}
name|gfig_pos_update
argument_list|(
name|point
operator|.
name|x
argument_list|,
name|point
operator|.
name|y
argument_list|)
expr_stmt|;
break|break;
case|case
name|GDK_KEY_PRESS
case|:
if|if
condition|(
operator|(
name|tmp_show_single
operator|=
name|obj_show_single
operator|)
operator|!=
operator|-
literal|1
condition|)
block|{
name|obj_show_single
operator|=
operator|-
literal|1
expr_stmt|;
name|draw_grid_clear
argument_list|()
expr_stmt|;
block|}
break|break;
case|case
name|GDK_KEY_RELEASE
case|:
if|if
condition|(
name|tmp_show_single
operator|!=
operator|-
literal|1
condition|)
block|{
name|obj_show_single
operator|=
name|tmp_show_single
expr_stmt|;
name|draw_grid_clear
argument_list|()
expr_stmt|;
block|}
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
name|GtkWidget
modifier|*
DECL|function|make_pos_info (void)
name|make_pos_info
parameter_list|(
name|void
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Object Details"
argument_list|)
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|TRUE
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|hbox
argument_list|)
expr_stmt|;
comment|/* Add labels */
name|label
operator|=
name|gfig_pos_labels
argument_list|()
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|label
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gfig_pos_enable
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|#
directive|if
literal|0
block|label = gfig_obj_size_label ();   gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, FALSE, 0);
endif|#
directive|endif
comment|/* 0 */
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
return|return
name|frame
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|gfig_invscale_x (gint x)
name|gfig_invscale_x
parameter_list|(
name|gint
name|x
parameter_list|)
block|{
if|if
condition|(
operator|!
name|selvals
operator|.
name|scaletoimage
condition|)
return|return
call|(
name|gint
call|)
argument_list|(
name|x
operator|*
name|scale_x_factor
argument_list|)
return|;
else|else
return|return
name|x
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|gfig_invscale_y (gint y)
name|gfig_invscale_y
parameter_list|(
name|gint
name|y
parameter_list|)
block|{
if|if
condition|(
operator|!
name|selvals
operator|.
name|scaletoimage
condition|)
return|return
call|(
name|gint
call|)
argument_list|(
name|y
operator|*
name|scale_y_factor
argument_list|)
return|;
else|else
return|return
name|y
return|;
block|}
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|gfig_pos_labels (void)
name|gfig_pos_labels
parameter_list|(
name|void
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|gchar
name|buf
index|[
literal|256
index|]
decl_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
comment|/* Position labels */
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"XY position:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|label
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
name|label
argument_list|)
expr_stmt|;
name|pos_label
operator|=
name|gtk_label_new
argument_list|(
literal|""
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|pos_label
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
name|pos_label
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
literal|"%d, %d"
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|pos_label
argument_list|)
argument_list|,
name|buf
argument_list|)
expr_stmt|;
return|return
name|hbox
return|;
block|}
end_function

begin_function
name|void
DECL|function|gfig_pos_enable (GtkWidget * widget,gpointer data)
name|gfig_pos_enable
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gboolean
name|enable
init|=
name|selvals
operator|.
name|showpos
decl_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|GTK_WIDGET
argument_list|(
name|pos_label
argument_list|)
argument_list|,
name|enable
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gfig_pos_update_labels (gpointer data)
name|gfig_pos_update_labels
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
specifier|static
name|gchar
name|buf
index|[
literal|256
index|]
decl_stmt|;
name|pos_tag
operator|=
operator|-
literal|1
expr_stmt|;
name|g_snprintf
argument_list|(
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
literal|"%d, %d"
argument_list|,
name|x_pos_val
argument_list|,
name|y_pos_val
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|pos_label
argument_list|)
argument_list|,
name|buf
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gfig_pos_update (gint x,gint y)
name|gfig_pos_update
parameter_list|(
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
block|{
if|if
condition|(
operator|(
name|x_pos_val
operator|!=
name|x
operator|||
name|y_pos_val
operator|!=
name|y
operator|)
operator|&&
name|pos_tag
operator|==
operator|-
literal|1
operator|&&
name|selvals
operator|.
name|showpos
condition|)
block|{
name|x_pos_val
operator|=
name|x
expr_stmt|;
name|y_pos_val
operator|=
name|y
expr_stmt|;
name|gfig_pos_update_labels
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

