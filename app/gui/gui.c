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
file|"libgimpwidgets/gimpwidgets-private.h"
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
file|"tools/gimp-tools.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdevices.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdevicestatus.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpitemfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpmenufactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpsessioninfo.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-utils.h"
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
file|"gui.h"
end_include

begin_include
include|#
directive|include
file|"gui-vtable.h"
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
file|"splash.h"
end_include

begin_include
include|#
directive|include
file|"themes.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gui_help_func
parameter_list|(
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
name|gpointer
name|help_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gui_get_background_func
parameter_list|(
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gui_get_foreground_func
parameter_list|(
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gui_initialize_after_callback
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpInitStatusFunc
name|callback
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gui_restore_callback
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpInitStatusFunc
name|callback
parameter_list|,
name|gboolean
name|restore_session
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gui_restore_after_callback
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpInitStatusFunc
name|callback
parameter_list|,
name|gboolean
name|restore_session
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gui_exit_callback
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gboolean
name|kill_it
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gui_exit_after_callback
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gboolean
name|kill_it
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
name|gui_device_change_notify
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
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  private variables  */
end_comment

begin_decl_stmt
DECL|variable|the_gui_gimp
specifier|static
name|Gimp
modifier|*
name|the_gui_gimp
init|=
name|NULL
decl_stmt|;
end_decl_stmt

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
DECL|variable|toolbox_item_factory
specifier|static
name|GimpItemFactory
modifier|*
name|toolbox_item_factory
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_item_factory
specifier|static
name|GimpItemFactory
modifier|*
name|image_item_factory
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|gboolean
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
name|GimpWidgetsVTable
name|vtable
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|mismatch
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|argc
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|argv
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gtk_init_check
argument_list|(
name|argc
argument_list|,
name|argv
argument_list|)
condition|)
return|return
name|FALSE
return|;
comment|/*  Initialize the eeky vtable needed by libgimpwidgets  */
name|vtable
operator|.
name|unit_get_number_of_units
operator|=
name|gimp_unit_get_number_of_units
expr_stmt|;
name|vtable
operator|.
name|unit_get_number_of_built_in_units
operator|=
name|gimp_unit_get_number_of_built_in_units
expr_stmt|;
name|vtable
operator|.
name|unit_get_factor
operator|=
name|gimp_unit_get_factor
expr_stmt|;
name|vtable
operator|.
name|unit_get_digits
operator|=
name|gimp_unit_get_digits
expr_stmt|;
name|vtable
operator|.
name|unit_get_identifier
operator|=
name|gimp_unit_get_identifier
expr_stmt|;
name|vtable
operator|.
name|unit_get_symbol
operator|=
name|gimp_unit_get_symbol
expr_stmt|;
name|vtable
operator|.
name|unit_get_abbreviation
operator|=
name|gimp_unit_get_abbreviation
expr_stmt|;
name|vtable
operator|.
name|unit_get_singular
operator|=
name|gimp_unit_get_singular
expr_stmt|;
name|vtable
operator|.
name|unit_get_plural
operator|=
name|gimp_unit_get_plural
expr_stmt|;
name|gimp_widgets_init
argument_list|(
operator|&
name|vtable
argument_list|,
name|gui_help_func
argument_list|,
name|gui_get_foreground_func
argument_list|,
name|gui_get_background_func
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_COLOR_SELECT
argument_list|)
expr_stmt|;
DECL|macro|REQUIRED_MAJOR
define|#
directive|define
name|REQUIRED_MAJOR
value|2
DECL|macro|REQUIRED_MINOR
define|#
directive|define
name|REQUIRED_MINOR
value|2
DECL|macro|REQUIRED_MICRO
define|#
directive|define
name|REQUIRED_MICRO
value|2
name|mismatch
operator|=
name|gtk_check_version
argument_list|(
name|REQUIRED_MAJOR
argument_list|,
name|REQUIRED_MINOR
argument_list|,
name|REQUIRED_MICRO
argument_list|)
expr_stmt|;
if|if
condition|(
name|mismatch
condition|)
block|{
name|gchar
modifier|*
name|message
decl_stmt|;
name|message
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s\n\n"
literal|"The GIMP requires Gtk+ version %d.%d.%d or later.\n"
literal|"Installed Gtk+ version is %d.%d.%d.\n\n"
literal|"Somehow you or your software packager managed\n"
literal|"to install The GIMP with an older Gtk+ version.\n\n"
literal|"Please upgrade to Gtk+ version %d.%d.%d or later."
argument_list|,
name|mismatch
argument_list|,
name|REQUIRED_MAJOR
argument_list|,
name|REQUIRED_MINOR
argument_list|,
name|REQUIRED_MICRO
argument_list|,
name|gtk_major_version
argument_list|,
name|gtk_minor_version
argument_list|,
name|gtk_micro_version
argument_list|,
name|REQUIRED_MAJOR
argument_list|,
name|REQUIRED_MINOR
argument_list|,
name|REQUIRED_MICRO
argument_list|)
expr_stmt|;
name|gimp_message_box
argument_list|(
name|GIMP_STOCK_WILBER_EEK
argument_list|,
name|NULL
argument_list|,
name|message
argument_list|,
operator|(
name|GtkCallback
operator|)
name|gtk_main_quit
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|message
argument_list|)
expr_stmt|;
name|gtk_main
argument_list|()
expr_stmt|;
name|exit
argument_list|(
name|EXIT_FAILURE
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|GimpInitStatusFunc
DECL|function|gui_init (Gimp * gimp,gboolean no_splash,gboolean no_splash_image)
name|gui_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gboolean
name|no_splash
parameter_list|,
name|gboolean
name|no_splash_image
parameter_list|)
block|{
name|GimpInitStatusFunc
name|status_callback
init|=
name|NULL
decl_stmt|;
name|GdkScreen
modifier|*
name|screen
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|the_gui_gimp
operator|==
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|the_gui_gimp
operator|=
name|gimp
expr_stmt|;
name|gimp_dnd_init
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|themes_init
argument_list|(
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
name|screen
operator|=
name|gdk_screen_get_default
argument_list|()
expr_stmt|;
name|gtk_widget_set_default_colormap
argument_list|(
name|gdk_screen_get_rgb_colormap
argument_list|(
name|screen
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|no_splash
condition|)
block|{
name|splash_create
argument_list|(
operator|!
name|no_splash_image
argument_list|)
expr_stmt|;
name|status_callback
operator|=
name|splash_update
expr_stmt|;
block|}
name|g_signal_connect_after
argument_list|(
name|gimp
argument_list|,
literal|"initialize"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gui_initialize_after_callback
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gimp
argument_list|,
literal|"restore"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gui_restore_callback
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect_after
argument_list|(
name|gimp
argument_list|,
literal|"restore"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gui_restore_after_callback
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gimp
argument_list|,
literal|"exit"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gui_exit_callback
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect_after
argument_list|(
name|gimp
argument_list|,
literal|"exit"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gui_exit_after_callback
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|status_callback
return|;
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
name|gimp_dialog_factory_dialog_new
argument_list|(
name|global_dialog_factory
argument_list|,
name|gdk_screen_get_default
argument_list|()
argument_list|,
literal|"gimp-tips-dialog"
argument_list|,
operator|-
literal|1
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
DECL|function|gui_help_func (const gchar * help_id,gpointer help_data)
name|gui_help_func
parameter_list|(
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
name|gpointer
name|help_data
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|the_gui_gimp
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_help
argument_list|(
name|the_gui_gimp
argument_list|,
name|NULL
argument_list|,
name|help_id
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gui_get_foreground_func (GimpRGB * color)
name|gui_get_foreground_func
parameter_list|(
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|color
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|the_gui_gimp
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_context_get_foreground
argument_list|(
name|gimp_get_user_context
argument_list|(
name|the_gui_gimp
argument_list|)
argument_list|,
name|color
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
DECL|function|gui_get_background_func (GimpRGB * color)
name|gui_get_background_func
parameter_list|(
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|color
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|the_gui_gimp
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_context_get_background
argument_list|(
name|gimp_get_user_context
argument_list|(
name|the_gui_gimp
argument_list|)
argument_list|,
name|color
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
DECL|function|gui_initialize_after_callback (Gimp * gimp,GimpInitStatusFunc status_callback)
name|gui_initialize_after_callback
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpInitStatusFunc
name|status_callback
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|name
init|=
name|NULL
decl_stmt|;
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
name|gimp
operator|->
name|be_verbose
condition|)
name|g_print
argument_list|(
literal|"INIT: gui_initialize_after_callback\n"
argument_list|)
expr_stmt|;
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
block|{
name|gchar
modifier|*
name|display
decl_stmt|;
name|display
operator|=
name|gdk_get_display
argument_list|()
expr_stmt|;
name|gimp_environ_table_add
argument_list|(
name|gimp
operator|->
name|environ_table
argument_list|,
name|name
argument_list|,
name|display
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|display
argument_list|)
expr_stmt|;
block|}
name|gimp_tools_init
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gui_restore_callback (Gimp * gimp,GimpInitStatusFunc status_callback,gboolean restore_session)
name|gui_restore_callback
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpInitStatusFunc
name|status_callback
parameter_list|,
name|gboolean
name|restore_session
parameter_list|)
block|{
name|GimpDisplayConfig
modifier|*
name|display_config
init|=
name|GIMP_DISPLAY_CONFIG
argument_list|(
name|gimp
operator|->
name|config
argument_list|)
decl_stmt|;
name|GimpGuiConfig
modifier|*
name|gui_config
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
name|gimp
operator|->
name|be_verbose
condition|)
name|g_print
argument_list|(
literal|"INIT: gui_restore_callback\n"
argument_list|)
expr_stmt|;
name|gui_vtable_init
argument_list|(
name|gimp
argument_list|)
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
if|if
condition|(
operator|!
name|gui_config
operator|->
name|show_tool_tips
condition|)
name|gimp_help_disable_tooltips
argument_list|()
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gui_config
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
name|g_signal_connect
argument_list|(
name|gimp_get_user_context
argument_list|(
name|gimp
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
name|gimp_get_screen_resolution
argument_list|(
name|NULL
argument_list|,
operator|&
name|xres
argument_list|,
operator|&
name|yres
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|gimp
operator|->
name|config
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
name|gui_device_change_notify
argument_list|)
expr_stmt|;
name|session_init
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
call|(
modifier|*
name|status_callback
call|)
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Tool Options"
argument_list|)
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|gimp_tools_restore
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gui_restore_after_callback (Gimp * gimp,GimpInitStatusFunc status_callback,gboolean restore_session)
name|gui_restore_after_callback
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpInitStatusFunc
name|status_callback
parameter_list|,
name|gboolean
name|restore_session
parameter_list|)
block|{
name|GimpGuiConfig
modifier|*
name|gui_config
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
name|gimp
operator|->
name|be_verbose
condition|)
name|g_print
argument_list|(
literal|"INIT: gui_restore_after_callback\n"
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|message_handler
operator|=
name|GIMP_MESSAGE_BOX
expr_stmt|;
if|if
condition|(
name|gui_config
operator|->
name|restore_accels
condition|)
name|menus_restore
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|toolbox_item_factory
operator|=
name|gimp_menu_factory_menu_new
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<Toolbox>"
argument_list|,
name|GTK_TYPE_MENU_BAR
argument_list|,
name|gimp
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|image_item_factory
operator|=
name|gimp_menu_factory_menu_new
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<Image>"
argument_list|,
name|GTK_TYPE_MENU
argument_list|,
name|gimp
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_devices_restore
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|status_callback
operator|==
name|splash_update
condition|)
name|splash_destroy
argument_list|()
expr_stmt|;
if|if
condition|(
name|gui_config
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
specifier|static
name|gboolean
DECL|function|gui_exit_callback (Gimp * gimp,gboolean kill_it)
name|gui_exit_callback
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gboolean
name|kill_it
parameter_list|)
block|{
name|GimpGuiConfig
modifier|*
name|gui_config
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
name|gimp
operator|->
name|be_verbose
condition|)
name|g_print
argument_list|(
literal|"EXIT: gui_exit_callback\n"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|kill_it
operator|&&
name|gimp_displays_dirty
argument_list|(
name|gimp
argument_list|)
condition|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|gimp_item_factories_set_sensitive
argument_list|(
literal|"<Toolbox>"
argument_list|,
literal|"/File/Quit"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_item_factories_set_sensitive
argument_list|(
literal|"<Image>"
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
name|NULL
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_FILE_QUIT_CONFIRM
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
name|gimp
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
comment|/* stop exit for now */
block|}
name|gimp
operator|->
name|message_handler
operator|=
name|GIMP_CONSOLE
expr_stmt|;
if|if
condition|(
name|gui_config
operator|->
name|save_session_info
condition|)
name|session_save
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|gui_config
operator|->
name|save_accels
condition|)
name|menus_save
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|gui_config
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
name|gimp_tools_save
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|gimp_tools_exit
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
comment|/* continue exiting */
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gui_exit_after_callback (Gimp * gimp,gboolean kill_it)
name|gui_exit_after_callback
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gboolean
name|kill_it
parameter_list|)
block|{
if|if
condition|(
name|gimp
operator|->
name|be_verbose
condition|)
name|g_print
argument_list|(
literal|"EXIT: gui_exit_after_callback\n"
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|gimp
operator|->
name|config
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
name|g_object_unref
argument_list|(
name|toolbox_item_factory
argument_list|)
expr_stmt|;
name|toolbox_item_factory
operator|=
name|NULL
expr_stmt|;
name|g_object_unref
argument_list|(
name|image_item_factory
argument_list|)
expr_stmt|;
name|image_item_factory
operator|=
name|NULL
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
name|themes_exit
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|g_type_class_unref
argument_list|(
name|g_type_class_peek
argument_list|(
name|GIMP_TYPE_COLOR_SELECT
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
comment|/* continue exiting */
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
name|Gimp
modifier|*
name|gimp
init|=
name|GIMP
argument_list|(
name|data
argument_list|)
decl_stmt|;
if|if
condition|(
name|quit
condition|)
block|{
name|gimp_exit
argument_list|(
name|gimp
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_item_factories_set_sensitive
argument_list|(
literal|"<Toolbox>"
argument_list|,
literal|"/File/Quit"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_item_factories_set_sensitive
argument_list|(
literal|"<Image>"
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

begin_function
specifier|static
name|void
DECL|function|gui_device_change_notify (Gimp * gimp)
name|gui_device_change_notify
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpSessionInfo
modifier|*
name|session_info
decl_stmt|;
name|session_info
operator|=
name|gimp_dialog_factory_find_session_info
argument_list|(
name|global_dock_factory
argument_list|,
literal|"gimp-device-status"
argument_list|)
expr_stmt|;
if|if
condition|(
name|session_info
operator|&&
name|session_info
operator|->
name|widget
condition|)
block|{
name|GtkWidget
modifier|*
name|device_status
decl_stmt|;
name|device_status
operator|=
name|GTK_BIN
argument_list|(
name|session_info
operator|->
name|widget
argument_list|)
operator|->
name|child
expr_stmt|;
name|gimp_device_status_update
argument_list|(
name|GIMP_DEVICE_STATUS
argument_list|(
name|device_status
argument_list|)
argument_list|)
expr_stmt|;
block|}
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
name|GimpItemFactory
modifier|*
name|item_factory
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|NULL
decl_stmt|;
name|item_factory
operator|=
name|gimp_item_factory_from_path
argument_list|(
literal|"<Image>"
argument_list|)
expr_stmt|;
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
name|gimp_item_factory_update
argument_list|(
name|item_factory
argument_list|,
name|shell
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gui_image_disconnect (GimpImage * gimage,Gimp * gimp)
name|gui_image_disconnect
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
comment|/*  check if this is the last image and if it had a display  */
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
operator|&&
name|gimage
operator|->
name|instance_count
operator|>
literal|0
condition|)
block|{
name|dialogs_show_toolbox
argument_list|()
expr_stmt|;
block|}
block|}
end_function

end_unit

