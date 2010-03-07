begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 2009 Martin Nordholts<martinn@src.gnome.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|<stdlib.h>
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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"dialogs/dialogs-types.h"
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
file|"display/gimpdisplayshell-transform.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpimagewindow.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdocked.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdockwindow.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpsessioninfo.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimptoolbox.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimptooloptionseditor.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpuimanager.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptooloptions.h"
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

begin_define
DECL|macro|GIMP_UI_WINDOW_POSITION_EPSILON
define|#
directive|define
name|GIMP_UI_WINDOW_POSITION_EPSILON
value|10
end_define

begin_define
DECL|macro|GIMP_UI_WINDOW_POSITION_EPSILON
define|#
directive|define
name|GIMP_UI_WINDOW_POSITION_EPSILON
value|10
end_define

begin_define
DECL|macro|GIMP_UI_POSITION_EPSILON
define|#
directive|define
name|GIMP_UI_POSITION_EPSILON
value|1
end_define

begin_define
DECL|macro|GIMP_UI_POSITION_EPSILON
define|#
directive|define
name|GIMP_UI_POSITION_EPSILON
value|1
end_define

begin_typedef
DECL|typedef|GimpUiTestFunc
typedef|typedef
name|gboolean
function_decl|(
modifier|*
name|GimpUiTestFunc
function_decl|)
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon29589ac80108
block|{
DECL|member|avoid_sizeof_zero
name|int
name|avoid_sizeof_zero
decl_stmt|;
DECL|typedef|GimpTestFixture
block|}
name|GimpTestFixture
typedef|;
end_typedef

begin_function_decl
specifier|static
name|void
name|gimp_ui_tool_options_editor_updates
parameter_list|(
name|GimpTestFixture
modifier|*
name|fixture
parameter_list|,
name|gconstpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_ui_create_new_image_via_dialog
parameter_list|(
name|GimpTestFixture
modifier|*
name|fixture
parameter_list|,
name|gconstpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_ui_restore_recently_closed_dock
parameter_list|(
name|GimpTestFixture
modifier|*
name|fixture
parameter_list|,
name|gconstpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_ui_tab_toggle_dont_change_position
parameter_list|(
name|GimpTestFixture
modifier|*
name|fixture
parameter_list|,
name|gconstpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_ui_switch_to_single_window_mode
parameter_list|(
name|GimpTestFixture
modifier|*
name|fixture
parameter_list|,
name|gconstpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_ui_hide_docks_in_single_window_mode
parameter_list|(
name|GimpTestFixture
modifier|*
name|fixture
parameter_list|,
name|gconstpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_ui_show_docks_in_single_window_mode
parameter_list|(
name|GimpTestFixture
modifier|*
name|fixture
parameter_list|,
name|gconstpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_ui_switch_back_to_multi_window_mode
parameter_list|(
name|GimpTestFixture
modifier|*
name|fixture
parameter_list|,
name|gconstpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpUIManager
modifier|*
name|gimp_ui_get_ui_manager
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
name|gimp_ui_synthesize_delete_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|gimp_ui_find_dock_window
parameter_list|(
name|GimpDialogFactory
modifier|*
name|dialog_factory
parameter_list|,
name|GimpUiTestFunc
name|predicate
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_ui_not_toolbox_window
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function
DECL|function|main (int argc,char ** argv)
name|int
name|main
parameter_list|(
name|int
name|argc
parameter_list|,
name|char
modifier|*
modifier|*
name|argv
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
init|=
name|NULL
decl_stmt|;
name|gint
name|result
init|=
operator|-
literal|1
decl_stmt|;
name|g_type_init
argument_list|()
expr_stmt|;
name|gtk_init
argument_list|(
operator|&
name|argc
argument_list|,
operator|&
name|argv
argument_list|)
expr_stmt|;
name|g_test_init
argument_list|(
operator|&
name|argc
argument_list|,
operator|&
name|argv
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_test_utils_set_gimp2_directory
argument_list|(
literal|"GIMP_TESTING_ABS_TOP_SRCDIR"
argument_list|,
literal|"app/tests/gimpdir"
argument_list|)
expr_stmt|;
name|gimp_test_utils_setup_menus_dir
argument_list|()
expr_stmt|;
comment|/* Start up GIMP */
name|gimp
operator|=
name|gimp_init_for_gui_testing
argument_list|(
name|FALSE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_test_run_mainloop_until_idle
argument_list|()
expr_stmt|;
comment|/* Setup the tests */
name|g_test_add
argument_list|(
literal|"/gimp-ui/tool-options-editor-updates"
argument_list|,
name|GimpTestFixture
argument_list|,
name|gimp
argument_list|,
name|NULL
argument_list|,
name|gimp_ui_tool_options_editor_updates
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_test_add
argument_list|(
literal|"/gimp-ui/create-new-image-via-dialog"
argument_list|,
name|GimpTestFixture
argument_list|,
name|gimp
argument_list|,
name|NULL
argument_list|,
name|gimp_ui_create_new_image_via_dialog
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_test_add
argument_list|(
literal|"/gimp-ui/restore-recently-closed-dock"
argument_list|,
name|GimpTestFixture
argument_list|,
name|gimp
argument_list|,
name|NULL
argument_list|,
name|gimp_ui_restore_recently_closed_dock
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_test_add
argument_list|(
literal|"/gimp-ui/tab-toggle-dont-change-dock-window-position"
argument_list|,
name|GimpTestFixture
argument_list|,
name|gimp
argument_list|,
name|NULL
argument_list|,
name|gimp_ui_tab_toggle_dont_change_position
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_test_add
argument_list|(
literal|"/gimp-ui/switch-to-single-window-mode"
argument_list|,
name|GimpTestFixture
argument_list|,
name|gimp
argument_list|,
name|NULL
argument_list|,
name|gimp_ui_switch_to_single_window_mode
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_test_add
argument_list|(
literal|"/gimp-ui/hide-docks-in-single-window-mode"
argument_list|,
name|GimpTestFixture
argument_list|,
name|gimp
argument_list|,
name|NULL
argument_list|,
name|gimp_ui_hide_docks_in_single_window_mode
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_test_add
argument_list|(
literal|"/gimp-ui/show-docks-in-single-window-mode"
argument_list|,
name|GimpTestFixture
argument_list|,
name|gimp
argument_list|,
name|NULL
argument_list|,
name|gimp_ui_show_docks_in_single_window_mode
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_test_add
argument_list|(
literal|"/gimp-ui/switch-back-to-multi-window-mode"
argument_list|,
name|GimpTestFixture
argument_list|,
name|gimp
argument_list|,
name|NULL
argument_list|,
name|gimp_ui_switch_back_to_multi_window_mode
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* Run the tests and return status */
name|result
operator|=
name|g_test_run
argument_list|()
expr_stmt|;
comment|/* Don't write files to the source dir */
name|gimp_test_utils_set_gimp2_directory
argument_list|(
literal|"GIMP_TESTING_ABS_TOP_BUILDDIR"
argument_list|,
literal|"app/tests/gimpdir-output"
argument_list|)
expr_stmt|;
comment|/* Exit properly so we don't break script-fu plug-in wire */
name|gimp_exit
argument_list|(
name|gimp
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
return|return
name|result
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_ui_tool_options_editor_updates:  * @fixture:  * @data:  *  * Makes sure that the tool options editor is updated when the tool  * changes.  **/
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_ui_tool_options_editor_updates (GimpTestFixture * fixture,gconstpointer data)
name|gimp_ui_tool_options_editor_updates
parameter_list|(
name|GimpTestFixture
modifier|*
name|fixture
parameter_list|,
name|gconstpointer
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
name|GimpDisplay
modifier|*
name|display
init|=
name|GIMP_DISPLAY
argument_list|(
name|gimp_get_empty_display
argument_list|(
name|gimp
argument_list|)
argument_list|)
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|gimp_display_get_shell
argument_list|(
name|display
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|toplevel
init|=
name|gtk_widget_get_toplevel
argument_list|(
name|GTK_WIDGET
argument_list|(
name|shell
argument_list|)
argument_list|)
decl_stmt|;
name|GimpImageWindow
modifier|*
name|image_window
init|=
name|GIMP_IMAGE_WINDOW
argument_list|(
name|toplevel
argument_list|)
decl_stmt|;
name|GimpUIManager
modifier|*
name|ui_manager
init|=
name|gimp_image_window_get_ui_manager
argument_list|(
name|image_window
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|dockable
init|=
name|gimp_dialog_factory_dialog_new
argument_list|(
name|gimp_dialog_factory_get_singleton
argument_list|()
argument_list|,
name|gtk_widget_get_screen
argument_list|(
name|toplevel
argument_list|)
argument_list|,
literal|"gimp-tool-options"
argument_list|,
operator|-
literal|1
comment|/*view_size*/
argument_list|,
name|FALSE
comment|/*present*/
argument_list|)
decl_stmt|;
name|GimpToolOptionsEditor
modifier|*
name|editor
init|=
name|GIMP_TOOL_OPTIONS_EDITOR
argument_list|(
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|dockable
argument_list|)
argument_list|)
argument_list|)
decl_stmt|;
comment|/* First select the rect select tool */
name|gimp_ui_manager_activate_action
argument_list|(
name|ui_manager
argument_list|,
literal|"tools"
argument_list|,
literal|"tools-rect-select"
argument_list|)
expr_stmt|;
name|g_assert_cmpstr
argument_list|(
name|GIMP_HELP_TOOL_RECT_SELECT
argument_list|,
operator|==
argument_list|,
name|gimp_tool_options_editor_get_tool_options
argument_list|(
name|editor
argument_list|)
operator|->
name|tool_info
operator|->
name|help_id
argument_list|)
expr_stmt|;
comment|/* Change tool and make sure the change is taken into account by the    * tool options editor    */
name|gimp_ui_manager_activate_action
argument_list|(
name|ui_manager
argument_list|,
literal|"tools"
argument_list|,
literal|"tools-ellipse-select"
argument_list|)
expr_stmt|;
name|g_assert_cmpstr
argument_list|(
name|GIMP_HELP_TOOL_ELLIPSE_SELECT
argument_list|,
operator|==
argument_list|,
name|gimp_tool_options_editor_get_tool_options
argument_list|(
name|editor
argument_list|)
operator|->
name|tool_info
operator|->
name|help_id
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_ui_create_new_image_via_dialog (GimpTestFixture * fixture,gconstpointer data)
name|gimp_ui_create_new_image_via_dialog
parameter_list|(
name|GimpTestFixture
modifier|*
name|fixture
parameter_list|,
name|gconstpointer
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
name|GimpDisplay
modifier|*
name|display
init|=
name|GIMP_DISPLAY
argument_list|(
name|gimp_get_empty_display
argument_list|(
name|gimp
argument_list|)
argument_list|)
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|gimp_display_get_shell
argument_list|(
name|display
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|toplevel
init|=
name|gtk_widget_get_toplevel
argument_list|(
name|GTK_WIDGET
argument_list|(
name|shell
argument_list|)
argument_list|)
decl_stmt|;
name|GimpImageWindow
modifier|*
name|image_window
init|=
name|GIMP_IMAGE_WINDOW
argument_list|(
name|toplevel
argument_list|)
decl_stmt|;
name|GimpUIManager
modifier|*
name|ui_manager
init|=
name|gimp_image_window_get_ui_manager
argument_list|(
name|image_window
argument_list|)
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
name|gtk_widget_get_screen
argument_list|(
name|GTK_WIDGET
argument_list|(
name|shell
argument_list|)
argument_list|)
argument_list|,
literal|"gimp-image-new-dialog"
argument_list|,
operator|-
literal|1
comment|/*view_size*/
argument_list|)
expr_stmt|;
comment|/* Press the focused widget, it should be the Ok button. It will    * take a while for the image to be created to loop for a while    */
name|gtk_widget_activate
argument_list|(
name|gtk_window_get_focus
argument_list|(
name|GTK_WINDOW
argument_list|(
name|new_image_dialog
argument_list|)
argument_list|)
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_ui_restore_recently_closed_dock (GimpTestFixture * fixture,gconstpointer data)
name|gimp_ui_restore_recently_closed_dock
parameter_list|(
name|GimpTestFixture
modifier|*
name|fixture
parameter_list|,
name|gconstpointer
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
name|GtkWidget
modifier|*
name|dock_window
init|=
name|NULL
decl_stmt|;
name|gint
name|n_session_infos_before_close
init|=
operator|-
literal|1
decl_stmt|;
name|gint
name|n_session_infos_after_close
init|=
operator|-
literal|1
decl_stmt|;
name|gint
name|n_session_infos_after_restore
init|=
operator|-
literal|1
decl_stmt|;
name|GList
modifier|*
name|session_infos
init|=
name|NULL
decl_stmt|;
comment|/* Find a non-toolbox dock window */
name|dock_window
operator|=
name|gimp_ui_find_dock_window
argument_list|(
name|gimp_dialog_factory_get_singleton
argument_list|()
argument_list|,
name|gimp_ui_not_toolbox_window
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|dock_window
operator|!=
name|NULL
argument_list|)
expr_stmt|;
comment|/* Count number of docks */
name|session_infos
operator|=
name|gimp_dialog_factory_get_session_infos
argument_list|(
name|gimp_dialog_factory_get_singleton
argument_list|()
argument_list|)
expr_stmt|;
name|n_session_infos_before_close
operator|=
name|g_list_length
argument_list|(
name|session_infos
argument_list|)
expr_stmt|;
comment|/* Close one of the dock windows */
name|gimp_ui_synthesize_delete_event
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dock_window
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_test_run_mainloop_until_idle
argument_list|()
expr_stmt|;
comment|/* Make sure the number of session infos went down */
name|session_infos
operator|=
name|gimp_dialog_factory_get_session_infos
argument_list|(
name|gimp_dialog_factory_get_singleton
argument_list|()
argument_list|)
expr_stmt|;
name|n_session_infos_after_close
operator|=
name|g_list_length
argument_list|(
name|session_infos
argument_list|)
expr_stmt|;
name|g_assert_cmpint
argument_list|(
name|n_session_infos_before_close
argument_list|,
operator|>
argument_list|,
name|n_session_infos_after_close
argument_list|)
expr_stmt|;
comment|/* Restore the (only avaiable) closed dock and make sure the session    * infos in the global dock factory are increased again    */
name|gimp_ui_manager_activate_action
argument_list|(
name|gimp_ui_get_ui_manager
argument_list|(
name|gimp
argument_list|)
argument_list|,
literal|"windows"
argument_list|,
comment|/* FIXME: This is severly hardcoded */
literal|"windows-recent-0003"
argument_list|)
expr_stmt|;
name|gimp_test_run_mainloop_until_idle
argument_list|()
expr_stmt|;
name|session_infos
operator|=
name|gimp_dialog_factory_get_session_infos
argument_list|(
name|gimp_dialog_factory_get_singleton
argument_list|()
argument_list|)
expr_stmt|;
name|n_session_infos_after_restore
operator|=
name|g_list_length
argument_list|(
name|session_infos
argument_list|)
expr_stmt|;
name|g_assert_cmpint
argument_list|(
name|n_session_infos_after_close
argument_list|,
operator|<
argument_list|,
name|n_session_infos_after_restore
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_ui_tab_toggle_dont_change_position:  * @fixture:  * @data:  *  * Makes sure that when dock windows are hidden with Tab and shown  * again, their positions and sizes are not changed. We don't really  * use Tab though, we only simulate its effect.  **/
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_ui_tab_toggle_dont_change_position (GimpTestFixture * fixture,gconstpointer data)
name|gimp_ui_tab_toggle_dont_change_position
parameter_list|(
name|GimpTestFixture
modifier|*
name|fixture
parameter_list|,
name|gconstpointer
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
name|GtkWidget
modifier|*
name|dock_window
init|=
name|NULL
decl_stmt|;
name|gint
name|x_before_hide
init|=
operator|-
literal|1
decl_stmt|;
name|gint
name|y_before_hide
init|=
operator|-
literal|1
decl_stmt|;
name|gint
name|w_before_hide
init|=
operator|-
literal|1
decl_stmt|;
name|gint
name|h_before_hide
init|=
operator|-
literal|1
decl_stmt|;
name|gint
name|x_after_show
init|=
operator|-
literal|1
decl_stmt|;
name|gint
name|y_after_show
init|=
operator|-
literal|1
decl_stmt|;
name|gint
name|w_after_show
init|=
operator|-
literal|1
decl_stmt|;
name|gint
name|h_after_show
init|=
operator|-
literal|1
decl_stmt|;
comment|/* Find a non-toolbox dock window */
name|dock_window
operator|=
name|gimp_ui_find_dock_window
argument_list|(
name|gimp_dialog_factory_get_singleton
argument_list|()
argument_list|,
name|gimp_ui_not_toolbox_window
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|dock_window
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|gtk_widget_get_visible
argument_list|(
name|dock_window
argument_list|)
argument_list|)
expr_stmt|;
comment|/* Get the position and size */
name|gimp_test_run_mainloop_until_idle
argument_list|()
expr_stmt|;
name|gtk_window_get_position
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dock_window
argument_list|)
argument_list|,
operator|&
name|x_before_hide
argument_list|,
operator|&
name|y_before_hide
argument_list|)
expr_stmt|;
name|gtk_window_get_size
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dock_window
argument_list|)
argument_list|,
operator|&
name|w_before_hide
argument_list|,
operator|&
name|h_before_hide
argument_list|)
expr_stmt|;
comment|/* Hide all dock windows */
name|gimp_ui_manager_activate_action
argument_list|(
name|gimp_ui_get_ui_manager
argument_list|(
name|gimp
argument_list|)
argument_list|,
literal|"windows"
argument_list|,
literal|"windows-hide-docks"
argument_list|)
expr_stmt|;
name|gimp_test_run_mainloop_until_idle
argument_list|()
expr_stmt|;
name|g_assert
argument_list|(
operator|!
name|gtk_widget_get_visible
argument_list|(
name|dock_window
argument_list|)
argument_list|)
expr_stmt|;
comment|/* Show them again */
name|gimp_ui_manager_activate_action
argument_list|(
name|gimp_ui_get_ui_manager
argument_list|(
name|gimp
argument_list|)
argument_list|,
literal|"windows"
argument_list|,
literal|"windows-hide-docks"
argument_list|)
expr_stmt|;
name|gimp_test_run_mainloop_until_idle
argument_list|()
expr_stmt|;
name|g_assert
argument_list|(
name|gtk_widget_get_visible
argument_list|(
name|dock_window
argument_list|)
argument_list|)
expr_stmt|;
comment|/* Get the position and size again and make sure it's the same as    * before    */
name|gtk_window_get_position
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dock_window
argument_list|)
argument_list|,
operator|&
name|x_after_show
argument_list|,
operator|&
name|y_after_show
argument_list|)
expr_stmt|;
name|gtk_window_get_size
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dock_window
argument_list|)
argument_list|,
operator|&
name|w_after_show
argument_list|,
operator|&
name|h_after_show
argument_list|)
expr_stmt|;
name|g_assert_cmpint
argument_list|(
operator|(
name|int
operator|)
name|abs
argument_list|(
name|x_before_hide
operator|-
name|x_after_show
argument_list|)
argument_list|,
operator|<=
argument_list|,
name|GIMP_UI_WINDOW_POSITION_EPSILON
argument_list|)
expr_stmt|;
name|g_assert_cmpint
argument_list|(
operator|(
name|int
operator|)
name|abs
argument_list|(
name|y_before_hide
operator|-
name|y_after_show
argument_list|)
argument_list|,
operator|<=
argument_list|,
name|GIMP_UI_WINDOW_POSITION_EPSILON
argument_list|)
expr_stmt|;
name|g_assert_cmpint
argument_list|(
operator|(
name|int
operator|)
name|abs
argument_list|(
name|w_before_hide
operator|-
name|w_after_show
argument_list|)
argument_list|,
operator|<=
argument_list|,
name|GIMP_UI_WINDOW_POSITION_EPSILON
argument_list|)
expr_stmt|;
name|g_assert_cmpint
argument_list|(
operator|(
name|int
operator|)
name|abs
argument_list|(
name|h_before_hide
operator|-
name|h_after_show
argument_list|)
argument_list|,
operator|<=
argument_list|,
name|GIMP_UI_WINDOW_POSITION_EPSILON
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_ui_switch_to_single_window_mode (GimpTestFixture * fixture,gconstpointer data)
name|gimp_ui_switch_to_single_window_mode
parameter_list|(
name|GimpTestFixture
modifier|*
name|fixture
parameter_list|,
name|gconstpointer
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
comment|/* Switch to single-window mode. We consider this test as passed if    * we don't get any GLib warnings/errors    */
name|gimp_ui_manager_activate_action
argument_list|(
name|gimp_ui_get_ui_manager
argument_list|(
name|gimp
argument_list|)
argument_list|,
literal|"windows"
argument_list|,
literal|"windows-use-single-window-mode"
argument_list|)
expr_stmt|;
name|gimp_test_run_mainloop_until_idle
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_ui_toggle_docks_in_single_window_mode (Gimp * gimp)
name|gimp_ui_toggle_docks_in_single_window_mode
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
name|GIMP_DISPLAY
argument_list|(
name|gimp_get_display_iter
argument_list|(
name|gimp
argument_list|)
operator|->
name|data
argument_list|)
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|gimp_display_get_shell
argument_list|(
name|display
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|toplevel
init|=
name|GTK_WIDGET
argument_list|(
name|gimp_display_shell_get_window
argument_list|(
name|shell
argument_list|)
argument_list|)
decl_stmt|;
name|gint
name|x_temp
init|=
operator|-
literal|1
decl_stmt|;
name|gint
name|y_temp
init|=
operator|-
literal|1
decl_stmt|;
name|gint
name|x_before_hide
init|=
operator|-
literal|1
decl_stmt|;
name|gint
name|y_before_hide
init|=
operator|-
literal|1
decl_stmt|;
name|gint
name|x_after_hide
init|=
operator|-
literal|1
decl_stmt|;
name|gint
name|y_after_hide
init|=
operator|-
literal|1
decl_stmt|;
name|g_assert
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|toplevel
argument_list|)
expr_stmt|;
comment|/* Get toplevel coordinate of image origin */
name|gimp_test_run_mainloop_until_idle
argument_list|()
expr_stmt|;
name|gimp_display_shell_transform_xy
argument_list|(
name|shell
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
operator|&
name|x_temp
argument_list|,
operator|&
name|y_temp
argument_list|,
name|FALSE
comment|/*use_offsets*/
argument_list|)
expr_stmt|;
name|gtk_widget_translate_coordinates
argument_list|(
name|GTK_WIDGET
argument_list|(
name|shell
argument_list|)
argument_list|,
name|toplevel
argument_list|,
name|x_temp
argument_list|,
name|y_temp
argument_list|,
operator|&
name|x_before_hide
argument_list|,
operator|&
name|y_before_hide
argument_list|)
expr_stmt|;
comment|/* Hide all dock windows */
name|gimp_ui_manager_activate_action
argument_list|(
name|gimp_ui_get_ui_manager
argument_list|(
name|gimp
argument_list|)
argument_list|,
literal|"windows"
argument_list|,
literal|"windows-hide-docks"
argument_list|)
expr_stmt|;
name|gimp_test_run_mainloop_until_idle
argument_list|()
expr_stmt|;
comment|/* Get toplevel coordinate of image origin */
name|gimp_test_run_mainloop_until_idle
argument_list|()
expr_stmt|;
name|gimp_display_shell_transform_xy
argument_list|(
name|shell
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
operator|&
name|x_temp
argument_list|,
operator|&
name|y_temp
argument_list|,
name|FALSE
comment|/*use_offsets*/
argument_list|)
expr_stmt|;
name|gtk_widget_translate_coordinates
argument_list|(
name|GTK_WIDGET
argument_list|(
name|shell
argument_list|)
argument_list|,
name|toplevel
argument_list|,
name|x_temp
argument_list|,
name|y_temp
argument_list|,
operator|&
name|x_after_hide
argument_list|,
operator|&
name|y_after_hide
argument_list|)
expr_stmt|;
name|g_assert_cmpint
argument_list|(
operator|(
name|int
operator|)
name|abs
argument_list|(
name|x_after_hide
operator|-
name|x_before_hide
argument_list|)
argument_list|,
operator|<=
argument_list|,
name|GIMP_UI_POSITION_EPSILON
argument_list|)
expr_stmt|;
name|g_assert_cmpint
argument_list|(
operator|(
name|int
operator|)
name|abs
argument_list|(
name|y_after_hide
operator|-
name|y_before_hide
argument_list|)
argument_list|,
operator|<=
argument_list|,
name|GIMP_UI_POSITION_EPSILON
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_ui_hide_docks_in_single_window_mode (GimpTestFixture * fixture,gconstpointer data)
name|gimp_ui_hide_docks_in_single_window_mode
parameter_list|(
name|GimpTestFixture
modifier|*
name|fixture
parameter_list|,
name|gconstpointer
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
name|gimp_ui_toggle_docks_in_single_window_mode
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_ui_show_docks_in_single_window_mode (GimpTestFixture * fixture,gconstpointer data)
name|gimp_ui_show_docks_in_single_window_mode
parameter_list|(
name|GimpTestFixture
modifier|*
name|fixture
parameter_list|,
name|gconstpointer
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
name|gimp_ui_toggle_docks_in_single_window_mode
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_ui_switch_back_to_multi_window_mode (GimpTestFixture * fixture,gconstpointer data)
name|gimp_ui_switch_back_to_multi_window_mode
parameter_list|(
name|GimpTestFixture
modifier|*
name|fixture
parameter_list|,
name|gconstpointer
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
comment|/* Switch back to multi-window mode. We consider this test as passed    * if we don't get any GLib warnings/errors    */
name|gimp_ui_manager_activate_action
argument_list|(
name|gimp_ui_get_ui_manager
argument_list|(
name|gimp
argument_list|)
argument_list|,
literal|"windows"
argument_list|,
literal|"windows-use-single-window-mode"
argument_list|)
expr_stmt|;
name|gimp_test_run_mainloop_until_idle
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GimpUIManager
modifier|*
DECL|function|gimp_ui_get_ui_manager (Gimp * gimp)
name|gimp_ui_get_ui_manager
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
comment|/**  * gimp_ui_synthesize_delete_event:  * @widget:  *  * Synthesize a delete event to @widget.  **/
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_ui_synthesize_delete_event (GtkWidget * widget)
name|gimp_ui_synthesize_delete_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|GdkWindow
modifier|*
name|window
init|=
name|NULL
decl_stmt|;
name|GdkEvent
modifier|*
name|event
init|=
name|NULL
decl_stmt|;
name|window
operator|=
name|gtk_widget_get_window
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|window
argument_list|)
expr_stmt|;
name|event
operator|=
name|gdk_event_new
argument_list|(
name|GDK_DELETE
argument_list|)
expr_stmt|;
name|event
operator|->
name|any
operator|.
name|window
operator|=
name|g_object_ref
argument_list|(
name|window
argument_list|)
expr_stmt|;
name|event
operator|->
name|any
operator|.
name|send_event
operator|=
name|TRUE
expr_stmt|;
name|gtk_main_do_event
argument_list|(
name|event
argument_list|)
expr_stmt|;
name|gdk_event_free
argument_list|(
name|event
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|gimp_ui_find_dock_window (GimpDialogFactory * dialog_factory,GimpUiTestFunc predicate)
name|gimp_ui_find_dock_window
parameter_list|(
name|GimpDialogFactory
modifier|*
name|dialog_factory
parameter_list|,
name|GimpUiTestFunc
name|predicate
parameter_list|)
block|{
name|GList
modifier|*
name|iter
init|=
name|NULL
decl_stmt|;
name|GtkWidget
modifier|*
name|dock_window
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|predicate
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|iter
operator|=
name|gimp_dialog_factory_get_session_infos
argument_list|(
name|dialog_factory
argument_list|)
init|;
name|iter
condition|;
name|iter
operator|=
name|g_list_next
argument_list|(
name|iter
argument_list|)
control|)
block|{
name|GtkWidget
modifier|*
name|widget
init|=
name|gimp_session_info_get_widget
argument_list|(
name|iter
operator|->
name|data
argument_list|)
decl_stmt|;
if|if
condition|(
name|GIMP_IS_DOCK_WINDOW
argument_list|(
name|widget
argument_list|)
operator|&&
name|predicate
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|)
condition|)
block|{
name|dock_window
operator|=
name|widget
expr_stmt|;
break|break;
block|}
block|}
return|return
name|dock_window
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_ui_not_toolbox_window (GObject * object)
name|gimp_ui_not_toolbox_window
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
return|return
operator|!
name|gimp_dock_window_has_toolbox
argument_list|(
name|GIMP_DOCK_WINDOW
argument_list|(
name|object
argument_list|)
argument_list|)
return|;
block|}
end_function

end_unit

