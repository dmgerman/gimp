begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * test-single-window-mode.c  * Copyright (C) 2011 Martin Nordholts<martinn@src.gnome.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
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
file|"libgimpwidgets/gimpwidgets.h"
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
file|"display/gimpdisplayshell-scale.h"
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
file|"widgets/gimpdock.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdockable.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdockbook.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdockcontainer.h"
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
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpchannel.h"
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
file|"core/gimplayer.h"
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
DECL|macro|ADD_TEST (function)
define|#
directive|define
name|ADD_TEST
parameter_list|(
name|function
parameter_list|)
define|\
value|g_test_add ("/gimp-single-window-mode/" #function, \               GimpTestFixture, \               gimp, \               NULL, \               function, \               NULL);
end_define

begin_comment
comment|/* Put this in the code below when you want the test to pause so you  * can do measurements of widgets on the screen for example  */
end_comment

begin_define
DECL|macro|GIMP_PAUSE
define|#
directive|define
name|GIMP_PAUSE
value|(g_usleep (20 * 1000 * 1000))
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2be375bc0108
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

begin_comment
comment|/**  * new_dockable_not_in_new_window:  * @fixture:  * @data:  *  * Test that in single-window mode, new dockables are not put in new  * windows (they should end up in the single image window).  **/
end_comment

begin_function
specifier|static
name|void
DECL|function|new_dockable_not_in_new_window (GimpTestFixture * fixture,gconstpointer data)
name|new_dockable_not_in_new_window
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
name|GimpDialogFactory
modifier|*
name|factory
init|=
name|gimp_dialog_factory_get_singleton
argument_list|()
decl_stmt|;
name|gint
name|dialogs_before
init|=
literal|0
decl_stmt|;
name|gint
name|toplevels_before
init|=
literal|0
decl_stmt|;
name|gint
name|dialogs_after
init|=
literal|0
decl_stmt|;
name|gint
name|toplevels_after
init|=
literal|0
decl_stmt|;
name|GList
modifier|*
name|dialogs
decl_stmt|;
name|GList
modifier|*
name|iter
decl_stmt|;
name|gimp_test_run_mainloop_until_idle
argument_list|()
expr_stmt|;
comment|/* Count dialogs before we create the dockable */
name|dialogs
operator|=
name|gimp_dialog_factory_get_open_dialogs
argument_list|(
name|factory
argument_list|)
expr_stmt|;
name|dialogs_before
operator|=
name|g_list_length
argument_list|(
name|dialogs
argument_list|)
expr_stmt|;
for|for
control|(
name|iter
operator|=
name|dialogs
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
if|if
condition|(
name|gtk_widget_is_toplevel
argument_list|(
name|iter
operator|->
name|data
argument_list|)
condition|)
name|toplevels_before
operator|++
expr_stmt|;
block|}
comment|/* Create a dockable */
name|gimp_ui_manager_activate_action
argument_list|(
name|gimp_test_utils_get_ui_manager
argument_list|(
name|gimp
argument_list|)
argument_list|,
literal|"dialogs"
argument_list|,
literal|"dialogs-undo-history"
argument_list|)
expr_stmt|;
name|gimp_test_run_mainloop_until_idle
argument_list|()
expr_stmt|;
comment|/* Count dialogs after we created the dockable */
name|dialogs
operator|=
name|gimp_dialog_factory_get_open_dialogs
argument_list|(
name|factory
argument_list|)
expr_stmt|;
name|dialogs_after
operator|=
name|g_list_length
argument_list|(
name|dialogs
argument_list|)
expr_stmt|;
for|for
control|(
name|iter
operator|=
name|dialogs
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
if|if
condition|(
name|gtk_widget_is_toplevel
argument_list|(
name|iter
operator|->
name|data
argument_list|)
condition|)
name|toplevels_after
operator|++
expr_stmt|;
block|}
comment|/* We got one more session managed dialog ... */
name|g_assert_cmpint
argument_list|(
name|dialogs_before
operator|+
literal|1
argument_list|,
operator|==
argument_list|,
name|dialogs_after
argument_list|)
expr_stmt|;
comment|/* ... but no new toplevels */
name|g_assert_cmpint
argument_list|(
name|toplevels_before
argument_list|,
operator|==
argument_list|,
name|toplevels_after
argument_list|)
expr_stmt|;
block|}
end_function

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
name|gchar
modifier|*
name|gimprc
decl_stmt|;
name|gimp_test_bail_if_no_display
argument_list|()
expr_stmt|;
name|gtk_test_init
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
comment|/* Launch GIMP in single-window mode */
name|g_setenv
argument_list|(
literal|"GIMP_TESTING_SESSIONRC_NAME"
argument_list|,
literal|"sessionrc-2-8-single-window"
argument_list|,
name|TRUE
comment|/*overwrite*/
argument_list|)
expr_stmt|;
name|gimprc
operator|=
name|g_build_filename
argument_list|(
name|g_getenv
argument_list|(
literal|"GIMP_TESTING_ABS_TOP_SRCDIR"
argument_list|)
argument_list|,
literal|"app/tests/gimpdir/gimprc-single-window"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp
operator|=
name|gimp_init_for_gui_testing_with_rc
argument_list|(
name|TRUE
comment|/*show_gui*/
argument_list|,
name|gimprc
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|gimprc
argument_list|)
expr_stmt|;
name|gimp_test_run_mainloop_until_idle
argument_list|()
expr_stmt|;
name|ADD_TEST
argument_list|(
name|new_dockable_not_in_new_window
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

end_unit

