begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimppickbutton.c  * Copyright (C) 2002 Michael Natterer<mitch@gimp.org>  *  * based on gtk+/gtk/gtkcolorsel.c  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_define
DECL|macro|WIN32_LEAN_AND_MEAN
define|#
directive|define
name|WIN32_LEAN_AND_MEAN
end_define

begin_include
include|#
directive|include
file|<windows.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgetstypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpcairo-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimphelpui.h"
end_include

begin_include
include|#
directive|include
file|"gimpicons.h"
end_include

begin_include
include|#
directive|include
file|"gimppickbutton.h"
end_include

begin_include
include|#
directive|include
file|"gimppickbutton-default.h"
end_include

begin_include
include|#
directive|include
file|"gimppickbutton-private.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgetsutils.h"
end_include

begin_include
include|#
directive|include
file|"cursors/gimp-color-picker-cursors.c"
end_include

begin_include
include|#
directive|include
file|"libgimp/libgimp-intl.h"
end_include

begin_function_decl
specifier|static
name|gboolean
name|gimp_pick_button_mouse_press
parameter_list|(
name|GtkWidget
modifier|*
name|invisible
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|,
name|GimpPickButton
modifier|*
name|button
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_pick_button_key_press
parameter_list|(
name|GtkWidget
modifier|*
name|invisible
parameter_list|,
name|GdkEventKey
modifier|*
name|event
parameter_list|,
name|GimpPickButton
modifier|*
name|button
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_pick_button_mouse_motion
parameter_list|(
name|GtkWidget
modifier|*
name|invisible
parameter_list|,
name|GdkEventMotion
modifier|*
name|event
parameter_list|,
name|GimpPickButton
modifier|*
name|button
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_pick_button_mouse_release
parameter_list|(
name|GtkWidget
modifier|*
name|invisible
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|,
name|GimpPickButton
modifier|*
name|button
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_pick_button_shutdown
parameter_list|(
name|GimpPickButton
modifier|*
name|button
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_pick_button_pick
parameter_list|(
name|GimpPickButton
modifier|*
name|button
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_function
specifier|static
name|GdkCursor
modifier|*
DECL|function|make_cursor (GdkDisplay * display)
name|make_cursor
parameter_list|(
name|GdkDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GdkPixbuf
modifier|*
name|pixbuf
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|pixbuf
operator|=
name|gdk_pixbuf_new_from_resource
argument_list|(
literal|"/org/gimp/color-picker-cursors/cursor-color-picker.png"
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|pixbuf
condition|)
block|{
name|GdkCursor
modifier|*
name|cursor
init|=
name|gdk_cursor_new_from_pixbuf
argument_list|(
name|display
argument_list|,
name|pixbuf
argument_list|,
literal|1
argument_list|,
literal|30
argument_list|)
decl_stmt|;
name|g_object_unref
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
return|return
name|cursor
return|;
block|}
else|else
block|{
name|g_critical
argument_list|(
literal|"Failed to create cursor image: %s"
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_pick_button_mouse_press (GtkWidget * invisible,GdkEventButton * event,GimpPickButton * button)
name|gimp_pick_button_mouse_press
parameter_list|(
name|GtkWidget
modifier|*
name|invisible
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|,
name|GimpPickButton
modifier|*
name|button
parameter_list|)
block|{
if|if
condition|(
name|event
operator|->
name|type
operator|==
name|GDK_BUTTON_PRESS
operator|&&
name|event
operator|->
name|button
operator|==
literal|1
condition|)
block|{
name|g_signal_connect
argument_list|(
name|invisible
argument_list|,
literal|"motion-notify-event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_pick_button_mouse_motion
argument_list|)
argument_list|,
name|button
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|invisible
argument_list|,
literal|"button-release-event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_pick_button_mouse_release
argument_list|)
argument_list|,
name|button
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|invisible
argument_list|,
name|gimp_pick_button_mouse_press
argument_list|,
name|button
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|invisible
argument_list|,
name|gimp_pick_button_key_press
argument_list|,
name|button
argument_list|)
expr_stmt|;
name|gimp_pick_button_pick
argument_list|(
name|button
argument_list|,
operator|(
name|GdkEvent
operator|*
operator|)
name|event
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_pick_button_key_press (GtkWidget * invisible,GdkEventKey * event,GimpPickButton * button)
name|gimp_pick_button_key_press
parameter_list|(
name|GtkWidget
modifier|*
name|invisible
parameter_list|,
name|GdkEventKey
modifier|*
name|event
parameter_list|,
name|GimpPickButton
modifier|*
name|button
parameter_list|)
block|{
if|if
condition|(
name|event
operator|->
name|keyval
operator|==
name|GDK_KEY_Escape
condition|)
block|{
name|gimp_pick_button_shutdown
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|invisible
argument_list|,
name|gimp_pick_button_mouse_press
argument_list|,
name|button
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|invisible
argument_list|,
name|gimp_pick_button_key_press
argument_list|,
name|button
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_pick_button_mouse_motion (GtkWidget * invisible,GdkEventMotion * event,GimpPickButton * button)
name|gimp_pick_button_mouse_motion
parameter_list|(
name|GtkWidget
modifier|*
name|invisible
parameter_list|,
name|GdkEventMotion
modifier|*
name|event
parameter_list|,
name|GimpPickButton
modifier|*
name|button
parameter_list|)
block|{
name|gimp_pick_button_pick
argument_list|(
name|button
argument_list|,
operator|(
name|GdkEvent
operator|*
operator|)
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
DECL|function|gimp_pick_button_mouse_release (GtkWidget * invisible,GdkEventButton * event,GimpPickButton * button)
name|gimp_pick_button_mouse_release
parameter_list|(
name|GtkWidget
modifier|*
name|invisible
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|,
name|GimpPickButton
modifier|*
name|button
parameter_list|)
block|{
if|if
condition|(
name|event
operator|->
name|button
operator|!=
literal|1
condition|)
return|return
name|FALSE
return|;
name|gimp_pick_button_pick
argument_list|(
name|button
argument_list|,
operator|(
name|GdkEvent
operator|*
operator|)
name|event
argument_list|)
expr_stmt|;
name|gimp_pick_button_shutdown
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|invisible
argument_list|,
name|gimp_pick_button_mouse_motion
argument_list|,
name|button
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|invisible
argument_list|,
name|gimp_pick_button_mouse_release
argument_list|,
name|button
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pick_button_shutdown (GimpPickButton * button)
name|gimp_pick_button_shutdown
parameter_list|(
name|GimpPickButton
modifier|*
name|button
parameter_list|)
block|{
name|GdkDisplay
modifier|*
name|display
init|=
name|gtk_widget_get_display
argument_list|(
name|button
operator|->
name|priv
operator|->
name|grab_widget
argument_list|)
decl_stmt|;
name|gtk_grab_remove
argument_list|(
name|button
operator|->
name|priv
operator|->
name|grab_widget
argument_list|)
expr_stmt|;
name|gdk_seat_ungrab
argument_list|(
name|gdk_display_get_default_seat
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pick_button_pick (GimpPickButton * button,GdkEvent * event)
name|gimp_pick_button_pick
parameter_list|(
name|GimpPickButton
modifier|*
name|button
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|)
block|{
name|GdkScreen
modifier|*
name|screen
init|=
name|gdk_event_get_screen
argument_list|(
name|event
argument_list|)
decl_stmt|;
name|GimpColorProfile
modifier|*
name|monitor_profile
decl_stmt|;
name|GdkMonitor
modifier|*
name|monitor
decl_stmt|;
name|GimpRGB
name|rgb
decl_stmt|;
name|gint
name|x_root
decl_stmt|;
name|gint
name|y_root
decl_stmt|;
name|gdouble
name|x_win
decl_stmt|;
name|gdouble
name|y_win
decl_stmt|;
name|gdk_window_get_origin
argument_list|(
name|gdk_event_get_window
argument_list|(
name|event
argument_list|)
argument_list|,
operator|&
name|x_root
argument_list|,
operator|&
name|y_root
argument_list|)
expr_stmt|;
name|gdk_event_get_coords
argument_list|(
name|event
argument_list|,
operator|&
name|x_win
argument_list|,
operator|&
name|y_win
argument_list|)
expr_stmt|;
name|x_root
operator|+=
name|x_win
expr_stmt|;
name|y_root
operator|+=
name|y_win
expr_stmt|;
ifdef|#
directive|ifdef
name|G_OS_WIN32
block|{
name|HDC
name|hdc
decl_stmt|;
name|RECT
name|rect
decl_stmt|;
name|COLORREF
name|win32_color
decl_stmt|;
comment|/* For MS Windows, use native GDI functions to get the pixel, as      * cairo does not handle the case where you have multiple monitors      * with a monitor on the left or above the primary monitor.  That      * scenario create a cairo primary surface with negative extent,      * which is not handled properly (bug 740634).      */
name|hdc
operator|=
name|GetDC
argument_list|(
name|HWND_DESKTOP
argument_list|)
expr_stmt|;
name|GetClipBox
argument_list|(
name|hdc
argument_list|,
operator|&
name|rect
argument_list|)
expr_stmt|;
name|win32_color
operator|=
name|GetPixel
argument_list|(
name|hdc
argument_list|,
name|x_root
operator|+
name|rect
operator|.
name|left
argument_list|,
name|y_root
operator|+
name|rect
operator|.
name|top
argument_list|)
expr_stmt|;
name|ReleaseDC
argument_list|(
name|HWND_DESKTOP
argument_list|,
name|hdc
argument_list|)
expr_stmt|;
name|gimp_rgba_set_uchar
argument_list|(
operator|&
name|rgb
argument_list|,
name|GetRValue
argument_list|(
name|win32_color
argument_list|)
argument_list|,
name|GetGValue
argument_list|(
name|win32_color
argument_list|)
argument_list|,
name|GetBValue
argument_list|(
name|win32_color
argument_list|)
argument_list|,
literal|255
argument_list|)
expr_stmt|;
block|}
else|#
directive|else
block|{
name|GdkWindow
modifier|*
name|window
decl_stmt|;
name|gint
name|x_window
decl_stmt|;
name|gint
name|y_window
decl_stmt|;
name|cairo_surface_t
modifier|*
name|image
decl_stmt|;
name|cairo_t
modifier|*
name|cr
decl_stmt|;
name|guchar
modifier|*
name|data
decl_stmt|;
name|guchar
name|color
index|[
literal|3
index|]
decl_stmt|;
comment|/* we try to pick from the local window under the cursor, and fall      * back to picking from the root window if this fails (i.e., if      * the cursor is not under a local window).  on wayland, picking      * from the root window is not supported, so this at least allows      * us to pick from local windows.  see bug #780375.      */
name|window
operator|=
name|gdk_device_get_window_at_position
argument_list|(
name|gdk_event_get_device
argument_list|(
name|event
argument_list|)
argument_list|,
operator|&
name|x_window
argument_list|,
operator|&
name|y_window
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|window
condition|)
block|{
name|window
operator|=
name|gdk_screen_get_root_window
argument_list|(
name|screen
argument_list|)
expr_stmt|;
name|x_window
operator|=
name|x_root
expr_stmt|;
name|y_window
operator|=
name|y_root
expr_stmt|;
block|}
name|image
operator|=
name|cairo_image_surface_create
argument_list|(
name|CAIRO_FORMAT_RGB24
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|cr
operator|=
name|cairo_create
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gdk_cairo_set_source_window
argument_list|(
name|cr
argument_list|,
name|window
argument_list|,
operator|-
name|x_window
argument_list|,
operator|-
name|y_window
argument_list|)
expr_stmt|;
name|cairo_paint
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|cairo_destroy
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|data
operator|=
name|cairo_image_surface_get_data
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|GIMP_CAIRO_RGB24_GET_PIXEL
argument_list|(
name|data
argument_list|,
name|color
index|[
literal|0
index|]
argument_list|,
name|color
index|[
literal|1
index|]
argument_list|,
name|color
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
name|cairo_surface_destroy
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gimp_rgba_set_uchar
argument_list|(
operator|&
name|rgb
argument_list|,
name|color
index|[
literal|0
index|]
argument_list|,
name|color
index|[
literal|1
index|]
argument_list|,
name|color
index|[
literal|2
index|]
argument_list|,
literal|255
argument_list|)
expr_stmt|;
block|}
endif|#
directive|endif
name|monitor
operator|=
name|gdk_display_get_monitor_at_point
argument_list|(
name|gdk_screen_get_display
argument_list|(
name|screen
argument_list|)
argument_list|,
name|x_root
argument_list|,
name|y_root
argument_list|)
expr_stmt|;
name|monitor_profile
operator|=
name|gimp_monitor_get_color_profile
argument_list|(
name|monitor
argument_list|)
expr_stmt|;
if|if
condition|(
name|monitor_profile
condition|)
block|{
name|GimpColorProfile
modifier|*
name|srgb_profile
decl_stmt|;
name|GimpColorTransform
modifier|*
name|transform
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|format
decl_stmt|;
name|GimpColorTransformFlags
name|flags
init|=
literal|0
decl_stmt|;
name|format
operator|=
name|babl_format
argument_list|(
literal|"R'G'B'A double"
argument_list|)
expr_stmt|;
name|flags
operator||=
name|GIMP_COLOR_TRANSFORM_FLAGS_NOOPTIMIZE
expr_stmt|;
name|flags
operator||=
name|GIMP_COLOR_TRANSFORM_FLAGS_BLACK_POINT_COMPENSATION
expr_stmt|;
name|srgb_profile
operator|=
name|gimp_color_profile_new_rgb_srgb
argument_list|()
expr_stmt|;
name|transform
operator|=
name|gimp_color_transform_new
argument_list|(
name|monitor_profile
argument_list|,
name|format
argument_list|,
name|srgb_profile
argument_list|,
name|format
argument_list|,
name|GIMP_COLOR_RENDERING_INTENT_PERCEPTUAL
argument_list|,
name|flags
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|srgb_profile
argument_list|)
expr_stmt|;
if|if
condition|(
name|transform
condition|)
block|{
name|gimp_color_transform_process_pixels
argument_list|(
name|transform
argument_list|,
name|format
argument_list|,
operator|&
name|rgb
argument_list|,
name|format
argument_list|,
operator|&
name|rgb
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gimp_rgb_clamp
argument_list|(
operator|&
name|rgb
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|transform
argument_list|)
expr_stmt|;
block|}
block|}
name|g_signal_emit_by_name
argument_list|(
name|button
argument_list|,
literal|"color-picked"
argument_list|,
operator|&
name|rgb
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* entry point to this file, called from gimppickbutton.c */
end_comment

begin_function
name|void
DECL|function|_gimp_pick_button_default_pick (GimpPickButton * button)
name|_gimp_pick_button_default_pick
parameter_list|(
name|GimpPickButton
modifier|*
name|button
parameter_list|)
block|{
name|GdkDisplay
modifier|*
name|display
decl_stmt|;
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
if|if
condition|(
operator|!
name|button
operator|->
name|priv
operator|->
name|cursor
condition|)
name|button
operator|->
name|priv
operator|->
name|cursor
operator|=
name|make_cursor
argument_list|(
name|gtk_widget_get_display
argument_list|(
name|GTK_WIDGET
argument_list|(
name|button
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|button
operator|->
name|priv
operator|->
name|grab_widget
condition|)
block|{
name|button
operator|->
name|priv
operator|->
name|grab_widget
operator|=
name|gtk_invisible_new
argument_list|()
expr_stmt|;
name|gtk_widget_add_events
argument_list|(
name|button
operator|->
name|priv
operator|->
name|grab_widget
argument_list|,
name|GDK_BUTTON_PRESS_MASK
operator||
name|GDK_BUTTON_RELEASE_MASK
operator||
name|GDK_BUTTON1_MOTION_MASK
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
operator|->
name|priv
operator|->
name|grab_widget
argument_list|)
expr_stmt|;
block|}
name|widget
operator|=
name|button
operator|->
name|priv
operator|->
name|grab_widget
expr_stmt|;
name|display
operator|=
name|gtk_widget_get_display
argument_list|(
name|widget
argument_list|)
expr_stmt|;
if|if
condition|(
name|gdk_seat_grab
argument_list|(
name|gdk_display_get_default_seat
argument_list|(
name|display
argument_list|)
argument_list|,
name|gtk_widget_get_window
argument_list|(
name|widget
argument_list|)
argument_list|,
name|GDK_SEAT_CAPABILITY_ALL
argument_list|,
name|FALSE
argument_list|,
name|button
operator|->
name|priv
operator|->
name|cursor
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
operator|!=
name|GDK_GRAB_SUCCESS
condition|)
block|{
name|g_warning
argument_list|(
literal|"Failed to grab seat to do eyedropper"
argument_list|)
expr_stmt|;
return|return;
block|}
name|gtk_grab_add
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|widget
argument_list|,
literal|"button-press-event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_pick_button_mouse_press
argument_list|)
argument_list|,
name|button
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|widget
argument_list|,
literal|"key-press-event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_pick_button_key_press
argument_list|)
argument_list|,
name|button
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

