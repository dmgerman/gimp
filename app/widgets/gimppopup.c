begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimppopup.c  * Copyright (C) 2003-2014 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<gdk/gdkkeysyms.h>
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
file|"core/gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"gimppopup.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon29c6190e0103
block|{
DECL|enumerator|CANCEL
name|CANCEL
block|,
DECL|enumerator|CONFIRM
name|CONFIRM
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_popup_map
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
name|gimp_popup_button_press
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
name|gboolean
name|gimp_popup_key_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventKey
modifier|*
name|kevent
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_popup_real_cancel
parameter_list|(
name|GimpPopup
modifier|*
name|popup
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_popup_real_confirm
parameter_list|(
name|GimpPopup
modifier|*
name|popup
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpPopup,gimp_popup,GTK_TYPE_WINDOW)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpPopup
argument_list|,
argument|gimp_popup
argument_list|,
argument|GTK_TYPE_WINDOW
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_popup_parent_class
end_define

begin_decl_stmt
specifier|static
name|guint
name|popup_signals
index|[
name|LAST_SIGNAL
index|]
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
name|gimp_popup_class_init
parameter_list|(
name|GimpPopupClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkWidgetClass
modifier|*
name|widget_class
init|=
name|GTK_WIDGET_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GtkBindingSet
modifier|*
name|binding_set
decl_stmt|;
name|popup_signals
index|[
name|CANCEL
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"cancel"
argument_list|,
name|G_OBJECT_CLASS_TYPE
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_LAST
operator||
name|G_SIGNAL_ACTION
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpPopupClass
argument_list|,
name|cancel
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__VOID
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|popup_signals
index|[
name|CONFIRM
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"confirm"
argument_list|,
name|G_OBJECT_CLASS_TYPE
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_LAST
operator||
name|G_SIGNAL_ACTION
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpPopupClass
argument_list|,
name|confirm
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__VOID
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|widget_class
operator|->
name|map
operator|=
name|gimp_popup_map
expr_stmt|;
name|widget_class
operator|->
name|button_press_event
operator|=
name|gimp_popup_button_press
expr_stmt|;
name|widget_class
operator|->
name|key_press_event
operator|=
name|gimp_popup_key_press
expr_stmt|;
name|klass
operator|->
name|cancel
operator|=
name|gimp_popup_real_cancel
expr_stmt|;
name|klass
operator|->
name|confirm
operator|=
name|gimp_popup_real_confirm
expr_stmt|;
name|binding_set
operator|=
name|gtk_binding_set_by_class
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|gtk_binding_entry_add_signal
argument_list|(
name|binding_set
argument_list|,
name|GDK_KEY_Escape
argument_list|,
literal|0
argument_list|,
literal|"cancel"
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_binding_entry_add_signal
argument_list|(
name|binding_set
argument_list|,
name|GDK_KEY_Return
argument_list|,
literal|0
argument_list|,
literal|"confirm"
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_binding_entry_add_signal
argument_list|(
name|binding_set
argument_list|,
name|GDK_KEY_KP_Enter
argument_list|,
literal|0
argument_list|,
literal|"confirm"
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_binding_entry_add_signal
argument_list|(
name|binding_set
argument_list|,
name|GDK_KEY_ISO_Enter
argument_list|,
literal|0
argument_list|,
literal|"confirm"
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_binding_entry_add_signal
argument_list|(
name|binding_set
argument_list|,
name|GDK_KEY_space
argument_list|,
literal|0
argument_list|,
literal|"confirm"
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_binding_entry_add_signal
argument_list|(
name|binding_set
argument_list|,
name|GDK_KEY_KP_Space
argument_list|,
literal|0
argument_list|,
literal|"confirm"
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_popup_init (GimpPopup * popup)
name|gimp_popup_init
parameter_list|(
name|GimpPopup
modifier|*
name|popup
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_popup_grab_notify (GtkWidget * widget,gboolean was_grabbed)
name|gimp_popup_grab_notify
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gboolean
name|was_grabbed
parameter_list|)
block|{
if|if
condition|(
name|was_grabbed
condition|)
return|return;
comment|/* ignore grabs on one of our children, like a scrollbar */
if|if
condition|(
name|gtk_widget_is_ancestor
argument_list|(
name|gtk_grab_get_current
argument_list|()
argument_list|,
name|widget
argument_list|)
condition|)
return|return;
name|g_signal_emit
argument_list|(
name|widget
argument_list|,
name|popup_signals
index|[
name|CANCEL
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_popup_grab_broken_event (GtkWidget * widget,GdkEventGrabBroken * event)
name|gimp_popup_grab_broken_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventGrabBroken
modifier|*
name|event
parameter_list|)
block|{
name|gimp_popup_grab_notify
argument_list|(
name|widget
argument_list|,
name|FALSE
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
DECL|function|gimp_popup_map (GtkWidget * widget)
name|gimp_popup_map
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|map
argument_list|(
name|widget
argument_list|)
expr_stmt|;
comment|/*  grab with owner_events == TRUE so the popup's widgets can    *  receive events. we filter away events outside this toplevel    *  away in button_press()    */
if|if
condition|(
name|gdk_pointer_grab
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|widget
argument_list|)
argument_list|,
name|TRUE
argument_list|,
name|GDK_BUTTON_PRESS_MASK
operator||
name|GDK_BUTTON_RELEASE_MASK
operator||
name|GDK_POINTER_MOTION_MASK
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GDK_CURRENT_TIME
argument_list|)
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|gdk_keyboard_grab
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|widget
argument_list|)
argument_list|,
name|TRUE
argument_list|,
name|GDK_CURRENT_TIME
argument_list|)
operator|==
literal|0
condition|)
block|{
name|gtk_grab_add
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|widget
argument_list|,
literal|"grab-notify"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_popup_grab_notify
argument_list|)
argument_list|,
name|widget
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|widget
argument_list|,
literal|"grab-broken-event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_popup_grab_broken_event
argument_list|)
argument_list|,
name|widget
argument_list|)
expr_stmt|;
return|return;
block|}
else|else
block|{
name|gdk_display_pointer_ungrab
argument_list|(
name|gtk_widget_get_display
argument_list|(
name|widget
argument_list|)
argument_list|,
name|GDK_CURRENT_TIME
argument_list|)
expr_stmt|;
block|}
block|}
comment|/*  if we could not grab, destroy the popup instead of leaving it    *  around uncloseable.    */
name|g_signal_emit
argument_list|(
name|widget
argument_list|,
name|popup_signals
index|[
name|CANCEL
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_popup_button_press (GtkWidget * widget,GdkEventButton * bevent)
name|gimp_popup_button_press
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
name|GtkWidget
modifier|*
name|event_widget
decl_stmt|;
name|gboolean
name|cancel
init|=
name|FALSE
decl_stmt|;
name|event_widget
operator|=
name|gtk_get_event_widget
argument_list|(
operator|(
name|GdkEvent
operator|*
operator|)
name|bevent
argument_list|)
expr_stmt|;
if|if
condition|(
name|event_widget
operator|==
name|widget
condition|)
block|{
name|GtkAllocation
name|allocation
decl_stmt|;
name|gtk_widget_get_allocation
argument_list|(
name|widget
argument_list|,
operator|&
name|allocation
argument_list|)
expr_stmt|;
comment|/*  the event was on the popup, which can either be really on the        *  popup or outside gimp (owner_events == TRUE, see map())        */
if|if
condition|(
name|bevent
operator|->
name|x
operator|<
literal|0
operator|||
name|bevent
operator|->
name|y
operator|<
literal|0
operator|||
name|bevent
operator|->
name|x
operator|>
name|allocation
operator|.
name|width
operator|||
name|bevent
operator|->
name|y
operator|>
name|allocation
operator|.
name|height
condition|)
block|{
comment|/*  the event was outsde gimp  */
name|cancel
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|gtk_widget_get_toplevel
argument_list|(
name|event_widget
argument_list|)
operator|!=
name|widget
condition|)
block|{
comment|/*  the event was on a gimp widget, but not inside the popup  */
name|cancel
operator|=
name|TRUE
expr_stmt|;
block|}
if|if
condition|(
name|cancel
condition|)
name|g_signal_emit
argument_list|(
name|widget
argument_list|,
name|popup_signals
index|[
name|CANCEL
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|cancel
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_popup_key_press (GtkWidget * widget,GdkEventKey * kevent)
name|gimp_popup_key_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventKey
modifier|*
name|kevent
parameter_list|)
block|{
name|GtkBindingSet
modifier|*
name|binding_set
decl_stmt|;
name|binding_set
operator|=
name|gtk_binding_set_by_class
argument_list|(
name|GIMP_POPUP_GET_CLASS
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  invoke the popup's binding entries manually, because otherwise    *  the focus widget (GtkTreeView e.g.) would consume it    */
if|if
condition|(
name|gtk_binding_set_activate
argument_list|(
name|binding_set
argument_list|,
name|kevent
operator|->
name|keyval
argument_list|,
name|kevent
operator|->
name|state
argument_list|,
name|GTK_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|)
condition|)
block|{
return|return
name|TRUE
return|;
block|}
return|return
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|key_press_event
argument_list|(
name|widget
argument_list|,
name|kevent
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_popup_real_cancel (GimpPopup * popup)
name|gimp_popup_real_cancel
parameter_list|(
name|GimpPopup
modifier|*
name|popup
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
init|=
name|GTK_WIDGET
argument_list|(
name|popup
argument_list|)
decl_stmt|;
if|if
condition|(
name|gtk_grab_get_current
argument_list|()
operator|==
name|widget
condition|)
name|gtk_grab_remove
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|widget
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_popup_real_confirm (GimpPopup * popup)
name|gimp_popup_real_confirm
parameter_list|(
name|GimpPopup
modifier|*
name|popup
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
init|=
name|GTK_WIDGET
argument_list|(
name|popup
argument_list|)
decl_stmt|;
if|if
condition|(
name|gtk_grab_get_current
argument_list|()
operator|==
name|widget
condition|)
name|gtk_grab_remove
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|widget
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_popup_show (GimpPopup * popup,GtkWidget * widget)
name|gimp_popup_show
parameter_list|(
name|GimpPopup
modifier|*
name|popup
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|GdkScreen
modifier|*
name|screen
decl_stmt|;
name|GtkRequisition
name|requisition
decl_stmt|;
name|GtkAllocation
name|allocation
decl_stmt|;
name|GdkRectangle
name|rect
decl_stmt|;
name|gint
name|monitor
decl_stmt|;
name|gint
name|orig_x
decl_stmt|;
name|gint
name|orig_y
decl_stmt|;
name|gint
name|x
decl_stmt|;
name|gint
name|y
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_POPUP
argument_list|(
name|popup
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GTK_IS_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_size_request
argument_list|(
name|GTK_WIDGET
argument_list|(
name|popup
argument_list|)
argument_list|,
operator|&
name|requisition
argument_list|)
expr_stmt|;
name|gtk_widget_get_allocation
argument_list|(
name|widget
argument_list|,
operator|&
name|allocation
argument_list|)
expr_stmt|;
name|gdk_window_get_origin
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|widget
argument_list|)
argument_list|,
operator|&
name|orig_x
argument_list|,
operator|&
name|orig_y
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gtk_widget_get_has_window
argument_list|(
name|widget
argument_list|)
condition|)
block|{
name|orig_x
operator|+=
name|allocation
operator|.
name|x
expr_stmt|;
name|orig_y
operator|+=
name|allocation
operator|.
name|y
expr_stmt|;
block|}
name|screen
operator|=
name|gtk_widget_get_screen
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|monitor
operator|=
name|gdk_screen_get_monitor_at_point
argument_list|(
name|screen
argument_list|,
name|orig_x
argument_list|,
name|orig_y
argument_list|)
expr_stmt|;
name|gdk_screen_get_monitor_workarea
argument_list|(
name|screen
argument_list|,
name|monitor
argument_list|,
operator|&
name|rect
argument_list|)
expr_stmt|;
if|if
condition|(
name|gtk_widget_get_direction
argument_list|(
name|widget
argument_list|)
operator|==
name|GTK_TEXT_DIR_RTL
condition|)
block|{
name|x
operator|=
name|orig_x
operator|+
name|allocation
operator|.
name|width
operator|-
name|requisition
operator|.
name|width
expr_stmt|;
if|if
condition|(
name|x
operator|<
name|rect
operator|.
name|x
condition|)
name|x
operator|-=
name|allocation
operator|.
name|width
operator|-
name|requisition
operator|.
name|width
expr_stmt|;
block|}
else|else
block|{
name|x
operator|=
name|orig_x
expr_stmt|;
if|if
condition|(
name|x
operator|+
name|requisition
operator|.
name|width
operator|>
name|rect
operator|.
name|x
operator|+
name|rect
operator|.
name|width
condition|)
name|x
operator|+=
name|allocation
operator|.
name|width
operator|-
name|requisition
operator|.
name|width
expr_stmt|;
block|}
name|y
operator|=
name|orig_y
operator|+
name|allocation
operator|.
name|height
expr_stmt|;
if|if
condition|(
name|y
operator|+
name|requisition
operator|.
name|height
operator|>
name|rect
operator|.
name|y
operator|+
name|rect
operator|.
name|height
condition|)
name|y
operator|=
name|orig_y
operator|-
name|requisition
operator|.
name|height
expr_stmt|;
name|gtk_window_set_screen
argument_list|(
name|GTK_WINDOW
argument_list|(
name|popup
argument_list|)
argument_list|,
name|screen
argument_list|)
expr_stmt|;
name|gtk_window_set_transient_for
argument_list|(
name|GTK_WINDOW
argument_list|(
name|popup
argument_list|)
argument_list|,
name|GTK_WINDOW
argument_list|(
name|gtk_widget_get_toplevel
argument_list|(
name|widget
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_window_move
argument_list|(
name|GTK_WINDOW
argument_list|(
name|popup
argument_list|)
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|GTK_WIDGET
argument_list|(
name|popup
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

