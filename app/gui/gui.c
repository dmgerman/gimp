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
file|"core/gimpdatafiles.h"
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
file|"display/gximage.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"brush-select.h"
end_include

begin_include
include|#
directive|include
file|"color-select.h"
end_include

begin_include
include|#
directive|include
file|"devices.h"
end_include

begin_include
include|#
directive|include
file|"dialogs.h"
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
file|"gradient-select.h"
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
file|"palette-select.h"
end_include

begin_include
include|#
directive|include
file|"palette-import-dialog.h"
end_include

begin_include
include|#
directive|include
file|"pattern-select.h"
end_include

begin_include
include|#
directive|include
file|"session.h"
end_include

begin_include
include|#
directive|include
file|"tool-options-dialog.h"
end_include

begin_include
include|#
directive|include
file|"toolbox.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
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
name|gpointer
name|data
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

begin_function_decl
specifier|static
name|void
name|gui_image_name_changed
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
DECL|variable|image_name_changed_handler_id
specifier|static
name|GQuark
name|image_name_changed_handler_id
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
specifier|static
name|void
DECL|function|gui_themes_dir_foreach_func (const gchar * filename,gpointer loader_data)
name|gui_themes_dir_foreach_func
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gpointer
name|loader_data
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
name|loader_data
expr_stmt|;
name|basename
operator|=
name|g_path_get_basename
argument_list|(
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
literal|"adding theme \"%s\" (%s)\n"
argument_list|)
argument_list|,
name|basename
argument_list|,
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
name|filename
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

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
ifdef|#
directive|ifdef
name|HAVE_PUTENV
name|gchar
modifier|*
name|display_env
decl_stmt|;
endif|#
directive|endif
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
ifdef|#
directive|ifdef
name|HAVE_PUTENV
name|display_env
operator|=
name|g_strconcat
argument_list|(
literal|"DISPLAY="
argument_list|,
name|gdk_get_display
argument_list|()
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|putenv
argument_list|(
name|display_env
argument_list|)
expr_stmt|;
endif|#
directive|endif
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
name|gimp_stock_init
argument_list|()
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
name|gimprc
operator|.
name|theme_path
condition|)
block|{
name|gimp_datafiles_read_directories
argument_list|(
name|gimprc
operator|.
name|theme_path
argument_list|,
name|TYPE_DIRECTORY
argument_list|,
name|gui_themes_dir_foreach_func
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|gimprc
operator|.
name|theme
condition|)
name|theme_dir
operator|=
name|g_hash_table_lookup
argument_list|(
name|themes_hash
argument_list|,
name|gimprc
operator|.
name|theme
argument_list|)
expr_stmt|;
else|else
name|theme_dir
operator|=
name|g_hash_table_lookup
argument_list|(
name|themes_hash
argument_list|,
literal|"Default"
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
literal|"parsing \"%s\"\n"
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
literal|"parsing \"%s\"\n"
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
name|gimprc
operator|.
name|show_tool_tips
condition|)
name|gimp_help_disable_tooltips
argument_list|()
expr_stmt|;
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
name|gui_create_display_func
operator|=
name|gui_display_new
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
name|image_name_changed_handler_id
operator|=
name|gimp_container_add_handler
argument_list|(
name|gimp
operator|->
name|images
argument_list|,
literal|"name_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gui_image_name_changed
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
name|gimprc
operator|.
name|monitor_xres
operator|<
name|GIMP_MIN_RESOLUTION
operator|||
name|gimprc
operator|.
name|monitor_yres
operator|<
name|GIMP_MIN_RESOLUTION
condition|)
block|{
name|gui_get_screen_resolution
argument_list|(
operator|&
name|gimprc
operator|.
name|monitor_xres
argument_list|,
operator|&
name|gimprc
operator|.
name|monitor_yres
argument_list|)
expr_stmt|;
name|gimprc
operator|.
name|using_xserver_resolution
operator|=
name|TRUE
expr_stmt|;
block|}
name|menus_init
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|DISPLAY_FILTERS
name|color_display_init
argument_list|()
expr_stmt|;
endif|#
directive|endif
comment|/* DISPLAY_FILTERS */
name|gximage_init
argument_list|()
expr_stmt|;
name|render_setup
argument_list|(
name|gimprc
operator|.
name|transparency_type
argument_list|,
name|gimprc
operator|.
name|transparency_size
argument_list|)
expr_stmt|;
name|dialogs_init
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|devices_init
argument_list|(
name|gimp
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
name|file_open_dialog_menu_init
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|file_save_dialog_menu_init
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|menus_restore
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|gimp_dialog_factory_dialog_new
argument_list|(
name|global_dialog_factory
argument_list|,
literal|"gimp:toolbox"
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|color_select_init
argument_list|()
expr_stmt|;
name|devices_restore
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimprc
operator|.
name|always_restore_session
operator|||
name|restore_session
condition|)
name|session_restore
argument_list|(
name|gimp
argument_list|)
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
name|gimprc
operator|.
name|show_tips
condition|)
block|{
name|gimp_dialog_factory_dialog_new
argument_list|(
name|global_dialog_factory
argument_list|,
literal|"gimp:tips-dialog"
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
name|session_save
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|device_status_free
argument_list|()
expr_stmt|;
name|brush_dialog_free
argument_list|()
expr_stmt|;
name|pattern_dialog_free
argument_list|()
expr_stmt|;
name|palette_dialog_free
argument_list|()
expr_stmt|;
name|gradient_dialog_free
argument_list|()
expr_stmt|;
name|gdisplays_delete
argument_list|()
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
name|gximage_free
argument_list|()
expr_stmt|;
name|render_free
argument_list|()
expr_stmt|;
name|dialogs_exit
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
comment|/*  handle this in the dialog factory:  */
name|tool_options_dialog_free
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|toolbox_free
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|gimp_help_free
argument_list|()
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
name|gimp_container_remove_handler
argument_list|(
name|gimp
operator|->
name|images
argument_list|,
name|image_name_changed_handler_id
argument_list|)
expr_stmt|;
name|image_disconnect_handler_id
operator|=
literal|0
expr_stmt|;
name|image_name_changed_handler_id
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
name|widthMM
decl_stmt|,
name|heightMM
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
name|widthMM
operator|=
name|gdk_screen_width_mm
argument_list|()
expr_stmt|;
name|heightMM
operator|=
name|gdk_screen_height_mm
argument_list|()
expr_stmt|;
comment|/*    * From xdpyinfo.c:    *    * there are 2.54 centimeters to an inch; so there are 25.4 millimeters.    *    *     dpi = N pixels / (M millimeters / (25.4 millimeters / 1 inch))    *         = N pixels / (M inch / 25.4)    *         = N * 25.4 pixels / M inch    */
operator|*
name|xres
operator|=
operator|(
name|width
operator|*
literal|25.4
operator|)
operator|/
operator|(
operator|(
name|gdouble
operator|)
name|widthMM
operator|)
expr_stmt|;
operator|*
name|yres
operator|=
operator|(
name|height
operator|*
literal|25.4
operator|)
operator|/
operator|(
operator|(
name|gdouble
operator|)
name|heightMM
operator|)
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
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|menus_set_sensitive
argument_list|(
literal|"<Toolbox>/File/Quit"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|menus_set_sensitive
argument_list|(
literal|"<Image>/File/Quit"
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
literal|"Really Quit?"
argument_list|)
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"dialogs/really_quit.html"
argument_list|,
name|TRUE
argument_list|,
name|_
argument_list|(
literal|"Some files unsaved.\n\nQuit the GIMP?"
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
DECL|function|gui_set_busy (Gimp * gimp)
name|gui_set_busy
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|gdisplays_set_busy
argument_list|()
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
name|gdisplays_unset_busy
argument_list|()
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
name|gdk_drawable_unref
argument_list|(
name|pixmap
argument_list|)
expr_stmt|;
name|gdk_drawable_unref
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
name|menus_set_sensitive
argument_list|(
literal|"<Toolbox>/File/Quit"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|menus_set_sensitive
argument_list|(
literal|"<Image>/File/Quit"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  FIXME: this junk should mostly go to the display subsystem  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gui_display_changed (GimpContext * context,GimpDisplay * display,gpointer data)
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
if|if
condition|(
name|display
condition|)
name|gimp_display_shell_set_menu_sensitivity
argument_list|(
name|GIMP_DISPLAY_SHELL
argument_list|(
name|display
operator|->
name|shell
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|gimp_display_shell_set_menu_sensitivity
argument_list|(
name|NULL
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
name|gimp_dialog_factory_dialog_raise
argument_list|(
name|global_dialog_factory
argument_list|,
literal|"gimp:toolbox"
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gui_image_name_changed (GimpImage * gimage,gpointer data)
name|gui_image_name_changed
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
name|palette_import_image_renamed
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

