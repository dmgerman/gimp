begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimppickbutton-kwin.c  * Copyright (C) 2017 Jehan<jehan@gimp.org>  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
file|"gimppickbutton.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/libgimp-intl.h"
end_include

begin_function_decl
name|void
name|_gimp_pick_button_default_pick
parameter_list|(
name|GimpPickButton
modifier|*
name|button
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|_gimp_pick_button_kwin_available
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|_gimp_pick_button_kwin_pick
parameter_list|(
name|GimpPickButton
modifier|*
name|button
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|gboolean
DECL|function|_gimp_pick_button_kwin_available (void)
name|_gimp_pick_button_kwin_available
parameter_list|(
name|void
parameter_list|)
block|{
name|GDBusProxy
modifier|*
name|proxy
init|=
name|NULL
decl_stmt|;
name|gboolean
name|available
init|=
name|FALSE
decl_stmt|;
name|proxy
operator|=
name|g_dbus_proxy_new_for_bus_sync
argument_list|(
name|G_BUS_TYPE_SESSION
argument_list|,
name|G_DBUS_PROXY_FLAGS_DO_NOT_AUTO_START
argument_list|,
name|NULL
argument_list|,
literal|"org.kde.KWin"
argument_list|,
literal|"/ColorPicker"
argument_list|,
literal|"org.kde.kwin.ColorPicker"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|proxy
condition|)
block|{
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|g_dbus_proxy_call_sync
argument_list|(
name|proxy
argument_list|,
literal|"org.freedesktop.DBus.Peer.Ping"
argument_list|,
name|NULL
argument_list|,
name|G_DBUS_CALL_FLAGS_NONE
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|error
condition|)
name|available
operator|=
name|TRUE
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|proxy
argument_list|)
expr_stmt|;
block|}
return|return
name|available
return|;
block|}
end_function

begin_comment
comment|/* entry point to this file, called from gimppickbutton.c */
end_comment

begin_function
name|void
DECL|function|_gimp_pick_button_kwin_pick (GimpPickButton * button)
name|_gimp_pick_button_kwin_pick
parameter_list|(
name|GimpPickButton
modifier|*
name|button
parameter_list|)
block|{
name|GDBusProxy
modifier|*
name|proxy
init|=
name|NULL
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|GVariant
modifier|*
name|retval
decl_stmt|;
name|proxy
operator|=
name|g_dbus_proxy_new_for_bus_sync
argument_list|(
name|G_BUS_TYPE_SESSION
argument_list|,
name|G_DBUS_PROXY_FLAGS_DO_NOT_AUTO_START
argument_list|,
name|NULL
argument_list|,
literal|"org.kde.KWin"
argument_list|,
literal|"/ColorPicker"
argument_list|,
literal|"org.kde.kwin.ColorPicker"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|proxy
argument_list|)
expr_stmt|;
name|retval
operator|=
name|g_dbus_proxy_call_sync
argument_list|(
name|proxy
argument_list|,
literal|"pick"
argument_list|,
name|NULL
argument_list|,
name|G_DBUS_CALL_FLAGS_NONE
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|retval
condition|)
block|{
name|GimpRGB
name|rgb
decl_stmt|;
name|guint32
name|color
decl_stmt|;
name|g_variant_get
argument_list|(
name|retval
argument_list|,
literal|"(u)"
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|g_variant_unref
argument_list|(
name|retval
argument_list|)
expr_stmt|;
comment|/* Returned value is ARGB stored in uint32. */
name|gimp_rgba_set_uchar
argument_list|(
operator|&
name|rgb
argument_list|,
operator|(
name|color
operator|>>
literal|16
operator|)
operator|&
literal|0xff
argument_list|,
comment|/* Red                           */
operator|(
name|color
operator|>>
literal|8
operator|)
operator|&
literal|0xff
argument_list|,
comment|/* Green                         */
name|color
operator|&
literal|0xff
argument_list|,
comment|/* Blue: least significant byte. */
operator|(
name|color
operator|>>
literal|24
operator|)
operator|&
literal|0xff
argument_list|)
expr_stmt|;
comment|/* Alpha: most significant byte. */
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
else|else
block|{
comment|/* I had failure of KDE's color picking API. So let's just        * fallback to the default color picking when this happens. This        * will at least work on X11.        * See: https://bugs.kde.org/show_bug.cgi?id=387720        */
if|if
condition|(
name|error
condition|)
name|g_warning
argument_list|(
literal|"KWin backend for color picking failed with error: %s"
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|_gimp_pick_button_default_pick
argument_list|(
name|GIMP_PICK_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|proxy
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

