begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpview-popup.c  * Copyright (C) 2003-2006 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
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
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpviewable.h"
end_include

begin_include
include|#
directive|include
file|"gimpview.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewrenderer.h"
end_include

begin_include
include|#
directive|include
file|"gimpview-popup.h"
end_include

begin_define
DECL|macro|VIEW_POPUP_DELAY
define|#
directive|define
name|VIEW_POPUP_DELAY
value|150
end_define

begin_typedef
DECL|typedef|GimpViewPopup
typedef|typedef
name|struct
name|_GimpViewPopup
name|GimpViewPopup
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpViewPopup
struct|struct
name|_GimpViewPopup
block|{
DECL|member|widget
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
DECL|member|context
name|GimpContext
modifier|*
name|context
decl_stmt|;
DECL|member|viewable
name|GimpViewable
modifier|*
name|viewable
decl_stmt|;
DECL|member|popup_width
name|gint
name|popup_width
decl_stmt|;
DECL|member|popup_height
name|gint
name|popup_height
decl_stmt|;
DECL|member|dot_for_dot
name|gboolean
name|dot_for_dot
decl_stmt|;
DECL|member|button
name|gint
name|button
decl_stmt|;
DECL|member|button_x
name|gint
name|button_x
decl_stmt|;
DECL|member|button_y
name|gint
name|button_y
decl_stmt|;
DECL|member|timeout_id
name|guint
name|timeout_id
decl_stmt|;
DECL|member|popup
name|GtkWidget
modifier|*
name|popup
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
name|gimp_view_popup_hide
parameter_list|(
name|GimpViewPopup
modifier|*
name|popup
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_view_popup_button_release
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|GimpViewPopup
modifier|*
name|popup
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_view_popup_unmap
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpViewPopup
modifier|*
name|popup
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_view_popup_drag_begin
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|GimpViewPopup
modifier|*
name|popup
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_view_popup_timeout
parameter_list|(
name|GimpViewPopup
modifier|*
name|popup
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_view_popup_show (GtkWidget * widget,GdkEventButton * bevent,GimpContext * context,GimpViewable * viewable,gint view_width,gint view_height,gboolean dot_for_dot)
name|gimp_view_popup_show
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|view_width
parameter_list|,
name|gint
name|view_height
parameter_list|,
name|gboolean
name|dot_for_dot
parameter_list|)
block|{
name|GimpViewPopup
modifier|*
name|popup
decl_stmt|;
name|gint
name|popup_width
decl_stmt|;
name|gint
name|popup_height
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GTK_IS_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|bevent
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|context
operator|==
name|NULL
operator|||
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_VIEWABLE
argument_list|(
name|viewable
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_viewable_get_popup_size
argument_list|(
name|viewable
argument_list|,
name|view_width
argument_list|,
name|view_height
argument_list|,
name|dot_for_dot
argument_list|,
operator|&
name|popup_width
argument_list|,
operator|&
name|popup_height
argument_list|)
condition|)
return|return
name|FALSE
return|;
name|popup
operator|=
name|g_slice_new0
argument_list|(
name|GimpViewPopup
argument_list|)
expr_stmt|;
name|popup
operator|->
name|widget
operator|=
name|widget
expr_stmt|;
name|popup
operator|->
name|context
operator|=
name|context
expr_stmt|;
name|popup
operator|->
name|viewable
operator|=
name|viewable
expr_stmt|;
name|popup
operator|->
name|popup_width
operator|=
name|popup_width
expr_stmt|;
name|popup
operator|->
name|popup_height
operator|=
name|popup_height
expr_stmt|;
name|popup
operator|->
name|dot_for_dot
operator|=
name|dot_for_dot
expr_stmt|;
name|popup
operator|->
name|button
operator|=
name|bevent
operator|->
name|button
expr_stmt|;
name|popup
operator|->
name|button_x
operator|=
name|bevent
operator|->
name|x_root
expr_stmt|;
name|popup
operator|->
name|button_y
operator|=
name|bevent
operator|->
name|y_root
expr_stmt|;
name|g_signal_connect
argument_list|(
name|widget
argument_list|,
literal|"button-release-event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_view_popup_button_release
argument_list|)
argument_list|,
name|popup
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|widget
argument_list|,
literal|"unmap"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_view_popup_unmap
argument_list|)
argument_list|,
name|popup
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|widget
argument_list|,
literal|"drag-begin"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_view_popup_drag_begin
argument_list|)
argument_list|,
name|popup
argument_list|)
expr_stmt|;
name|popup
operator|->
name|timeout_id
operator|=
name|g_timeout_add
argument_list|(
name|VIEW_POPUP_DELAY
argument_list|,
operator|(
name|GSourceFunc
operator|)
name|gimp_view_popup_timeout
argument_list|,
name|popup
argument_list|)
expr_stmt|;
name|g_object_set_data_full
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"gimp-view-popup"
argument_list|,
name|popup
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|gimp_view_popup_hide
argument_list|)
expr_stmt|;
name|gtk_grab_add
argument_list|(
name|widget
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_view_popup_hide (GimpViewPopup * popup)
name|gimp_view_popup_hide
parameter_list|(
name|GimpViewPopup
modifier|*
name|popup
parameter_list|)
block|{
if|if
condition|(
name|popup
operator|->
name|timeout_id
condition|)
name|g_source_remove
argument_list|(
name|popup
operator|->
name|timeout_id
argument_list|)
expr_stmt|;
if|if
condition|(
name|popup
operator|->
name|popup
condition|)
name|gtk_widget_destroy
argument_list|(
name|popup
operator|->
name|popup
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|popup
operator|->
name|widget
argument_list|,
name|gimp_view_popup_button_release
argument_list|,
name|popup
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|popup
operator|->
name|widget
argument_list|,
name|gimp_view_popup_unmap
argument_list|,
name|popup
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|popup
operator|->
name|widget
argument_list|,
name|gimp_view_popup_drag_begin
argument_list|,
name|popup
argument_list|)
expr_stmt|;
name|gtk_grab_remove
argument_list|(
name|popup
operator|->
name|widget
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|GimpViewPopup
argument_list|,
name|popup
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_view_popup_button_release (GtkWidget * widget,GdkEventButton * bevent,GimpViewPopup * popup)
name|gimp_view_popup_button_release
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|GimpViewPopup
modifier|*
name|popup
parameter_list|)
block|{
if|if
condition|(
name|bevent
operator|->
name|button
operator|==
name|popup
operator|->
name|button
condition|)
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|popup
operator|->
name|widget
argument_list|)
argument_list|,
literal|"gimp-view-popup"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_view_popup_unmap (GtkWidget * widget,GimpViewPopup * popup)
name|gimp_view_popup_unmap
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpViewPopup
modifier|*
name|popup
parameter_list|)
block|{
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|popup
operator|->
name|widget
argument_list|)
argument_list|,
literal|"gimp-view-popup"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_view_popup_drag_begin (GtkWidget * widget,GdkDragContext * context,GimpViewPopup * popup)
name|gimp_view_popup_drag_begin
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|GimpViewPopup
modifier|*
name|popup
parameter_list|)
block|{
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|popup
operator|->
name|widget
argument_list|)
argument_list|,
literal|"gimp-view-popup"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_view_popup_timeout (GimpViewPopup * popup)
name|gimp_view_popup_timeout
parameter_list|(
name|GimpViewPopup
modifier|*
name|popup
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|window
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|view
decl_stmt|;
name|GdkDisplay
modifier|*
name|display
decl_stmt|;
name|GdkRectangle
name|workarea
decl_stmt|;
name|gint
name|x
decl_stmt|;
name|gint
name|y
decl_stmt|;
name|popup
operator|->
name|timeout_id
operator|=
literal|0
expr_stmt|;
name|window
operator|=
name|gtk_window_new
argument_list|(
name|GTK_WINDOW_POPUP
argument_list|)
expr_stmt|;
name|gtk_window_set_resizable
argument_list|(
name|GTK_WINDOW
argument_list|(
name|window
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_window_set_screen
argument_list|(
name|GTK_WINDOW
argument_list|(
name|window
argument_list|)
argument_list|,
name|gtk_widget_get_screen
argument_list|(
name|popup
operator|->
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_window_set_transient_for
argument_list|(
name|GTK_WINDOW
argument_list|(
name|window
argument_list|)
argument_list|,
name|GTK_WINDOW
argument_list|(
name|gtk_widget_get_toplevel
argument_list|(
name|popup
operator|->
name|widget
argument_list|)
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
name|view
operator|=
name|gimp_view_new_full
argument_list|(
name|popup
operator|->
name|context
argument_list|,
name|popup
operator|->
name|viewable
argument_list|,
name|popup
operator|->
name|popup_width
argument_list|,
name|popup
operator|->
name|popup_height
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_view_renderer_set_dot_for_dot
argument_list|(
name|GIMP_VIEW
argument_list|(
name|view
argument_list|)
operator|->
name|renderer
argument_list|,
name|popup
operator|->
name|dot_for_dot
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|view
argument_list|)
expr_stmt|;
name|display
operator|=
name|gtk_widget_get_display
argument_list|(
name|popup
operator|->
name|widget
argument_list|)
expr_stmt|;
name|gdk_monitor_get_workarea
argument_list|(
name|gdk_display_get_monitor_at_point
argument_list|(
name|display
argument_list|,
name|popup
operator|->
name|button_x
argument_list|,
name|popup
operator|->
name|button_y
argument_list|)
argument_list|,
operator|&
name|workarea
argument_list|)
expr_stmt|;
name|x
operator|=
name|popup
operator|->
name|button_x
operator|-
operator|(
name|popup
operator|->
name|popup_width
operator|/
literal|2
operator|)
expr_stmt|;
name|y
operator|=
name|popup
operator|->
name|button_y
operator|-
operator|(
name|popup
operator|->
name|popup_height
operator|/
literal|2
operator|)
expr_stmt|;
name|x
operator|=
name|CLAMP
argument_list|(
name|x
argument_list|,
name|workarea
operator|.
name|x
argument_list|,
name|workarea
operator|.
name|x
operator|+
name|workarea
operator|.
name|width
operator|-
name|popup
operator|->
name|popup_width
argument_list|)
expr_stmt|;
name|y
operator|=
name|CLAMP
argument_list|(
name|y
argument_list|,
name|workarea
operator|.
name|y
argument_list|,
name|workarea
operator|.
name|y
operator|+
name|workarea
operator|.
name|height
operator|-
name|popup
operator|->
name|popup_height
argument_list|)
expr_stmt|;
name|gtk_window_move
argument_list|(
name|GTK_WINDOW
argument_list|(
name|window
argument_list|)
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|window
argument_list|)
expr_stmt|;
name|popup
operator|->
name|popup
operator|=
name|window
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

end_unit

