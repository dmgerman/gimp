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
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<stdio.h>
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
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"gui-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpguiconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpenvirontable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay-foreach.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell-render.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdevices.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpitemfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"device-status-dialog.h"
end_include

begin_include
include|#
directive|include
file|"dialogs.h"
end_include

begin_include
include|#
directive|include
file|"dialogs-commands.h"
end_include

begin_include
include|#
directive|include
file|"error-console-dialog.h"
end_include

begin_include
include|#
directive|include
file|"file-open-dialog.h"
end_include

begin_include
include|#
directive|include
file|"file-save-dialog.h"
end_include

begin_include
include|#
directive|include
file|"gui.h"
end_include

begin_include
include|#
directive|include
file|"menus.h"
end_include

begin_include
include|#
directive|include
file|"session.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_include
include|#
directive|include
file|"pixmaps/wilber2.xpm"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gui_main
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gui_main_quit
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gui_set_busy
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gui_unset_busy
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gui_message
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpObject
modifier|*
name|gui_display_new
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|guint
name|scale
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gui_themes_dir_foreach_func
parameter_list|(
name|GimpDatafileData
modifier|*
name|file_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|gui_rotate_the_shield_harmonics
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|eevent
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gui_really_quit_callback
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|gboolean
name|quit
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gui_show_tooltips_notify
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
name|GParamSpec
modifier|*
name|param_spec
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gui_display_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gui_image_disconnect
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  private variables  */
end_comment

begin_decl_stmt
DECL|variable|image_disconnect_handler_id
specifier|static
name|GQuark
name|image_disconnect_handler_id
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|themes_hash
specifier|static
name|GHashTable
modifier|*
name|themes_hash
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gui_libs_init (gint * argc,gchar *** argv)
name|gui_libs_init
parameter_list|(
name|gint
modifier|*
name|argc
parameter_list|,
name|gchar
modifier|*
modifier|*
modifier|*
name|argv
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|argc
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|argv
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gtk_init
argument_list|(
name|argc
argument_list|,
name|argv
argument_list|)
expr_stmt|;
name|gimp_widgets_init
argument_list|()
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_COLOR_SELECT
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gui_environ_init (Gimp * gimp)
name|gui_environ_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|gchar
modifier|*
name|name
init|=
name|NULL
decl_stmt|;
if|#
directive|if
name|defined
argument_list|(
name|GDK_WINDOWING_X11
argument_list|)
name|name
operator|=
literal|"DISPLAY"
expr_stmt|;
elif|#
directive|elif
name|defined
argument_list|(
name|GDK_WINDOWING_DIRECTFB
argument_list|)
operator|||
name|defined
argument_list|(
name|GDK_WINDOWING_FB
argument_list|)
name|name
operator|=
literal|"GDK_DISPLAY"
expr_stmt|;
endif|#
directive|endif
comment|/* TODO: Need to care about display migration with GTK+ 2.2 at some point */
if|if
condition|(
name|name
condition|)
name|gimp_environ_table_add
argument_list|(
name|gimp
operator|->
name|environ_table
argument_list|,
name|name
argument_list|,
name|gdk_get_display
argument_list|()
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gui_themes_init (Gimp * gimp)
name|gui_themes_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpGuiConfig
modifier|*
name|config
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|theme_dir
decl_stmt|;
name|gchar
modifier|*
name|gtkrc
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|config
operator|=
name|GIMP_GUI_CONFIG
argument_list|(
name|gimp
operator|->
name|config
argument_list|)
expr_stmt|;
name|themes_hash
operator|=
name|g_hash_table_new_full
argument_list|(
name|g_str_hash
argument_list|,
name|g_str_equal
argument_list|,
name|g_free
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
if|if
condition|(
name|config
operator|->
name|theme_path
condition|)
block|{
name|gimp_datafiles_read_directories
argument_list|(
name|config
operator|->
name|theme_path
argument_list|,
name|G_FILE_TEST_IS_DIR
argument_list|,
name|gui_themes_dir_foreach_func
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
block|}
name|theme_dir
operator|=
name|gui_themes_get_theme_dir
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|theme_dir
condition|)
block|{
name|gtkrc
operator|=
name|g_build_filename
argument_list|(
name|theme_dir
argument_list|,
literal|"gtkrc"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/*  get the hardcoded default theme gtkrc  */
name|gtkrc
operator|=
name|g_strdup
argument_list|(
name|gimp_gtkrc
argument_list|()
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|gimp
operator|->
name|be_verbose
condition|)
name|g_print
argument_list|(
name|_
argument_list|(
literal|"Parsing '%s'\n"
argument_list|)
argument_list|,
name|gtkrc
argument_list|)
expr_stmt|;
name|gtk_rc_parse
argument_list|(
name|gtkrc
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|gtkrc
argument_list|)
expr_stmt|;
comment|/*  parse the user gtkrc  */
name|gtkrc
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"gtkrc"
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|be_verbose
condition|)
name|g_print
argument_list|(
name|_
argument_list|(
literal|"Parsing '%s'\n"
argument_list|)
argument_list|,
name|gtkrc
argument_list|)
expr_stmt|;
name|gtk_rc_parse
argument_list|(
name|gtkrc
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|gtkrc
argument_list|)
expr_stmt|;
comment|/*  tooltips  */
name|gimp_help_init
argument_list|()
expr_stmt|;
if|if
condition|(
operator|!
name|config
operator|->
name|show_tool_tips
condition|)
name|gimp_help_disable_tooltips
argument_list|()
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp
operator|->
name|config
argument_list|)
argument_list|,
literal|"notify::show-tool-tips"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gui_show_tooltips_notify
argument_list|)
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
name|gdk_rgb_set_min_colors
argument_list|(
name|CLAMP
argument_list|(
name|gimp
operator|->
name|config
operator|->
name|min_colors
argument_list|,
literal|27
argument_list|,
literal|256
argument_list|)
argument_list|)
expr_stmt|;
name|gdk_rgb_set_install
argument_list|(
name|gimp
operator|->
name|config
operator|->
name|install_cmap
argument_list|)
expr_stmt|;
name|gtk_widget_set_default_colormap
argument_list|(
name|gdk_rgb_get_colormap
argument_list|()
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gui_themes_get_theme_dir (Gimp * gimp)
name|gui_themes_get_theme_dir
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpGuiConfig
modifier|*
name|config
init|=
name|GIMP_GUI_CONFIG
argument_list|(
name|gimp
operator|->
name|config
argument_list|)
decl_stmt|;
if|if
condition|(
name|config
operator|->
name|theme
condition|)
return|return
name|g_hash_table_lookup
argument_list|(
name|themes_hash
argument_list|,
name|config
operator|->
name|theme
argument_list|)
return|;
return|return
name|g_hash_table_lookup
argument_list|(
name|themes_hash
argument_list|,
literal|"Default"
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gui_init (Gimp * gimp)
name|gui_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpDisplayConfig
modifier|*
name|display_config
decl_stmt|;
name|GimpGuiConfig
modifier|*
name|gui_config
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|display_config
operator|=
name|GIMP_DISPLAY_CONFIG
argument_list|(
name|gimp
operator|->
name|config
argument_list|)
expr_stmt|;
name|gui_config
operator|=
name|GIMP_GUI_CONFIG
argument_list|(
name|gimp
operator|->
name|config
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|gui_main_loop_func
operator|=
name|gui_main
expr_stmt|;
name|gimp
operator|->
name|gui_main_loop_quit_func
operator|=
name|gui_main_quit
expr_stmt|;
name|gimp
operator|->
name|gui_set_busy_func
operator|=
name|gui_set_busy
expr_stmt|;
name|gimp
operator|->
name|gui_unset_busy_func
operator|=
name|gui_unset_busy
expr_stmt|;
name|gimp
operator|->
name|gui_message_func
operator|=
name|gui_message
expr_stmt|;
name|gimp
operator|->
name|gui_create_display_func
operator|=
name|gui_display_new
expr_stmt|;
name|image_disconnect_handler_id
operator|=
name|gimp_container_add_handler
argument_list|(
name|gimp
operator|->
name|images
argument_list|,
literal|"disconnect"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gui_image_disconnect
argument_list|)
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
argument_list|)
argument_list|,
literal|"display_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gui_display_changed
argument_list|)
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
comment|/* make sure the monitor resolution is valid */
if|if
condition|(
name|display_config
operator|->
name|monitor_res_from_gdk
operator|||
name|display_config
operator|->
name|monitor_xres
operator|<
name|GIMP_MIN_RESOLUTION
operator|||
name|display_config
operator|->
name|monitor_yres
operator|<
name|GIMP_MIN_RESOLUTION
condition|)
block|{
name|gdouble
name|xres
decl_stmt|,
name|yres
decl_stmt|;
name|gui_get_screen_resolution
argument_list|(
operator|&
name|xres
argument_list|,
operator|&
name|yres
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp
operator|->
name|config
argument_list|)
argument_list|,
literal|"monitor-xresolution"
argument_list|,
name|xres
argument_list|,
literal|"monitor-yresolution"
argument_list|,
name|yres
argument_list|,
literal|"monitor-resolution-from-windowing-system"
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|menus_init
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|render_init
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|dialogs_init
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|gimp_devices_init
argument_list|(
name|gimp
argument_list|,
name|device_status_dialog_update_current
argument_list|)
expr_stmt|;
name|session_init
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gui_restore (Gimp * gimp,gboolean restore_session)
name|gui_restore
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gboolean
name|restore_session
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|message_handler
operator|=
name|GIMP_MESSAGE_BOX
expr_stmt|;
name|file_open_dialog_menu_init
argument_list|(
name|gimp
argument_list|,
name|gimp_item_factory_from_path
argument_list|(
literal|"<Load>"
argument_list|)
argument_list|)
expr_stmt|;
name|file_save_dialog_menu_init
argument_list|(
name|gimp
argument_list|,
name|gimp_item_factory_from_path
argument_list|(
literal|"<Save>"
argument_list|)
argument_list|)
expr_stmt|;
name|menus_restore
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|gimp_devices_restore
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_GUI_CONFIG
argument_list|(
name|gimp
operator|->
name|config
argument_list|)
operator|->
name|restore_session
operator|||
name|restore_session
condition|)
name|session_restore
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|dialogs_show_toolbox
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gui_post_init (Gimp * gimp)
name|gui_post_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_GUI_CONFIG
argument_list|(
name|gimp
operator|->
name|config
argument_list|)
operator|->
name|show_tips
condition|)
block|{
name|gimp_dialog_factory_dialog_new
argument_list|(
name|global_dialog_factory
argument_list|,
literal|"gimp-tips-dialog"
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gui_shutdown (Gimp * gimp)
name|gui_shutdown
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|message_handler
operator|=
name|GIMP_CONSOLE
expr_stmt|;
name|session_save
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_GUI_CONFIG
argument_list|(
name|gimp
operator|->
name|config
argument_list|)
operator|->
name|save_device_status
condition|)
name|gimp_devices_save
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|gimp_displays_delete
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gui_exit (Gimp * gimp)
name|gui_exit
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|menus_exit
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|render_exit
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|dialogs_exit
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|gimp_devices_exit
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|gimp_help_free
argument_list|()
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp
operator|->
name|config
argument_list|)
argument_list|,
name|gui_show_tooltips_notify
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
name|gimp_container_remove_handler
argument_list|(
name|gimp
operator|->
name|images
argument_list|,
name|image_disconnect_handler_id
argument_list|)
expr_stmt|;
name|image_disconnect_handler_id
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|themes_hash
condition|)
block|{
name|g_hash_table_destroy
argument_list|(
name|themes_hash
argument_list|)
expr_stmt|;
name|themes_hash
operator|=
name|NULL
expr_stmt|;
block|}
name|g_type_class_unref
argument_list|(
name|g_type_class_peek
argument_list|(
name|GIMP_TYPE_COLOR_SELECT
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gui_get_screen_resolution (gdouble * xres,gdouble * yres)
name|gui_get_screen_resolution
parameter_list|(
name|gdouble
modifier|*
name|xres
parameter_list|,
name|gdouble
modifier|*
name|yres
parameter_list|)
block|{
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|width_mm
decl_stmt|,
name|height_mm
decl_stmt|;
name|gdouble
name|x
init|=
literal|0.0
decl_stmt|;
name|gdouble
name|y
init|=
literal|0.0
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|xres
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|yres
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|width
operator|=
name|gdk_screen_width
argument_list|()
expr_stmt|;
name|height
operator|=
name|gdk_screen_height
argument_list|()
expr_stmt|;
name|width_mm
operator|=
name|gdk_screen_width_mm
argument_list|()
expr_stmt|;
name|height_mm
operator|=
name|gdk_screen_height_mm
argument_list|()
expr_stmt|;
comment|/*    * From xdpyinfo.c:    *    * there are 2.54 centimeters to an inch; so there are 25.4 millimeters.    *    *     dpi = N pixels / (M millimeters / (25.4 millimeters / 1 inch))    *         = N pixels / (M inch / 25.4)    *         = N * 25.4 pixels / M inch    */
if|if
condition|(
name|width_mm
operator|>
literal|0
operator|&&
name|height_mm
operator|>
literal|0
condition|)
block|{
name|x
operator|=
operator|(
name|width
operator|*
literal|25.4
operator|)
operator|/
operator|(
name|gdouble
operator|)
name|width_mm
expr_stmt|;
name|y
operator|=
operator|(
name|height
operator|*
literal|25.4
operator|)
operator|/
operator|(
name|gdouble
operator|)
name|height_mm
expr_stmt|;
block|}
if|if
condition|(
name|x
operator|<
name|GIMP_MIN_RESOLUTION
operator|||
name|x
operator|>
name|GIMP_MAX_RESOLUTION
operator|||
name|y
operator|<
name|GIMP_MIN_RESOLUTION
operator|||
name|y
operator|>
name|GIMP_MAX_RESOLUTION
condition|)
block|{
name|g_warning
argument_list|(
literal|"GDK returned bogus values for the screen resolution, "
literal|"using 75 dpi instead."
argument_list|)
expr_stmt|;
name|x
operator|=
literal|75.0
expr_stmt|;
name|y
operator|=
literal|75.0
expr_stmt|;
block|}
operator|*
name|xres
operator|=
name|x
expr_stmt|;
operator|*
name|yres
operator|=
name|y
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gui_really_quit_dialog (GCallback quit_func)
name|gui_really_quit_dialog
parameter_list|(
name|GCallback
name|quit_func
parameter_list|)
block|{
name|GtkItemFactory
modifier|*
name|item_factory
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|item_factory
operator|=
name|GTK_ITEM_FACTORY
argument_list|(
name|gimp_item_factory_from_path
argument_list|(
literal|"<Toolbox>"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_item_factory_set_sensitive
argument_list|(
name|item_factory
argument_list|,
literal|"/File/Quit"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|item_factory
operator|=
name|GTK_ITEM_FACTORY
argument_list|(
name|gimp_item_factory_from_path
argument_list|(
literal|"<Image>"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_item_factory_set_sensitive
argument_list|(
name|item_factory
argument_list|,
literal|"/File/Quit"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|gimp_query_boolean_box
argument_list|(
name|_
argument_list|(
literal|"Quit The GIMP?"
argument_list|)
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"dialogs/really_quit.html"
argument_list|,
name|GIMP_STOCK_WILBER_EEK
argument_list|,
name|_
argument_list|(
literal|"Some files are unsaved.\n"
literal|"\nReally quit The GIMP?"
argument_list|)
argument_list|,
name|GTK_STOCK_QUIT
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gui_really_quit_callback
argument_list|,
name|quit_func
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
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
DECL|function|gui_main (Gimp * gimp)
name|gui_main
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|gtk_main
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gui_main_quit (Gimp * gimp)
name|gui_main_quit
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|gtk_main_quit
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gui_set_busy (Gimp * gimp)
name|gui_set_busy
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|gimp_displays_set_busy
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|gimp_dialog_factories_idle
argument_list|()
expr_stmt|;
name|gdk_flush
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gui_unset_busy (Gimp * gimp)
name|gui_unset_busy
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|gimp_displays_unset_busy
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|gimp_dialog_factories_unidle
argument_list|()
expr_stmt|;
name|gdk_flush
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gui_message (Gimp * gimp,const gchar * message)
name|gui_message
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|)
block|{
switch|switch
condition|(
name|gimp
operator|->
name|message_handler
condition|)
block|{
case|case
name|GIMP_MESSAGE_BOX
case|:
name|gimp_message_box
argument_list|(
name|message
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_ERROR_CONSOLE
case|:
name|gimp_dialog_factory_dialog_raise
argument_list|(
name|global_dock_factory
argument_list|,
literal|"gimp-error-console"
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|error_console_add
argument_list|(
name|gimp
argument_list|,
name|message
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
end_function

begin_decl_stmt
DECL|variable|double_speed
name|gboolean
name|double_speed
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|GimpObject
modifier|*
DECL|function|gui_display_new (GimpImage * gimage,guint scale)
name|gui_display_new
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|guint
name|scale
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
name|gdisp
operator|=
name|gimp_display_new
argument_list|(
name|gimage
argument_list|,
name|scale
argument_list|)
expr_stmt|;
name|gimp_context_set_display
argument_list|(
name|gimp_get_user_context
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|)
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
if|if
condition|(
name|double_speed
condition|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|g_signal_connect_after
argument_list|(
name|G_OBJECT
argument_list|(
name|shell
operator|->
name|canvas
argument_list|)
argument_list|,
literal|"expose_event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gui_rotate_the_shield_harmonics
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
return|return
name|GIMP_OBJECT
argument_list|(
name|gdisp
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gui_themes_dir_foreach_func (GimpDatafileData * file_data)
name|gui_themes_dir_foreach_func
parameter_list|(
name|GimpDatafileData
modifier|*
name|file_data
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|gchar
modifier|*
name|basename
decl_stmt|;
name|gimp
operator|=
operator|(
name|Gimp
operator|*
operator|)
name|file_data
operator|->
name|user_data
expr_stmt|;
name|basename
operator|=
name|g_path_get_basename
argument_list|(
name|file_data
operator|->
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|be_verbose
condition|)
name|g_print
argument_list|(
name|_
argument_list|(
literal|"Adding theme '%s' (%s)\n"
argument_list|)
argument_list|,
name|basename
argument_list|,
name|file_data
operator|->
name|filename
argument_list|)
expr_stmt|;
name|g_hash_table_insert
argument_list|(
name|themes_hash
argument_list|,
name|basename
argument_list|,
name|g_strdup
argument_list|(
name|file_data
operator|->
name|filename
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|gui_rotate_the_shield_harmonics (GtkWidget * widget,GdkEvent * eevent,gpointer data)
name|gui_rotate_the_shield_harmonics
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|eevent
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GdkPixmap
modifier|*
name|pixmap
init|=
name|NULL
decl_stmt|;
name|GdkBitmap
modifier|*
name|mask
init|=
name|NULL
decl_stmt|;
name|gint
name|width
init|=
literal|0
decl_stmt|;
name|gint
name|height
init|=
literal|0
decl_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
name|gui_rotate_the_shield_harmonics
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|pixmap
operator|=
name|gdk_pixmap_create_from_xpm_d
argument_list|(
name|widget
operator|->
name|window
argument_list|,
operator|&
name|mask
argument_list|,
name|NULL
argument_list|,
name|wilber2_xpm
argument_list|)
expr_stmt|;
name|gdk_drawable_get_size
argument_list|(
name|pixmap
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
if|if
condition|(
name|widget
operator|->
name|allocation
operator|.
name|width
operator|>=
name|width
operator|&&
name|widget
operator|->
name|allocation
operator|.
name|height
operator|>=
name|height
condition|)
block|{
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|x
operator|=
operator|(
name|widget
operator|->
name|allocation
operator|.
name|width
operator|-
name|width
operator|)
operator|/
literal|2
expr_stmt|;
name|y
operator|=
operator|(
name|widget
operator|->
name|allocation
operator|.
name|height
operator|-
name|height
operator|)
operator|/
literal|2
expr_stmt|;
name|gdk_gc_set_clip_mask
argument_list|(
name|widget
operator|->
name|style
operator|->
name|black_gc
argument_list|,
name|mask
argument_list|)
expr_stmt|;
name|gdk_gc_set_clip_origin
argument_list|(
name|widget
operator|->
name|style
operator|->
name|black_gc
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|gdk_draw_drawable
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
name|pixmap
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|gdk_gc_set_clip_mask
argument_list|(
name|widget
operator|->
name|style
operator|->
name|black_gc
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gdk_gc_set_clip_origin
argument_list|(
name|widget
operator|->
name|style
operator|->
name|black_gc
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|pixmap
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|mask
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
DECL|function|gui_really_quit_callback (GtkWidget * button,gboolean quit,gpointer data)
name|gui_really_quit_callback
parameter_list|(
name|GtkWidget
modifier|*
name|button
parameter_list|,
name|gboolean
name|quit
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GCallback
name|quit_func
decl_stmt|;
name|quit_func
operator|=
name|G_CALLBACK
argument_list|(
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|quit
condition|)
block|{
call|(
modifier|*
name|quit_func
call|)
argument_list|()
expr_stmt|;
block|}
else|else
block|{
name|GtkItemFactory
modifier|*
name|item_factory
decl_stmt|;
name|item_factory
operator|=
name|GTK_ITEM_FACTORY
argument_list|(
name|gimp_item_factory_from_path
argument_list|(
literal|"<Toolbox>"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_item_factory_set_sensitive
argument_list|(
name|item_factory
argument_list|,
literal|"/File/Quit"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|item_factory
operator|=
name|GTK_ITEM_FACTORY
argument_list|(
name|gimp_item_factory_from_path
argument_list|(
literal|"<Image>"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_item_factory_set_sensitive
argument_list|(
name|item_factory
argument_list|,
literal|"/File/Quit"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gui_show_tooltips_notify (GObject * config,GParamSpec * param_spec,Gimp * gimp)
name|gui_show_tooltips_notify
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
name|GParamSpec
modifier|*
name|param_spec
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|gboolean
name|show_tool_tips
decl_stmt|;
name|g_object_get
argument_list|(
name|config
argument_list|,
literal|"show-tool-tips"
argument_list|,
operator|&
name|show_tool_tips
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|show_tool_tips
condition|)
name|gimp_help_enable_tooltips
argument_list|()
expr_stmt|;
else|else
name|gimp_help_disable_tooltips
argument_list|()
expr_stmt|;
block|}
end_function

begin_ifdef
ifdef|#
directive|ifdef
name|__GNUC__
end_ifdef

begin_warning
warning|#
directive|warning
warning|FIXME: this junk should mostly go to the display subsystem
end_warning

begin_endif
endif|#
directive|endif
end_endif

begin_function
specifier|static
name|void
DECL|function|gui_display_changed (GimpContext * context,GimpDisplay * display,Gimp * gimp)
name|gui_display_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|display
condition|)
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|display
operator|->
name|shell
argument_list|)
expr_stmt|;
name|gimp_display_shell_set_menu_sensitivity
argument_list|(
name|shell
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gui_image_disconnect (GimpImage * gimage,gpointer data)
name|gui_image_disconnect
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|gimp
operator|=
operator|(
name|Gimp
operator|*
operator|)
name|data
expr_stmt|;
comment|/*  check if this is the last image  */
if|if
condition|(
name|gimp_container_num_children
argument_list|(
name|gimp
operator|->
name|images
argument_list|)
operator|==
literal|1
condition|)
block|{
name|dialogs_show_toolbox
argument_list|()
expr_stmt|;
block|}
block|}
end_function

end_unit

