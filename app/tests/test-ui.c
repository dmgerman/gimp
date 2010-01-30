begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 2009 Martin Nordholts<martinn@src.gnome.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

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
file|"dialogs/dialogs-types.h"
end_include

begin_include
include|#
directive|include
file|"dialogs/dialogs.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
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

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2b9593cb0108
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
name|GimpDialogFactory
modifier|*
name|dock_factory
init|=
name|gimp_dialog_factory_from_name
argument_list|(
literal|"dock"
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|dockable
init|=
name|gimp_dialog_factory_dialog_new
argument_list|(
name|dock_factory
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
name|GimpDialogFactory
modifier|*
name|dialog_factory
init|=
name|gimp_dialog_factory_from_name
argument_list|(
literal|"toplevel"
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
name|dialog_factory
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
return|return
name|ui_manager
return|;
block|}
end_function

end_unit

