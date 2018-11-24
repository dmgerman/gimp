begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 2009 Martin Nordholts<martinn@src.gnome.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"display/display-types.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpimagewindow.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpuimanager.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayer-new.h"
end_include

begin_include
include|#
directive|include
file|"tests.h"
end_include

begin_include
include|#
directive|include
file|"gimp-app-test-utils.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_comment
comment|/* SendInput() requirement is Windows 2000 pro or over.  * We may need to set WINVER to make sure the compiler does not try to  * compile for on older version of win32, thus breaking the build.  * See  * http://msdn.microsoft.com/en-us/library/aa383745%28v=vs.85%29.aspx#setting_winver_or__win32_winnt  */
end_comment

begin_define
DECL|macro|WINVER
define|#
directive|define
name|WINVER
value|0x0500
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

begin_comment
comment|/* G_OS_WIN32 */
end_comment

begin_ifdef
ifdef|#
directive|ifdef
name|GDK_WINDOWING_QUARTZ
end_ifdef

begin_comment
comment|// only to get keycode definitions from HIToolbox/Events.h
end_comment

begin_include
include|#
directive|include
file|<Carbon/Carbon.h>
end_include

begin_include
include|#
directive|include
file|<Cocoa/Cocoa.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* GDK_WINDOWING_QUARTZ */
end_comment

begin_function
name|void
DECL|function|gimp_test_utils_set_env_to_subdir (const gchar * root_env_var,const gchar * subdir,const gchar * target_env_var)
name|gimp_test_utils_set_env_to_subdir
parameter_list|(
specifier|const
name|gchar
modifier|*
name|root_env_var
parameter_list|,
specifier|const
name|gchar
modifier|*
name|subdir
parameter_list|,
specifier|const
name|gchar
modifier|*
name|target_env_var
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|root_dir
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|target_dir
init|=
name|NULL
decl_stmt|;
comment|/* Get root dir */
name|root_dir
operator|=
name|g_getenv
argument_list|(
name|root_env_var
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|root_dir
condition|)
name|g_printerr
argument_list|(
literal|"*\n"
literal|"*  The env var %s is not set, you are probably running\n"
literal|"*  in a debugger. Set it manually, e.g.:\n"
literal|"*\n"
literal|"*    set env %s=%s/source/gimp\n"
literal|"*\n"
argument_list|,
name|root_env_var
argument_list|,
name|root_env_var
argument_list|,
name|g_get_home_dir
argument_list|()
argument_list|)
expr_stmt|;
comment|/* Construct path and setup target env var */
name|target_dir
operator|=
name|g_build_filename
argument_list|(
name|root_dir
argument_list|,
name|subdir
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_setenv
argument_list|(
name|target_env_var
argument_list|,
name|target_dir
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|target_dir
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_test_utils_set_env_to_subpath (const gchar * root_env_var1,const gchar * root_env_var2,const gchar * subdir,const gchar * target_env_var)
name|gimp_test_utils_set_env_to_subpath
parameter_list|(
specifier|const
name|gchar
modifier|*
name|root_env_var1
parameter_list|,
specifier|const
name|gchar
modifier|*
name|root_env_var2
parameter_list|,
specifier|const
name|gchar
modifier|*
name|subdir
parameter_list|,
specifier|const
name|gchar
modifier|*
name|target_env_var
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|root_dir1
init|=
name|NULL
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|root_dir2
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|target_dir1
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|target_dir2
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|target_path
init|=
name|NULL
decl_stmt|;
comment|/* Get root dir */
name|root_dir1
operator|=
name|g_getenv
argument_list|(
name|root_env_var1
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|root_dir1
condition|)
name|g_printerr
argument_list|(
literal|"*\n"
literal|"*  The env var %s is not set, you are probably running\n"
literal|"*  in a debugger. Set it manually, e.g.:\n"
literal|"*\n"
literal|"*    set env %s=%s/source/gimp\n"
literal|"*\n"
argument_list|,
name|root_env_var1
argument_list|,
name|root_env_var1
argument_list|,
name|g_get_home_dir
argument_list|()
argument_list|)
expr_stmt|;
name|root_dir2
operator|=
name|g_getenv
argument_list|(
name|root_env_var2
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|root_dir2
condition|)
name|g_printerr
argument_list|(
literal|"*\n"
literal|"*  The env var %s is not set, you are probably running\n"
literal|"*  in a debugger. Set it manually, e.g.:\n"
literal|"*\n"
literal|"*    set env %s=%s/source/gimp\n"
literal|"*\n"
argument_list|,
name|root_env_var2
argument_list|,
name|root_env_var2
argument_list|,
name|g_get_home_dir
argument_list|()
argument_list|)
expr_stmt|;
comment|/* Construct path and setup target env var */
name|target_dir1
operator|=
name|g_build_filename
argument_list|(
name|root_dir1
argument_list|,
name|subdir
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|target_dir2
operator|=
name|g_build_filename
argument_list|(
name|root_dir2
argument_list|,
name|subdir
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|target_path
operator|=
name|g_strconcat
argument_list|(
name|target_dir1
argument_list|,
name|G_SEARCHPATH_SEPARATOR_S
argument_list|,
name|target_dir2
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|target_dir1
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|target_dir2
argument_list|)
expr_stmt|;
name|g_setenv
argument_list|(
name|target_env_var
argument_list|,
name|target_path
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|target_path
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_test_utils_set_gimp3_directory:  * @root_env_var: Either "GIMP_TESTING_ABS_TOP_SRCDIR" or  *                "GIMP_TESTING_ABS_TOP_BUILDDIR"  * @subdir:       Subdir, may be %NULL  *  * Sets GIMP3_DIRECTORY to the source dir @root_env_var/@subdir. The  * environment variables is set up by the test runner, see Makefile.am  **/
end_comment

begin_function
name|void
DECL|function|gimp_test_utils_set_gimp3_directory (const gchar * root_env_var,const gchar * subdir)
name|gimp_test_utils_set_gimp3_directory
parameter_list|(
specifier|const
name|gchar
modifier|*
name|root_env_var
parameter_list|,
specifier|const
name|gchar
modifier|*
name|subdir
parameter_list|)
block|{
name|gimp_test_utils_set_env_to_subdir
argument_list|(
name|root_env_var
argument_list|,
name|subdir
argument_list|,
literal|"GIMP3_DIRECTORY"
comment|/*target_env_var*/
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_test_utils_setup_menus_path:  *  * Sets GIMP_TESTING_MENUS_PATH to "$top_srcdir/menus:$top_builddir/menus".  **/
end_comment

begin_function
name|void
DECL|function|gimp_test_utils_setup_menus_path (void)
name|gimp_test_utils_setup_menus_path
parameter_list|(
name|void
parameter_list|)
block|{
comment|/* GIMP_TESTING_ABS_TOP_SRCDIR is set by the automake test runner,    * see Makefile.am    */
name|gimp_test_utils_set_env_to_subpath
argument_list|(
literal|"GIMP_TESTING_ABS_TOP_SRCDIR"
argument_list|,
literal|"GIMP_TESTING_ABS_TOP_BUILDDIR"
argument_list|,
literal|"menus"
argument_list|,
literal|"GIMP_TESTING_MENUS_PATH"
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_test_utils_create_image:  * @gimp:   A #Gimp instance.  * @width:  Width of image (and layer)  * @height: Height of image (and layer)  *  * Creates a new image of a given size with one layer of same size and  * a display.  *  * Returns: The new #GimpImage.  **/
end_comment

begin_function
name|void
DECL|function|gimp_test_utils_create_image (Gimp * gimp,gint width,gint height)
name|gimp_test_utils_create_image
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
name|image
operator|=
name|gimp_image_new
argument_list|(
name|gimp
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|GIMP_RGB
argument_list|,
name|GIMP_PRECISION_U8_NON_LINEAR
argument_list|)
expr_stmt|;
name|layer
operator|=
name|gimp_layer_new
argument_list|(
name|image
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|gimp_image_get_layer_format
argument_list|(
name|image
argument_list|,
name|TRUE
argument_list|)
argument_list|,
literal|"layer1"
argument_list|,
literal|1.0
argument_list|,
name|GIMP_LAYER_MODE_NORMAL
argument_list|)
expr_stmt|;
name|gimp_image_add_layer
argument_list|(
name|image
argument_list|,
name|layer
argument_list|,
name|NULL
comment|/*parent*/
argument_list|,
literal|0
comment|/*position*/
argument_list|,
name|FALSE
comment|/*push_undo*/
argument_list|)
expr_stmt|;
name|gimp_create_display
argument_list|(
name|gimp
argument_list|,
name|image
argument_list|,
name|GIMP_UNIT_PIXEL
argument_list|,
literal|1.0
comment|/*scale*/
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_test_utils_synthesize_key_event:  * @widget: Widget to target.  * @keyval: Keyval, e.g. GDK_Return  *  * Simulates a keypress and release with gdk_test_simulate_key().  **/
end_comment

begin_function
name|void
DECL|function|gimp_test_utils_synthesize_key_event (GtkWidget * widget,guint keyval)
name|gimp_test_utils_synthesize_key_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|guint
name|keyval
parameter_list|)
block|{
if|#
directive|if
name|defined
argument_list|(
name|GDK_WINDOWING_QUARTZ
argument_list|)
name|GdkKeymapKey
modifier|*
name|keys
init|=
name|NULL
decl_stmt|;
name|gint
name|n_keys
init|=
literal|0
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|CGEventRef
name|keyUp
decl_stmt|,
name|keyDown
decl_stmt|;
if|if
condition|(
name|gdk_keymap_get_entries_for_keyval
argument_list|(
name|gdk_keymap_get_for_display
argument_list|(
name|gdk_display_get_default
argument_list|()
argument_list|)
argument_list|,
name|keyval
argument_list|,
operator|&
name|keys
argument_list|,
operator|&
name|n_keys
argument_list|)
condition|)
block|{
comment|/* XXX not in use yet */
name|CGEventRef
name|commandDown
init|=
name|CGEventCreateKeyboardEvent
argument_list|(
name|NULL
argument_list|,
operator|(
name|CGKeyCode
operator|)
name|kVK_Command
argument_list|,
name|true
argument_list|)
decl_stmt|;
name|CGEventRef
name|commandUp
init|=
name|CGEventCreateKeyboardEvent
argument_list|(
name|NULL
argument_list|,
operator|(
name|CGKeyCode
operator|)
name|kVK_Command
argument_list|,
name|false
argument_list|)
decl_stmt|;
name|CGEventRef
name|shiftDown
init|=
name|CGEventCreateKeyboardEvent
argument_list|(
name|NULL
argument_list|,
operator|(
name|CGKeyCode
operator|)
name|kVK_Shift
argument_list|,
name|true
argument_list|)
decl_stmt|;
name|CGEventRef
name|shiftUp
init|=
name|CGEventCreateKeyboardEvent
argument_list|(
name|NULL
argument_list|,
operator|(
name|CGKeyCode
operator|)
name|kVK_Shift
argument_list|,
name|false
argument_list|)
decl_stmt|;
name|CGEventRef
name|optionDown
init|=
name|CGEventCreateKeyboardEvent
argument_list|(
name|NULL
argument_list|,
operator|(
name|CGKeyCode
operator|)
name|kVK_Option
argument_list|,
name|true
argument_list|)
decl_stmt|;
name|CGEventRef
name|optionUp
init|=
name|CGEventCreateKeyboardEvent
argument_list|(
name|NULL
argument_list|,
operator|(
name|CGKeyCode
operator|)
name|kVK_Option
argument_list|,
name|false
argument_list|)
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_keys
condition|;
name|i
operator|++
control|)
block|{
comment|/* Option press. */
if|if
condition|(
name|keys
index|[
name|i
index|]
operator|.
name|group
condition|)
block|{
name|CGEventPost
argument_list|(
name|kCGHIDEventTap
argument_list|,
name|optionDown
argument_list|)
expr_stmt|;
block|}
comment|/* Shift press. */
if|if
condition|(
name|keys
index|[
name|i
index|]
operator|.
name|level
condition|)
block|{
name|CGEventPost
argument_list|(
name|kCGHIDEventTap
argument_list|,
name|shiftDown
argument_list|)
expr_stmt|;
block|}
name|keyDown
operator|=
name|CGEventCreateKeyboardEvent
argument_list|(
name|NULL
argument_list|,
operator|(
name|CGKeyCode
operator|)
name|keys
index|[
name|i
index|]
operator|.
name|keycode
argument_list|,
name|true
argument_list|)
expr_stmt|;
name|keyUp
operator|=
name|CGEventCreateKeyboardEvent
argument_list|(
name|NULL
argument_list|,
operator|(
name|CGKeyCode
operator|)
name|keys
index|[
name|i
index|]
operator|.
name|keycode
argument_list|,
name|false
argument_list|)
expr_stmt|;
comment|/* Key pressed. */
name|CGEventPost
argument_list|(
name|kCGHIDEventTap
argument_list|,
name|keyDown
argument_list|)
expr_stmt|;
name|CFRelease
argument_list|(
name|keyDown
argument_list|)
expr_stmt|;
name|usleep
argument_list|(
literal|100
argument_list|)
expr_stmt|;
comment|/* key released */
name|CGEventPost
argument_list|(
name|kCGHIDEventTap
argument_list|,
name|keyUp
argument_list|)
expr_stmt|;
name|CFRelease
argument_list|(
name|keyUp
argument_list|)
expr_stmt|;
comment|/* Shift release. */
if|if
condition|(
name|keys
index|[
name|i
index|]
operator|.
name|level
condition|)
block|{
name|CGEventPost
argument_list|(
name|kCGHIDEventTap
argument_list|,
name|shiftDown
argument_list|)
expr_stmt|;
block|}
comment|/* Option release. */
if|if
condition|(
name|keys
index|[
name|i
index|]
operator|.
name|group
condition|)
block|{
name|CGEventPost
argument_list|(
name|kCGHIDEventTap
argument_list|,
name|optionUp
argument_list|)
expr_stmt|;
block|}
comment|/* No need to loop for alternative keycodes. We want only one          * key generated. */
break|break;
block|}
name|CFRelease
argument_list|(
name|commandDown
argument_list|)
expr_stmt|;
name|CFRelease
argument_list|(
name|commandUp
argument_list|)
expr_stmt|;
name|CFRelease
argument_list|(
name|shiftDown
argument_list|)
expr_stmt|;
name|CFRelease
argument_list|(
name|shiftUp
argument_list|)
expr_stmt|;
name|CFRelease
argument_list|(
name|optionDown
argument_list|)
expr_stmt|;
name|CFRelease
argument_list|(
name|optionUp
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|keys
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_warning
argument_list|(
literal|"%s: no macOS key mapping found for keyval %d."
argument_list|,
name|G_STRFUNC
argument_list|,
name|keyval
argument_list|)
expr_stmt|;
block|}
else|#
directive|else
comment|/* ! GDK_WINDOWING_QUARTZ */
name|gdk_test_simulate_key
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|widget
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|,
operator|-
literal|1
argument_list|,
comment|/*x, y*/
name|keyval
argument_list|,
literal|0
comment|/*modifiers*/
argument_list|,
name|GDK_KEY_PRESS
argument_list|)
expr_stmt|;
name|gdk_test_simulate_key
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|widget
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|,
operator|-
literal|1
argument_list|,
comment|/*x, y*/
name|keyval
argument_list|,
literal|0
comment|/*modifiers*/
argument_list|,
name|GDK_KEY_RELEASE
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* ! GDK_WINDOWING_QUARTZ */
block|}
end_function

begin_comment
comment|/**  * gimp_test_utils_get_ui_manager:  * @gimp: The #Gimp instance.  *  * Returns the "best" #GimpUIManager to use when performing  * actions. It gives the ui manager of the empty display if it exists,  * otherwise it gives it the ui manager of the first display.  *  * Returns: The #GimpUIManager.  **/
end_comment

begin_function
name|GimpUIManager
modifier|*
DECL|function|gimp_test_utils_get_ui_manager (Gimp * gimp)
name|gimp_test_utils_get_ui_manager
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|display
init|=
name|NULL
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|NULL
decl_stmt|;
name|GtkWidget
modifier|*
name|toplevel
init|=
name|NULL
decl_stmt|;
name|GimpImageWindow
modifier|*
name|image_window
init|=
name|NULL
decl_stmt|;
name|GimpUIManager
modifier|*
name|ui_manager
init|=
name|NULL
decl_stmt|;
name|display
operator|=
name|GIMP_DISPLAY
argument_list|(
name|gimp_get_empty_display
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
comment|/* If there were not empty display, assume that there is at least    * one image display and use that    */
if|if
condition|(
operator|!
name|display
condition|)
name|display
operator|=
name|GIMP_DISPLAY
argument_list|(
name|gimp_get_display_iter
argument_list|(
name|gimp
argument_list|)
operator|->
name|data
argument_list|)
expr_stmt|;
name|shell
operator|=
name|gimp_display_get_shell
argument_list|(
name|display
argument_list|)
expr_stmt|;
name|toplevel
operator|=
name|gtk_widget_get_toplevel
argument_list|(
name|GTK_WIDGET
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|image_window
operator|=
name|GIMP_IMAGE_WINDOW
argument_list|(
name|toplevel
argument_list|)
expr_stmt|;
name|ui_manager
operator|=
name|gimp_image_window_get_ui_manager
argument_list|(
name|image_window
argument_list|)
expr_stmt|;
return|return
name|ui_manager
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_test_utils_create_image_from_dalog:  * @gimp:  *  * Creates a new image using the "New image" dialog, and then returns  * the #GimpImage created.  *  * Returns: The created #GimpImage.  **/
end_comment

begin_function
name|GimpImage
modifier|*
DECL|function|gimp_test_utils_create_image_from_dialog (Gimp * gimp)
name|gimp_test_utils_create_image_from_dialog
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|NULL
decl_stmt|;
name|GtkWidget
modifier|*
name|new_image_dialog
init|=
name|NULL
decl_stmt|;
name|guint
name|n_initial_images
init|=
name|g_list_length
argument_list|(
name|gimp_get_image_iter
argument_list|(
name|gimp
argument_list|)
argument_list|)
decl_stmt|;
name|guint
name|n_images
init|=
operator|-
literal|1
decl_stmt|;
name|gint
name|tries_left
init|=
literal|100
decl_stmt|;
name|GimpUIManager
modifier|*
name|ui_manager
init|=
name|gimp_test_utils_get_ui_manager
argument_list|(
name|gimp
argument_list|)
decl_stmt|;
comment|/* Bring up the new image dialog */
name|gimp_ui_manager_activate_action
argument_list|(
name|ui_manager
argument_list|,
literal|"image"
argument_list|,
literal|"image-new"
argument_list|)
expr_stmt|;
name|gimp_test_run_mainloop_until_idle
argument_list|()
expr_stmt|;
comment|/* Get the GtkWindow of the dialog */
name|new_image_dialog
operator|=
name|gimp_dialog_factory_dialog_raise
argument_list|(
name|gimp_dialog_factory_get_singleton
argument_list|()
argument_list|,
name|gdk_display_get_monitor
argument_list|(
name|gdk_display_get_default
argument_list|()
argument_list|,
literal|0
argument_list|)
argument_list|,
name|NULL
argument_list|,
literal|"gimp-image-new-dialog"
argument_list|,
operator|-
literal|1
comment|/*view_size*/
argument_list|)
expr_stmt|;
comment|/* Press the OK button. It will take a while for the image to be    * created so loop for a while    */
name|gtk_dialog_response
argument_list|(
name|GTK_DIALOG
argument_list|(
name|new_image_dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|)
expr_stmt|;
do|do
block|{
name|g_usleep
argument_list|(
literal|20
operator|*
literal|1000
argument_list|)
expr_stmt|;
name|gimp_test_run_mainloop_until_idle
argument_list|()
expr_stmt|;
name|n_images
operator|=
name|g_list_length
argument_list|(
name|gimp_get_image_iter
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
block|}
do|while
condition|(
name|tries_left
operator|--
operator|&&
name|n_images
operator|!=
name|n_initial_images
operator|+
literal|1
condition|)
do|;
comment|/* Make sure there now is one image more than initially */
name|g_assert_cmpint
argument_list|(
name|n_images
argument_list|,
operator|==
argument_list|,
name|n_initial_images
operator|+
literal|1
argument_list|)
expr_stmt|;
name|image
operator|=
name|GIMP_IMAGE
argument_list|(
name|gimp_get_image_iter
argument_list|(
name|gimp
argument_list|)
operator|->
name|data
argument_list|)
expr_stmt|;
return|return
name|image
return|;
block|}
end_function

end_unit

