begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|<math.h>
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"color_panel.h"
end_include

begin_include
include|#
directive|include
file|"color_notebook.h"
end_include

begin_include
include|#
directive|include
file|"colormaps.h"
end_include

begin_include
include|#
directive|include
file|"gimpdnd.h"
end_include

begin_define
DECL|macro|EVENT_MASK
define|#
directive|define
name|EVENT_MASK
value|GDK_EXPOSURE_MASK | GDK_BUTTON_PRESS_MASK | \                     GDK_BUTTON_RELEASE_MASK | GDK_ENTER_NOTIFY_MASK | \                     GDK_LEAVE_NOTIFY_MASK
end_define

begin_typedef
DECL|typedef|ColorPanelPrivate
typedef|typedef
name|struct
name|_ColorPanelPrivate
name|ColorPanelPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_ColorPanelPrivate
struct|struct
name|_ColorPanelPrivate
block|{
DECL|member|drawing_area
name|GtkWidget
modifier|*
name|drawing_area
decl_stmt|;
DECL|member|gc
name|GdkGC
modifier|*
name|gc
decl_stmt|;
DECL|member|button_down
name|gboolean
name|button_down
decl_stmt|;
DECL|member|color_notebook
name|ColorNotebookP
name|color_notebook
decl_stmt|;
DECL|member|color_notebook_active
name|gboolean
name|color_notebook_active
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|color_panel_draw
parameter_list|(
name|ColorPanel
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|color_panel_events
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|GdkEvent
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|color_panel_select_callback
parameter_list|(
name|gint
parameter_list|,
name|gint
parameter_list|,
name|gint
parameter_list|,
name|ColorNotebookState
parameter_list|,
name|void
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|color_panel_drag_color
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|guchar
modifier|*
parameter_list|,
name|guchar
modifier|*
parameter_list|,
name|guchar
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|color_panel_drop_color
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|guchar
parameter_list|,
name|guchar
parameter_list|,
name|guchar
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  dnd stuff  */
end_comment

begin_decl_stmt
DECL|variable|color_panel_target_table
specifier|static
name|GtkTargetEntry
name|color_panel_target_table
index|[]
init|=
block|{
name|GIMP_TARGET_COLOR
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|n_color_panel_targets
specifier|static
name|guint
name|n_color_panel_targets
init|=
operator|(
sizeof|sizeof
argument_list|(
name|color_panel_target_table
argument_list|)
operator|/
sizeof|sizeof
argument_list|(
name|color_panel_target_table
index|[
literal|0
index|]
argument_list|)
operator|)
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|ColorPanel
modifier|*
DECL|function|color_panel_new (guchar * initial,gint width,gint height)
name|color_panel_new
parameter_list|(
name|guchar
modifier|*
name|initial
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
name|ColorPanel
modifier|*
name|color_panel
decl_stmt|;
name|ColorPanelPrivate
modifier|*
name|private
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|private
operator|=
name|g_new
argument_list|(
name|ColorPanelPrivate
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|private
operator|->
name|color_notebook
operator|=
name|NULL
expr_stmt|;
name|private
operator|->
name|color_notebook_active
operator|=
name|FALSE
expr_stmt|;
name|private
operator|->
name|gc
operator|=
name|NULL
expr_stmt|;
name|private
operator|->
name|button_down
operator|=
name|FALSE
expr_stmt|;
name|color_panel
operator|=
name|g_new
argument_list|(
name|ColorPanel
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|color_panel
operator|->
name|private_part
operator|=
name|private
expr_stmt|;
comment|/*  set the initial color  */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|3
condition|;
name|i
operator|++
control|)
name|color_panel
operator|->
name|color
index|[
name|i
index|]
operator|=
operator|(
name|initial
operator|)
condition|?
name|initial
index|[
name|i
index|]
else|:
literal|0
expr_stmt|;
name|color_panel
operator|->
name|color_panel_widget
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
name|color_panel
operator|->
name|color_panel_widget
argument_list|)
argument_list|,
name|GTK_SHADOW_IN
argument_list|)
expr_stmt|;
comment|/*  drawing area  */
name|private
operator|->
name|drawing_area
operator|=
name|gtk_drawing_area_new
argument_list|()
expr_stmt|;
name|gtk_drawing_area_size
argument_list|(
name|GTK_DRAWING_AREA
argument_list|(
name|private
operator|->
name|drawing_area
argument_list|)
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|gtk_widget_set_events
argument_list|(
name|private
operator|->
name|drawing_area
argument_list|,
name|EVENT_MASK
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|private
operator|->
name|drawing_area
argument_list|)
argument_list|,
literal|"event"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|color_panel_events
argument_list|,
name|color_panel
argument_list|)
expr_stmt|;
name|gtk_object_set_user_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|private
operator|->
name|drawing_area
argument_list|)
argument_list|,
name|color_panel
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|color_panel
operator|->
name|color_panel_widget
argument_list|)
argument_list|,
name|private
operator|->
name|drawing_area
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|private
operator|->
name|drawing_area
argument_list|)
expr_stmt|;
comment|/*  dnd stuff  */
name|gtk_drag_source_set
argument_list|(
name|private
operator|->
name|drawing_area
argument_list|,
name|GDK_BUTTON1_MASK
operator||
name|GDK_BUTTON3_MASK
argument_list|,
name|color_panel_target_table
argument_list|,
name|n_color_panel_targets
argument_list|,
name|GDK_ACTION_COPY
operator||
name|GDK_ACTION_MOVE
argument_list|)
expr_stmt|;
name|gimp_dnd_color_source_set
argument_list|(
name|private
operator|->
name|drawing_area
argument_list|,
name|color_panel_drag_color
argument_list|,
name|color_panel
argument_list|)
expr_stmt|;
name|gtk_drag_dest_set
argument_list|(
name|private
operator|->
name|drawing_area
argument_list|,
name|GTK_DEST_DEFAULT_HIGHLIGHT
operator||
name|GTK_DEST_DEFAULT_MOTION
operator||
name|GTK_DEST_DEFAULT_DROP
argument_list|,
name|color_panel_target_table
argument_list|,
name|n_color_panel_targets
argument_list|,
name|GDK_ACTION_COPY
argument_list|)
expr_stmt|;
name|gimp_dnd_color_dest_set
argument_list|(
name|private
operator|->
name|drawing_area
argument_list|,
name|color_panel_drop_color
argument_list|,
name|color_panel
argument_list|)
expr_stmt|;
return|return
name|color_panel
return|;
block|}
end_function

begin_function
name|void
DECL|function|color_panel_free (ColorPanel * color_panel)
name|color_panel_free
parameter_list|(
name|ColorPanel
modifier|*
name|color_panel
parameter_list|)
block|{
name|ColorPanelPrivate
modifier|*
name|private
decl_stmt|;
name|private
operator|=
operator|(
name|ColorPanelPrivate
operator|*
operator|)
name|color_panel
operator|->
name|private_part
expr_stmt|;
comment|/* make sure we hide and free color_notebook */
if|if
condition|(
name|private
operator|->
name|color_notebook
condition|)
block|{
name|color_notebook_hide
argument_list|(
name|private
operator|->
name|color_notebook
argument_list|)
expr_stmt|;
name|color_notebook_free
argument_list|(
name|private
operator|->
name|color_notebook
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|private
operator|->
name|gc
condition|)
name|gdk_gc_destroy
argument_list|(
name|private
operator|->
name|gc
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|color_panel
operator|->
name|private_part
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|color_panel
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|color_panel_set_color (ColorPanel * color_panel,guchar * col)
name|color_panel_set_color
parameter_list|(
name|ColorPanel
modifier|*
name|color_panel
parameter_list|,
name|guchar
modifier|*
name|col
parameter_list|)
block|{
name|ColorPanelPrivate
modifier|*
name|private
init|=
name|color_panel
operator|->
name|private_part
decl_stmt|;
name|color_panel
operator|->
name|color
index|[
literal|0
index|]
operator|=
name|col
index|[
literal|0
index|]
expr_stmt|;
name|color_panel
operator|->
name|color
index|[
literal|1
index|]
operator|=
name|col
index|[
literal|1
index|]
expr_stmt|;
name|color_panel
operator|->
name|color
index|[
literal|2
index|]
operator|=
name|col
index|[
literal|2
index|]
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|color_notebook_active
condition|)
name|color_notebook_set_color
argument_list|(
name|private
operator|->
name|color_notebook
argument_list|,
name|col
index|[
literal|0
index|]
argument_list|,
name|col
index|[
literal|1
index|]
argument_list|,
name|col
index|[
literal|2
index|]
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|gc
condition|)
name|color_panel_draw
argument_list|(
name|color_panel
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
DECL|function|color_panel_draw (ColorPanel * color_panel)
name|color_panel_draw
parameter_list|(
name|ColorPanel
modifier|*
name|color_panel
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|ColorPanelPrivate
modifier|*
name|private
decl_stmt|;
name|GdkColor
name|fg
decl_stmt|;
name|private
operator|=
operator|(
name|ColorPanelPrivate
operator|*
operator|)
name|color_panel
operator|->
name|private_part
expr_stmt|;
name|widget
operator|=
name|private
operator|->
name|drawing_area
expr_stmt|;
name|fg
operator|.
name|pixel
operator|=
name|old_color_pixel
expr_stmt|;
name|store_color
argument_list|(
operator|&
name|fg
operator|.
name|pixel
argument_list|,
name|color_panel
operator|->
name|color
index|[
literal|0
index|]
argument_list|,
name|color_panel
operator|->
name|color
index|[
literal|1
index|]
argument_list|,
name|color_panel
operator|->
name|color
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
name|gdk_gc_set_foreground
argument_list|(
name|private
operator|->
name|gc
argument_list|,
operator|&
name|fg
argument_list|)
expr_stmt|;
name|gdk_draw_rectangle
argument_list|(
name|widget
operator|->
name|window
argument_list|,
name|private
operator|->
name|gc
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|0
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
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|color_panel_events (GtkWidget * widget,GdkEvent * event)
name|color_panel_events
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
name|ColorPanel
modifier|*
name|color_panel
decl_stmt|;
name|ColorPanelPrivate
modifier|*
name|private
decl_stmt|;
name|color_panel
operator|=
operator|(
name|ColorPanel
operator|*
operator|)
name|gtk_object_get_user_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|=
operator|(
name|ColorPanelPrivate
operator|*
operator|)
name|color_panel
operator|->
name|private_part
expr_stmt|;
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
if|if
condition|(
operator|!
name|private
operator|->
name|gc
condition|)
name|private
operator|->
name|gc
operator|=
name|gdk_gc_new
argument_list|(
name|widget
operator|->
name|window
argument_list|)
expr_stmt|;
name|color_panel_draw
argument_list|(
name|color_panel
argument_list|)
expr_stmt|;
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
name|private
operator|->
name|button_down
operator|=
name|TRUE
expr_stmt|;
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
operator|&&
name|private
operator|->
name|button_down
condition|)
block|{
if|if
condition|(
operator|!
name|private
operator|->
name|color_notebook
condition|)
block|{
name|private
operator|->
name|color_notebook
operator|=
name|color_notebook_new
argument_list|(
name|color_panel
operator|->
name|color
index|[
literal|0
index|]
argument_list|,
name|color_panel
operator|->
name|color
index|[
literal|1
index|]
argument_list|,
name|color_panel
operator|->
name|color
index|[
literal|2
index|]
argument_list|,
name|color_panel_select_callback
argument_list|,
name|color_panel
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|private
operator|->
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
name|private
operator|->
name|color_notebook_active
condition|)
block|{
name|color_notebook_show
argument_list|(
name|private
operator|->
name|color_notebook
argument_list|)
expr_stmt|;
name|private
operator|->
name|color_notebook_active
operator|=
name|TRUE
expr_stmt|;
block|}
name|color_notebook_set_color
argument_list|(
name|private
operator|->
name|color_notebook
argument_list|,
name|color_panel
operator|->
name|color
index|[
literal|0
index|]
argument_list|,
name|color_panel
operator|->
name|color
index|[
literal|1
index|]
argument_list|,
name|color_panel
operator|->
name|color
index|[
literal|2
index|]
argument_list|,
literal|1
argument_list|)
expr_stmt|;
block|}
name|private
operator|->
name|button_down
operator|=
name|FALSE
expr_stmt|;
block|}
break|break;
case|case
name|GDK_LEAVE_NOTIFY
case|:
name|private
operator|->
name|button_down
operator|=
name|FALSE
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
DECL|function|color_panel_select_callback (gint r,gint g,gint b,ColorNotebookState state,void * client_data)
name|color_panel_select_callback
parameter_list|(
name|gint
name|r
parameter_list|,
name|gint
name|g
parameter_list|,
name|gint
name|b
parameter_list|,
name|ColorNotebookState
name|state
parameter_list|,
name|void
modifier|*
name|client_data
parameter_list|)
block|{
name|ColorPanel
modifier|*
name|color_panel
decl_stmt|;
name|ColorPanelPrivate
modifier|*
name|private
decl_stmt|;
name|color_panel
operator|=
operator|(
name|ColorPanel
operator|*
operator|)
name|client_data
expr_stmt|;
name|private
operator|=
operator|(
name|ColorPanelPrivate
operator|*
operator|)
name|color_panel
operator|->
name|private_part
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|color_notebook
condition|)
block|{
switch|switch
condition|(
name|state
condition|)
block|{
case|case
name|COLOR_NOTEBOOK_UPDATE
case|:
break|break;
case|case
name|COLOR_NOTEBOOK_OK
case|:
name|color_panel
operator|->
name|color
index|[
literal|0
index|]
operator|=
name|r
expr_stmt|;
name|color_panel
operator|->
name|color
index|[
literal|1
index|]
operator|=
name|g
expr_stmt|;
name|color_panel
operator|->
name|color
index|[
literal|2
index|]
operator|=
name|b
expr_stmt|;
name|color_panel_draw
argument_list|(
name|color_panel
argument_list|)
expr_stmt|;
comment|/* Fallthrough */
case|case
name|COLOR_NOTEBOOK_CANCEL
case|:
name|color_notebook_hide
argument_list|(
name|private
operator|->
name|color_notebook
argument_list|)
expr_stmt|;
name|private
operator|->
name|color_notebook_active
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|color_panel_drag_color (GtkWidget * widget,guchar * r,guchar * g,guchar * b,gpointer data)
name|color_panel_drag_color
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|guchar
modifier|*
name|r
parameter_list|,
name|guchar
modifier|*
name|g
parameter_list|,
name|guchar
modifier|*
name|b
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|ColorPanel
modifier|*
name|color_panel
init|=
name|data
decl_stmt|;
operator|*
name|r
operator|=
name|color_panel
operator|->
name|color
index|[
literal|0
index|]
expr_stmt|;
operator|*
name|g
operator|=
name|color_panel
operator|->
name|color
index|[
literal|1
index|]
expr_stmt|;
operator|*
name|b
operator|=
name|color_panel
operator|->
name|color
index|[
literal|2
index|]
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|color_panel_drop_color (GtkWidget * widget,guchar r,guchar g,guchar b,gpointer data)
name|color_panel_drop_color
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|guchar
name|r
parameter_list|,
name|guchar
name|g
parameter_list|,
name|guchar
name|b
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|ColorPanel
modifier|*
name|color_panel
init|=
name|data
decl_stmt|;
name|ColorPanelPrivate
modifier|*
name|private
init|=
operator|(
name|ColorPanelPrivate
operator|*
operator|)
name|color_panel
operator|->
name|private_part
decl_stmt|;
name|color_panel
operator|->
name|color
index|[
literal|0
index|]
operator|=
name|r
expr_stmt|;
name|color_panel
operator|->
name|color
index|[
literal|1
index|]
operator|=
name|g
expr_stmt|;
name|color_panel
operator|->
name|color
index|[
literal|2
index|]
operator|=
name|b
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|color_notebook_active
condition|)
name|color_notebook_set_color
argument_list|(
name|private
operator|->
name|color_notebook
argument_list|,
name|r
argument_list|,
name|g
argument_list|,
name|b
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|color_panel_draw
argument_list|(
name|color_panel
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

