begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 2011 Martin Nordholts<martinn@src.gnome.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|<glib/gstdio.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

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
file|<utime.h>
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
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpsessioninfo.h"
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
file|"tests.h"
end_include

begin_include
include|#
directive|include
file|"gimp-app-test-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimp-test-session-utils.h"
end_include

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon28e7c4b90108
block|{
DECL|member|file
name|GFile
modifier|*
name|file
decl_stmt|;
DECL|member|md5
name|gchar
modifier|*
name|md5
decl_stmt|;
DECL|member|modtime
name|guint64
name|modtime
decl_stmt|;
DECL|typedef|GimpTestFileState
block|}
name|GimpTestFileState
typedef|;
end_typedef

begin_function
specifier|static
name|gboolean
DECL|function|gimp_test_get_file_state_verbose (GFile * file,GimpTestFileState * filestate)
name|gimp_test_get_file_state_verbose
parameter_list|(
name|GFile
modifier|*
name|file
parameter_list|,
name|GimpTestFileState
modifier|*
name|filestate
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|filestate
operator|->
name|file
operator|=
name|g_object_ref
argument_list|(
name|file
argument_list|)
expr_stmt|;
comment|/* Get checksum */
if|if
condition|(
name|success
condition|)
block|{
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gchar
modifier|*
name|contents
init|=
name|NULL
decl_stmt|;
name|gsize
name|length
init|=
literal|0
decl_stmt|;
name|filename
operator|=
name|g_file_get_path
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|success
operator|=
name|g_file_get_contents
argument_list|(
name|filename
argument_list|,
operator|&
name|contents
argument_list|,
operator|&
name|length
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|filestate
operator|->
name|md5
operator|=
name|g_compute_checksum_for_string
argument_list|(
name|G_CHECKSUM_MD5
argument_list|,
name|contents
argument_list|,
name|length
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|contents
argument_list|)
expr_stmt|;
block|}
comment|/* Get modification time */
if|if
condition|(
name|success
condition|)
block|{
name|GFileInfo
modifier|*
name|info
init|=
name|g_file_query_info
argument_list|(
name|file
argument_list|,
name|G_FILE_ATTRIBUTE_TIME_MODIFIED
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
if|if
condition|(
name|info
condition|)
block|{
name|filestate
operator|->
name|modtime
operator|=
name|g_file_info_get_attribute_uint64
argument_list|(
name|info
argument_list|,
name|G_FILE_ATTRIBUTE_TIME_MODIFIED
argument_list|)
expr_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
name|g_object_unref
argument_list|(
name|info
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
if|if
condition|(
operator|!
name|success
condition|)
name|g_printerr
argument_list|(
literal|"Failed to get initial file info for '%s'\n"
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|file
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_test_file_state_changes (GFile * file,GimpTestFileState * state1,GimpTestFileState * state2)
name|gimp_test_file_state_changes
parameter_list|(
name|GFile
modifier|*
name|file
parameter_list|,
name|GimpTestFileState
modifier|*
name|state1
parameter_list|,
name|GimpTestFileState
modifier|*
name|state2
parameter_list|)
block|{
if|if
condition|(
name|state1
operator|->
name|modtime
operator|==
name|state2
operator|->
name|modtime
condition|)
block|{
name|g_printerr
argument_list|(
literal|"A new '%s' was not created\n"
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|file
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
if|if
condition|(
name|strcmp
argument_list|(
name|state1
operator|->
name|md5
argument_list|,
name|state2
operator|->
name|md5
argument_list|)
operator|!=
literal|0
condition|)
block|{
name|char
modifier|*
name|diff_argv
index|[
literal|5
index|]
init|=
block|{
literal|"diff"
block|,
literal|"-u"
block|,
name|g_file_get_path
argument_list|(
name|state1
operator|->
name|file
argument_list|)
block|,
name|g_file_get_path
argument_list|(
name|state2
operator|->
name|file
argument_list|)
block|,
name|NULL
block|}
decl_stmt|;
name|g_printerr
argument_list|(
literal|"'%s' was changed but should not have been. Reason, using "
literal|"`diff -u $expected $actual`\n"
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|file
argument_list|)
argument_list|)
expr_stmt|;
name|g_spawn_sync
argument_list|(
name|NULL
comment|/*working_directory*/
argument_list|,
name|diff_argv
argument_list|,
name|NULL
comment|/*envp*/
argument_list|,
name|G_SPAWN_SEARCH_PATH
argument_list|,
name|NULL
comment|/*child_setup*/
argument_list|,
name|NULL
comment|/*user_data*/
argument_list|,
name|NULL
comment|/*standard_output*/
argument_list|,
name|NULL
comment|/*standard_error*/
argument_list|,
name|NULL
comment|/*exist_status*/
argument_list|,
name|NULL
comment|/*error*/
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|diff_argv
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|diff_argv
index|[
literal|3
index|]
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_test_session_load_and_write_session_files:  * @loaded_sessionrc:   The name of the file of the sessionrc file to  *                      load  * @loaded_dockrc:      The name of the file of the dockrc file to load  * @expected_sessionrc: The name of the file with the expected  *                      sessionrc file content  * @expected_dockrc:    The name of the file with the expected dockrc  *                      file content  *  * Utility function for the various session management tests. We can't  * easily have all those tests in a single program several Gimp  * instance can't easily be initialized in the same process.  **/
end_comment

begin_function
name|void
DECL|function|gimp_test_session_load_and_write_session_files (const gchar * loaded_sessionrc,const gchar * loaded_dockrc,const gchar * expected_sessionrc,const gchar * expected_dockrc,gboolean single_window_mode)
name|gimp_test_session_load_and_write_session_files
parameter_list|(
specifier|const
name|gchar
modifier|*
name|loaded_sessionrc
parameter_list|,
specifier|const
name|gchar
modifier|*
name|loaded_dockrc
parameter_list|,
specifier|const
name|gchar
modifier|*
name|expected_sessionrc
parameter_list|,
specifier|const
name|gchar
modifier|*
name|expected_dockrc
parameter_list|,
name|gboolean
name|single_window_mode
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|GimpTestFileState
name|initial_sessionrc_state
init|=
block|{
name|NULL
block|,
name|NULL
block|,
literal|0
block|}
decl_stmt|;
name|GimpTestFileState
name|initial_dockrc_state
init|=
block|{
name|NULL
block|,
name|NULL
block|,
literal|0
block|}
decl_stmt|;
name|GimpTestFileState
name|final_sessionrc_state
init|=
block|{
name|NULL
block|,
name|NULL
block|,
literal|0
block|}
decl_stmt|;
name|GimpTestFileState
name|final_dockrc_state
init|=
block|{
name|NULL
block|,
name|NULL
block|,
literal|0
block|}
decl_stmt|;
name|GFile
modifier|*
name|sessionrc_file
init|=
name|NULL
decl_stmt|;
name|GFile
modifier|*
name|dockrc_file
init|=
name|NULL
decl_stmt|;
comment|/* Make sure to run this before we use any GIMP functions */
name|gimp_test_utils_set_gimp3_directory
argument_list|(
literal|"GIMP_TESTING_ABS_TOP_SRCDIR"
argument_list|,
literal|"app/tests/gimpdir"
argument_list|)
expr_stmt|;
name|gimp_test_utils_setup_menus_path
argument_list|()
expr_stmt|;
comment|/* Note that we expect the resulting sessionrc to be different from    * the read file, which is why we check the MD5 of the -expected    * variant    */
name|sessionrc_file
operator|=
name|gimp_directory_file
argument_list|(
name|expected_sessionrc
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dockrc_file
operator|=
name|gimp_directory_file
argument_list|(
name|expected_dockrc
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* Remember the modtimes and MD5s */
name|g_assert
argument_list|(
name|gimp_test_get_file_state_verbose
argument_list|(
name|sessionrc_file
argument_list|,
operator|&
name|initial_sessionrc_state
argument_list|)
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|gimp_test_get_file_state_verbose
argument_list|(
name|dockrc_file
argument_list|,
operator|&
name|initial_dockrc_state
argument_list|)
argument_list|)
expr_stmt|;
comment|/* Use specific input files when restoring the session */
name|g_setenv
argument_list|(
literal|"GIMP_TESTING_SESSIONRC_NAME"
argument_list|,
name|loaded_sessionrc
argument_list|,
name|TRUE
comment|/*overwrite*/
argument_list|)
expr_stmt|;
name|g_setenv
argument_list|(
literal|"GIMP_TESTING_DOCKRC_NAME"
argument_list|,
name|loaded_dockrc
argument_list|,
name|TRUE
comment|/*overwrite*/
argument_list|)
expr_stmt|;
comment|/* Start up GIMP */
name|gimp
operator|=
name|gimp_init_for_gui_testing
argument_list|(
name|TRUE
comment|/*show_gui*/
argument_list|)
expr_stmt|;
comment|/* Let the main loop run until idle to let things stabilize. This    * includes parsing sessionrc and dockrc    */
name|gimp_test_run_mainloop_until_idle
argument_list|()
expr_stmt|;
comment|/* Change the gimp dir to the output dir so files are written there,    * we don't want to (can't always) write to files in the source    * dir. There is a hook in Makefile.am that makes sure the output    * dir exists    */
name|gimp_test_utils_set_gimp3_directory
argument_list|(
literal|"GIMP_TESTING_ABS_TOP_BUILDDIR"
argument_list|,
literal|"app/tests/gimpdir-output"
argument_list|)
expr_stmt|;
comment|/* Use normal output names */
name|g_unsetenv
argument_list|(
literal|"GIMP_TESTING_SESSIONRC_NAME"
argument_list|)
expr_stmt|;
name|g_unsetenv
argument_list|(
literal|"GIMP_TESTING_DOCKRC_NAME"
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|sessionrc_file
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|dockrc_file
argument_list|)
expr_stmt|;
name|sessionrc_file
operator|=
name|gimp_directory_file
argument_list|(
literal|"sessionrc"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dockrc_file
operator|=
name|gimp_directory_file
argument_list|(
literal|"dockrc"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* Exit. This includes writing sessionrc and dockrc*/
name|gimp_exit
argument_list|(
name|gimp
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/* Now get the new modtimes and MD5s */
name|g_assert
argument_list|(
name|gimp_test_get_file_state_verbose
argument_list|(
name|sessionrc_file
argument_list|,
operator|&
name|final_sessionrc_state
argument_list|)
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|gimp_test_get_file_state_verbose
argument_list|(
name|dockrc_file
argument_list|,
operator|&
name|final_dockrc_state
argument_list|)
argument_list|)
expr_stmt|;
comment|/* If things have gone our way, GIMP will have deserialized    * sessionrc and dockrc, shown the GUI, and then serialized the new    * files. To make sure we have new files we check the modtime, and    * to make sure that their content remains the same we compare their    * MD5    */
name|g_assert
argument_list|(
name|gimp_test_file_state_changes
argument_list|(
name|g_file_new_for_path
argument_list|(
literal|"sessionrc"
argument_list|)
argument_list|,
operator|&
name|initial_sessionrc_state
argument_list|,
operator|&
name|final_sessionrc_state
argument_list|)
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|gimp_test_file_state_changes
argument_list|(
name|g_file_new_for_path
argument_list|(
literal|"dockrc"
argument_list|)
argument_list|,
operator|&
name|initial_dockrc_state
argument_list|,
operator|&
name|final_dockrc_state
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

