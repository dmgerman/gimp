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
file|"tools/tools-types.h"
end_include

begin_include
include|#
directive|include
file|"widgets/widgets-types.h"
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
file|"core/gimpimage.h"
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
file|"docindex.h"
end_include

begin_include
include|#
directive|include
file|"errorconsole.h"
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
file|"gximage.h"
end_include

begin_include
include|#
directive|include
file|"image_render.h"
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
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"app_procs.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_comment
comment|/* for gdisplay_*_override_cursor()  */
end_comment

begin_include
include|#
directive|include
file|"gdisplay_ops.h"
end_include

begin_comment
comment|/* for gdisplay_xserver_resolution() */
end_comment

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
name|gui_display_new
parameter_list|(
name|GimpImage
modifier|*
name|gimage
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
name|GDisplay
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
name|gui_image_destroy
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
name|gui_image_mode_changed
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
name|gui_image_colormap_changed
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|ncol
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

begin_function_decl
specifier|static
name|void
name|gui_image_size_changed
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
name|gui_image_alpha_changed
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
name|gui_image_update
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  global variables  */
end_comment

begin_decl_stmt
specifier|extern
name|GSList
modifier|*
name|display_list
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  from gdisplay.c  */
end_comment

begin_comment
comment|/*  private variables  */
end_comment

begin_decl_stmt
DECL|variable|image_destroy_handler_id
specifier|static
name|GQuark
name|image_destroy_handler_id
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_mode_changed_handler_id
specifier|static
name|GQuark
name|image_mode_changed_handler_id
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_colormap_changed_handler_id
specifier|static
name|GQuark
name|image_colormap_changed_handler_id
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
DECL|variable|image_size_changed_handler_id
specifier|static
name|GQuark
name|image_size_changed_handler_id
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_alpha_changed_handler_id
specifier|static
name|GQuark
name|image_alpha_changed_handler_id
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_update_handler_id
specifier|static
name|GQuark
name|image_update_handler_id
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

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
name|gimp
operator|->
name|create_display_func
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
if|if
condition|(
name|gimprc
operator|.
name|always_restore_session
condition|)
name|restore_session
operator|=
name|TRUE
expr_stmt|;
name|image_destroy_handler_id
operator|=
name|gimp_container_add_handler
argument_list|(
name|gimp
operator|->
name|images
argument_list|,
literal|"destroy"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gui_image_destroy
argument_list|)
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
name|image_mode_changed_handler_id
operator|=
name|gimp_container_add_handler
argument_list|(
name|gimp
operator|->
name|images
argument_list|,
literal|"mode_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gui_image_mode_changed
argument_list|)
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
name|image_colormap_changed_handler_id
operator|=
name|gimp_container_add_handler
argument_list|(
name|gimp
operator|->
name|images
argument_list|,
literal|"colormap_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gui_image_colormap_changed
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
name|GTK_SIGNAL_FUNC
argument_list|(
name|gui_image_name_changed
argument_list|)
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
name|image_size_changed_handler_id
operator|=
name|gimp_container_add_handler
argument_list|(
name|gimp
operator|->
name|images
argument_list|,
literal|"size_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gui_image_size_changed
argument_list|)
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
name|image_alpha_changed_handler_id
operator|=
name|gimp_container_add_handler
argument_list|(
name|gimp
operator|->
name|images
argument_list|,
literal|"alpha_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gui_image_alpha_changed
argument_list|)
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
name|image_update_handler_id
operator|=
name|gimp_container_add_handler
argument_list|(
name|gimp
operator|->
name|images
argument_list|,
literal|"update"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gui_image_update
argument_list|)
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
argument_list|)
argument_list|,
literal|"display_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
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
name|gdisplay_xserver_resolution
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
name|file_open_dialog_menu_init
argument_list|()
expr_stmt|;
name|file_save_dialog_menu_init
argument_list|()
expr_stmt|;
name|menus_reorder_plugins
argument_list|()
expr_stmt|;
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
argument_list|()
expr_stmt|;
name|session_init
argument_list|()
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
name|gimp_dialog_factory_dialog_new
argument_list|(
name|global_dialog_factory
argument_list|,
literal|"gimp:toolbox"
argument_list|)
expr_stmt|;
comment|/*  Fill the "last opened" menu items with the first last_opened_size    *  elements of the docindex    */
block|{
name|FILE
modifier|*
name|fp
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|filenames
init|=
name|g_new0
argument_list|(
name|gchar
operator|*
argument_list|,
name|gimprc
operator|.
name|last_opened_size
argument_list|)
decl_stmt|;
name|gint
name|i
decl_stmt|;
if|if
condition|(
operator|(
name|fp
operator|=
name|document_index_parse_init
argument_list|()
operator|)
condition|)
block|{
comment|/*  read the filenames...  */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|gimprc
operator|.
name|last_opened_size
condition|;
name|i
operator|++
control|)
if|if
condition|(
operator|(
name|filenames
index|[
name|i
index|]
operator|=
name|document_index_parse_line
argument_list|(
name|fp
argument_list|)
operator|)
operator|==
name|NULL
condition|)
break|break;
comment|/*  ...and add them in reverse order  */
for|for
control|(
operator|--
name|i
init|;
name|i
operator|>=
literal|0
condition|;
name|i
operator|--
control|)
block|{
name|menus_last_opened_add
argument_list|(
name|filenames
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filenames
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|filenames
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gui_restore (Gimp * gimp)
name|gui_restore
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|color_select_init
argument_list|()
expr_stmt|;
name|devices_restore
argument_list|()
expr_stmt|;
name|session_restore
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
name|session_save
argument_list|()
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
name|menus_quit
argument_list|()
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
name|document_index_free
argument_list|()
expr_stmt|;
name|error_console_free
argument_list|()
expr_stmt|;
name|tool_options_dialog_free
argument_list|()
expr_stmt|;
name|toolbox_free
argument_list|()
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
name|image_destroy_handler_id
argument_list|)
expr_stmt|;
name|gimp_container_remove_handler
argument_list|(
name|gimp
operator|->
name|images
argument_list|,
name|image_mode_changed_handler_id
argument_list|)
expr_stmt|;
name|gimp_container_remove_handler
argument_list|(
name|gimp
operator|->
name|images
argument_list|,
name|image_colormap_changed_handler_id
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
name|gimp_container_remove_handler
argument_list|(
name|gimp
operator|->
name|images
argument_list|,
name|image_size_changed_handler_id
argument_list|)
expr_stmt|;
name|gimp_container_remove_handler
argument_list|(
name|gimp
operator|->
name|images
argument_list|,
name|image_alpha_changed_handler_id
argument_list|)
expr_stmt|;
name|gimp_container_remove_handler
argument_list|(
name|gimp
operator|->
name|images
argument_list|,
name|image_update_handler_id
argument_list|)
expr_stmt|;
name|image_destroy_handler_id
operator|=
literal|0
expr_stmt|;
name|image_mode_changed_handler_id
operator|=
literal|0
expr_stmt|;
name|image_colormap_changed_handler_id
operator|=
literal|0
expr_stmt|;
name|image_name_changed_handler_id
operator|=
literal|0
expr_stmt|;
name|image_size_changed_handler_id
operator|=
literal|0
expr_stmt|;
name|image_alpha_changed_handler_id
operator|=
literal|0
expr_stmt|;
name|image_update_handler_id
operator|=
literal|0
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gui_really_quit_dialog (void)
name|gui_really_quit_dialog
parameter_list|(
name|void
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
name|_
argument_list|(
literal|"Quit"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Cancel"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gui_really_quit_callback
argument_list|,
name|NULL
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
DECL|function|gui_display_new (GimpImage * gimage)
name|gui_display_new
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|gdisp
operator|=
name|gdisplay_new
argument_list|(
name|gimage
argument_list|,
literal|0x0101
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
name|gtk_signal_connect_after
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gdisp
operator|->
name|canvas
argument_list|)
argument_list|,
literal|"expose_event"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gui_rotate_the_shield_harmonics
argument_list|)
argument_list|,
name|NULL
argument_list|)
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
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
comment|/* Canvases */
for|for
control|(
name|list
operator|=
name|display_list
init|;
name|list
condition|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|gdisp
operator|=
operator|(
name|GDisplay
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|gdisplay_install_override_cursor
argument_list|(
name|gdisp
argument_list|,
name|GDK_WATCH
argument_list|)
expr_stmt|;
block|}
comment|/* Dialogs */
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
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
comment|/* Canvases */
for|for
control|(
name|list
operator|=
name|display_list
init|;
name|list
condition|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|gdisp
operator|=
operator|(
name|GDisplay
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|gdisplay_remove_override_cursor
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
block|}
comment|/* Dialogs */
name|gimp_dialog_factories_unidle
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
name|gtk_signal_disconnect_by_func
argument_list|(
name|GTK_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gui_rotate_the_shield_harmonics
argument_list|)
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
name|gdk_window_get_size
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
name|gdk_draw_pixmap
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
if|if
condition|(
name|quit
condition|)
block|{
name|app_exit_finish
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
DECL|function|gui_display_changed (GimpContext * context,GDisplay * display,gpointer data)
name|gui_display_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GDisplay
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
name|gdisplay_set_menu_sensitivity
argument_list|(
name|display
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gui_image_destroy (GimpImage * gimage,gpointer data)
name|gui_image_destroy
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
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gui_image_mode_changed (GimpImage * gimage,gpointer data)
name|gui_image_mode_changed
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
name|gimp_image_invalidate_layer_previews
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|gimp_viewable_invalidate_preview
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|gdisplays_update_title
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|gdisplays_update_full
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gui_image_colormap_changed (GimpImage * gimage,gint ncol,gpointer data)
name|gui_image_colormap_changed
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|ncol
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
name|gimp_image_base_type
argument_list|(
name|gimage
argument_list|)
operator|==
name|INDEXED
condition|)
name|gdisplays_update_full
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
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
name|gdisplays_update_title
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|palette_import_image_renamed
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gui_image_size_changed (GimpImage * gimage,gpointer data)
name|gui_image_size_changed
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
comment|/*  shrink wrap and update all views  */
name|gdisplays_resize_cursor_label
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|gdisplays_update_full
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|gdisplays_shrink_wrap
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gui_image_alpha_changed (GimpImage * gimage,gpointer data)
name|gui_image_alpha_changed
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
name|gdisplays_update_title
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gui_image_update (GimpImage * gimage,gint x,gint y,gint w,gint h,gpointer data)
name|gui_image_update
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
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
name|gdisplays_update_area
argument_list|(
name|gimage
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

