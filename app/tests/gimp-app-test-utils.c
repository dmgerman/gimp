begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 2009 Martin Nordholts<martinn@src.gnome.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|"gimp-app-test-utils.h"
end_include

begin_function
specifier|static
name|void
DECL|function|gimp_test_utils_set_env_to_subdir (const gchar * root_env_var,const gchar * subdir,const gchar * target_env_var)
name|gimp_test_utils_set_env_to_subdir
parameter_list|(
specifier|const
name|gchar
modifier|*
name|root_env_var
parameter_list|,
specifier|const
name|gchar
modifier|*
name|subdir
parameter_list|,
specifier|const
name|gchar
modifier|*
name|target_env_var
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|root_dir
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|target_dir
init|=
name|NULL
decl_stmt|;
comment|/* Get root dir */
name|root_dir
operator|=
name|g_getenv
argument_list|(
name|root_env_var
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|root_dir
condition|)
name|g_printerr
argument_list|(
literal|"The env var %s is not set, you are probably running\n"
literal|"in a debugger. Set it manually, e.g.:\n"
literal|"set env %s=%s/source/gimp\n"
argument_list|,
name|root_env_var
argument_list|,
name|root_env_var
argument_list|,
name|g_get_home_dir
argument_list|()
argument_list|)
expr_stmt|;
comment|/* Construct path and setup target env var */
name|target_dir
operator|=
name|g_build_filename
argument_list|(
name|root_dir
argument_list|,
name|subdir
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_setenv
argument_list|(
name|target_env_var
argument_list|,
name|target_dir
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|target_dir
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_test_utils_set_gimp2_directory:  * @subdir: Subdir, may be %NULL  *  * Sets GIMP2_DIRECTORY to the source dir ./app/tests/@subdir. Make  * sure to run it before using any of the GIMP functions.  **/
end_comment

begin_function
name|void
DECL|function|gimp_test_utils_set_gimp2_directory (const gchar * subdir)
name|gimp_test_utils_set_gimp2_directory
parameter_list|(
specifier|const
name|gchar
modifier|*
name|subdir
parameter_list|)
block|{
comment|/* GIMP_TESTING_ABS_TOP_SRCDIR is set by the automake test runner,    * see Makefile.am    */
name|gimp_test_utils_set_env_to_subdir
argument_list|(
literal|"GIMP_TESTING_ABS_TOP_SRCDIR"
comment|/*root_env_var*/
argument_list|,
name|subdir
argument_list|,
literal|"GIMP2_DIRECTORY"
comment|/*target_env_var*/
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_test_utils_setup_menus_dir:  *  * Sets GIMP_TESTING_MENUS_DIR to "$top_srcdir/menus".  **/
end_comment

begin_function
name|void
DECL|function|gimp_test_utils_setup_menus_dir (void)
name|gimp_test_utils_setup_menus_dir
parameter_list|(
name|void
parameter_list|)
block|{
comment|/* GIMP_TESTING_ABS_TOP_SRCDIR is set by the automake test runner,    * see Makefile.am    */
name|gimp_test_utils_set_env_to_subdir
argument_list|(
literal|"GIMP_TESTING_ABS_TOP_SRCDIR"
comment|/*root_env_var*/
argument_list|,
literal|"menus"
comment|/*subdir*/
argument_list|,
literal|"GIMP_TESTING_MENUS_DIR"
comment|/*target_env_var*/
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

