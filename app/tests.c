begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 2009 Martin Nordholts  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"gui/gui-types.h"
end_include

begin_include
include|#
directive|include
file|"gui/gui.h"
end_include

begin_include
include|#
directive|include
file|"actions/actions.h"
end_include

begin_include
include|#
directive|include
file|"menus/menus.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpsessioninfo.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpgeglconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp-contexts.h"
end_include

begin_include
include|#
directive|include
file|"gegl/gimp-gegl.h"
end_include

begin_include
include|#
directive|include
file|"gimp-log.h"
end_include

begin_include
include|#
directive|include
file|"tests.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|GDK_WINDOWING_QUARTZ
end_ifdef

begin_include
include|#
directive|include
file|<Cocoa/Cocoa.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_function
specifier|static
name|void
DECL|function|gimp_status_func_dummy (const gchar * text1,const gchar * text2,gdouble percentage)
name|gimp_status_func_dummy
parameter_list|(
specifier|const
name|gchar
modifier|*
name|text1
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text2
parameter_list|,
name|gdouble
name|percentage
parameter_list|)
block|{ }
end_function

begin_comment
comment|/**  * gimp_init_for_testing:  *  * Initialize the GIMP object system for unit testing. This is a  * selected subset of the initialization happening in app_run().  **/
end_comment

begin_function
name|Gimp
modifier|*
DECL|function|gimp_init_for_testing (void)
name|gimp_init_for_testing
parameter_list|(
name|void
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|gimp_log_init
argument_list|()
expr_stmt|;
name|gegl_init
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp
operator|=
name|gimp_new
argument_list|(
literal|"Unit Tested GIMP"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|GIMP_STACK_TRACE_QUERY
argument_list|,
name|GIMP_PDB_COMPAT_OFF
argument_list|)
expr_stmt|;
name|gimp_load_config
argument_list|(
name|gimp
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_gegl_init
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|gimp_initialize
argument_list|(
name|gimp
argument_list|,
name|gimp_status_func_dummy
argument_list|)
expr_stmt|;
name|gimp_restore
argument_list|(
name|gimp
argument_list|,
name|gimp_status_func_dummy
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|gimp
return|;
block|}
end_function

begin_ifndef
ifndef|#
directive|ifndef
name|GIMP_CONSOLE_COMPILATION
end_ifndef

begin_function
specifier|static
name|void
DECL|function|gimp_init_icon_theme_for_testing (void)
name|gimp_init_icon_theme_for_testing
parameter_list|(
name|void
parameter_list|)
block|{
name|gchar
modifier|*
name|icon_root
decl_stmt|;
name|icon_root
operator|=
name|g_test_build_filename
argument_list|(
name|G_TEST_BUILT
argument_list|,
literal|"gimp-test-icon-theme"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_icon_theme_prepend_search_path
argument_list|(
name|gtk_icon_theme_get_default
argument_list|()
argument_list|,
name|icon_root
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|icon_root
argument_list|)
expr_stmt|;
return|return;
block|}
end_function

begin_ifdef
ifdef|#
directive|ifdef
name|GDK_WINDOWING_QUARTZ
end_ifdef

begin_function
specifier|static
name|void
DECL|function|gimp_osx_focus_window (void)
name|gimp_osx_focus_window
parameter_list|(
name|void
parameter_list|)
block|{
index|[
name|NSApp
name|activateIgnoringOtherApps
operator|:
name|YES
index|]
expr_stmt|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_function
specifier|static
name|Gimp
modifier|*
DECL|function|gimp_init_for_gui_testing_internal (gboolean show_gui,GFile * gimprc)
name|gimp_init_for_gui_testing_internal
parameter_list|(
name|gboolean
name|show_gui
parameter_list|,
name|GFile
modifier|*
name|gimprc
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
decl_stmt|;
if|#
directive|if
name|defined
argument_list|(
name|G_OS_WIN32
argument_list|)
comment|/* g_test_init() sets warnings always fatal, which is a usually a good      testing default. Nevertheless the Windows platform may have a few      quirks generating warnings, yet we want to finish tests. So we      allow some relaxed rules on this platform. */
name|GLogLevelFlags
name|fatal_mask
decl_stmt|;
name|fatal_mask
operator|=
call|(
name|GLogLevelFlags
call|)
argument_list|(
name|G_LOG_FATAL_MASK
operator||
name|G_LOG_LEVEL_CRITICAL
argument_list|)
expr_stmt|;
name|g_log_set_always_fatal
argument_list|(
name|fatal_mask
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* from main() */
name|gimp_log_init
argument_list|()
expr_stmt|;
name|gegl_init
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* Introduce an error margin for positions written to sessionrc */
name|gimp_session_info_set_position_accuracy
argument_list|(
literal|5
argument_list|)
expr_stmt|;
comment|/* from app_run() */
name|gimp
operator|=
name|gimp_new
argument_list|(
literal|"Unit Tested GIMP"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
operator|!
name|show_gui
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|GIMP_STACK_TRACE_QUERY
argument_list|,
name|GIMP_PDB_COMPAT_OFF
argument_list|)
expr_stmt|;
name|gimp_set_show_gui
argument_list|(
name|gimp
argument_list|,
name|show_gui
argument_list|)
expr_stmt|;
name|gimp_load_config
argument_list|(
name|gimp
argument_list|,
name|gimprc
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_gegl_init
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|gui_init
argument_list|(
name|gimp
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_init_icon_theme_for_testing
argument_list|()
expr_stmt|;
name|gimp_initialize
argument_list|(
name|gimp
argument_list|,
name|gimp_status_func_dummy
argument_list|)
expr_stmt|;
name|gimp_restore
argument_list|(
name|gimp
argument_list|,
name|gimp_status_func_dummy
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|GDK_WINDOWING_QUARTZ
name|g_idle_add
argument_list|(
operator|(
name|GSourceFunc
operator|)
name|gimp_osx_focus_window
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
endif|#
directive|endif
return|return
name|gimp
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_init_for_gui_testing:  * @show_gui:  *  * Initializes a #Gimp instance for use in test cases that rely on GUI  * code to be initialized.  *  * Returns: The #Gimp instance.  **/
end_comment

begin_function
name|Gimp
modifier|*
DECL|function|gimp_init_for_gui_testing (gboolean show_gui)
name|gimp_init_for_gui_testing
parameter_list|(
name|gboolean
name|show_gui
parameter_list|)
block|{
return|return
name|gimp_init_for_gui_testing_internal
argument_list|(
name|show_gui
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_init_for_gui_testing:  * @show_gui:  * @gimprc:  *  * Like gimp_init_for_gui_testing(), but also allows a custom gimprc  * filename to be specified.  *  * Returns: The #Gimp instance.  **/
end_comment

begin_function
name|Gimp
modifier|*
DECL|function|gimp_init_for_gui_testing_with_rc (gboolean show_gui,GFile * gimprc)
name|gimp_init_for_gui_testing_with_rc
parameter_list|(
name|gboolean
name|show_gui
parameter_list|,
name|GFile
modifier|*
name|gimprc
parameter_list|)
block|{
return|return
name|gimp_init_for_gui_testing_internal
argument_list|(
name|show_gui
argument_list|,
name|gimprc
argument_list|)
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* GIMP_CONSOLE_COMPILATION */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|gimp_tests_quit_mainloop (GMainLoop * loop)
name|gimp_tests_quit_mainloop
parameter_list|(
name|GMainLoop
modifier|*
name|loop
parameter_list|)
block|{
name|g_main_loop_quit
argument_list|(
name|loop
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_test_run_temp_mainloop:  * @running_time: The time to run the main loop.  *  * Helper function for tests that wants to run a main loop for a  * while. Useful when you want GIMP's state to settle before doing  * tests.  **/
end_comment

begin_function
name|void
DECL|function|gimp_test_run_temp_mainloop (guint32 running_time)
name|gimp_test_run_temp_mainloop
parameter_list|(
name|guint32
name|running_time
parameter_list|)
block|{
name|GMainLoop
modifier|*
name|loop
decl_stmt|;
name|loop
operator|=
name|g_main_loop_new
argument_list|(
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_timeout_add
argument_list|(
name|running_time
argument_list|,
operator|(
name|GSourceFunc
operator|)
name|gimp_tests_quit_mainloop
argument_list|,
name|loop
argument_list|)
expr_stmt|;
name|g_main_loop_run
argument_list|(
name|loop
argument_list|)
expr_stmt|;
name|g_main_loop_unref
argument_list|(
name|loop
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_test_run_mainloop_until_idle:  *  * Creates and runs a main loop until it is idle, i.e. has no more  * work to do.  **/
end_comment

begin_function
name|void
DECL|function|gimp_test_run_mainloop_until_idle (void)
name|gimp_test_run_mainloop_until_idle
parameter_list|(
name|void
parameter_list|)
block|{
name|GMainLoop
modifier|*
name|loop
init|=
name|g_main_loop_new
argument_list|(
name|NULL
argument_list|,
name|FALSE
argument_list|)
decl_stmt|;
name|g_idle_add
argument_list|(
operator|(
name|GSourceFunc
operator|)
name|gimp_tests_quit_mainloop
argument_list|,
name|loop
argument_list|)
expr_stmt|;
name|g_main_loop_run
argument_list|(
name|loop
argument_list|)
expr_stmt|;
name|g_main_loop_unref
argument_list|(
name|loop
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_test_bail_if_no_display:  * @void:  *  * If no DISPLAY is set, call exit(EXIT_SUCCESS). There is no use in  * having UI tests failing in DISPLAY-less environments.  **/
end_comment

begin_function
name|void
DECL|function|gimp_test_bail_if_no_display (void)
name|gimp_test_bail_if_no_display
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
operator|!
name|g_getenv
argument_list|(
literal|"DISPLAY"
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
literal|"No DISPLAY set, not running UI tests\n"
argument_list|)
expr_stmt|;
name|exit
argument_list|(
name|EXIT_SUCCESS
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

