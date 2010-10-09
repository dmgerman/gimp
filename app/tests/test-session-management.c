begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 2009 Martin Nordholts  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

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

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon28f76d860108
block|{
DECL|member|dummy
name|int
name|dummy
decl_stmt|;
DECL|typedef|GimpTestFixture
block|}
name|GimpTestFixture
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon28f76d860208
block|{
DECL|member|filename
name|gchar
modifier|*
name|filename
decl_stmt|;
DECL|member|md5
name|gchar
modifier|*
name|md5
decl_stmt|;
DECL|member|modtime
name|GTimeVal
name|modtime
decl_stmt|;
DECL|typedef|GimpTestFileState
block|}
name|GimpTestFileState
typedef|;
end_typedef

begin_function_decl
specifier|static
name|gboolean
name|gimp_test_get_file_state_verbose
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|GimpTestFileState
modifier|*
name|filestate
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_test_file_state_changes
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|GimpTestFileState
modifier|*
name|state1
parameter_list|,
name|GimpTestFileState
modifier|*
name|state2
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|gimp
specifier|static
name|Gimp
modifier|*
name|gimp
init|=
name|NULL
decl_stmt|;
end_decl_stmt

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
name|GimpTestFileState
name|initial_sessionrc_state
init|=
block|{
name|NULL
block|,
name|NULL
block|,
block|{
literal|0
block|,
literal|0
block|}
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
block|{
literal|0
block|,
literal|0
block|}
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
block|{
literal|0
block|,
literal|0
block|}
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
block|{
literal|0
block|,
literal|0
block|}
block|}
decl_stmt|;
name|gchar
modifier|*
name|sessionrc_filename
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|dockrc_filename
init|=
name|NULL
decl_stmt|;
name|gint
name|result
init|=
literal|0
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
comment|/* Make sure to run this before we use any GIMP functions */
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
comment|/* Note that we expect the resulting sessionrc to be different from    * the read file, which is why we check the MD5 of the -expected    * variant    */
name|sessionrc_filename
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"sessionrc-expected"
argument_list|)
expr_stmt|;
name|dockrc_filename
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"dockrc-expected"
argument_list|)
expr_stmt|;
comment|/* Remeber the modtimes and MD5s */
if|if
condition|(
operator|!
name|gimp_test_get_file_state_verbose
argument_list|(
name|sessionrc_filename
argument_list|,
operator|&
name|initial_sessionrc_state
argument_list|)
condition|)
name|result
operator|=
operator|-
literal|1
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_test_get_file_state_verbose
argument_list|(
name|dockrc_filename
argument_list|,
operator|&
name|initial_dockrc_state
argument_list|)
condition|)
name|result
operator|=
operator|-
literal|1
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
name|gimp_test_utils_set_gimp2_directory
argument_list|(
literal|"GIMP_TESTING_ABS_TOP_BUILDDIR"
argument_list|,
literal|"app/tests/gimpdir-output"
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|sessionrc_filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|dockrc_filename
argument_list|)
expr_stmt|;
name|sessionrc_filename
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"sessionrc"
argument_list|)
expr_stmt|;
name|dockrc_filename
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"dockrc"
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
if|if
condition|(
operator|!
name|gimp_test_get_file_state_verbose
argument_list|(
name|sessionrc_filename
argument_list|,
operator|&
name|final_sessionrc_state
argument_list|)
condition|)
name|result
operator|=
operator|-
literal|1
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_test_get_file_state_verbose
argument_list|(
name|dockrc_filename
argument_list|,
operator|&
name|final_dockrc_state
argument_list|)
condition|)
name|result
operator|=
operator|-
literal|1
expr_stmt|;
comment|/* If things have gone our way, GIMP will have deserialized    * sessionrc and dockrc, shown the GUI, and then serialized the new    * files. To make sure we have new files we check the modtime, and    * to make sure that their content remains the same we compare their    * MD5    */
if|if
condition|(
operator|!
name|gimp_test_file_state_changes
argument_list|(
literal|"sessionrc"
argument_list|,
operator|&
name|initial_sessionrc_state
argument_list|,
operator|&
name|final_sessionrc_state
argument_list|)
condition|)
name|result
operator|=
operator|-
literal|1
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_test_file_state_changes
argument_list|(
literal|"dockrc"
argument_list|,
operator|&
name|initial_dockrc_state
argument_list|,
operator|&
name|final_dockrc_state
argument_list|)
condition|)
name|result
operator|=
operator|-
literal|1
expr_stmt|;
if|if
condition|(
name|result
operator|==
literal|0
condition|)
name|g_print
argument_list|(
literal|"/gimp-session-management/sessionrc_compatibility: OK\n"
argument_list|)
expr_stmt|;
comment|/* Don't bother freeing stuff, the process is short-lived */
return|return
name|result
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_test_get_file_state_verbose (const gchar * filename,GimpTestFileState * filestate)
name|gimp_test_get_file_state_verbose
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
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
name|filename
operator|=
name|g_strdup
argument_list|(
name|filename
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
name|contents
init|=
name|NULL
decl_stmt|;
name|gsize
name|length
init|=
literal|0
decl_stmt|;
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
name|GFile
modifier|*
name|file
init|=
name|g_file_new_for_path
argument_list|(
name|filename
argument_list|)
decl_stmt|;
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
name|g_file_info_get_modification_time
argument_list|(
name|info
argument_list|,
operator|&
name|filestate
operator|->
name|modtime
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
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
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
name|filename
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
DECL|function|gimp_test_file_state_changes (const gchar * filename,GimpTestFileState * state1,GimpTestFileState * state2)
name|gimp_test_file_state_changes
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
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
operator|.
name|tv_sec
operator|==
name|state2
operator|->
name|modtime
operator|.
name|tv_sec
operator|&&
name|state1
operator|->
name|modtime
operator|.
name|tv_usec
operator|==
name|state2
operator|->
name|modtime
operator|.
name|tv_usec
condition|)
block|{
name|g_printerr
argument_list|(
literal|"A new '%s' was not created\n"
argument_list|,
name|filename
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
name|state1
operator|->
name|filename
block|,
name|state2
operator|->
name|filename
block|,
name|NULL
block|}
decl_stmt|;
name|g_printerr
argument_list|(
literal|"'%s' was changed but should not have been. Reason, using "
literal|"`diff -u $expected $actual`\n"
argument_list|,
name|filename
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
return|return
name|FALSE
return|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

end_unit

