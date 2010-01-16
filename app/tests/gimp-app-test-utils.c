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

begin_comment
comment|/**  * gimp_test_utils_set_gimp2_directory:  * @subdir:  *  * Sets GIMP2_DIRECTORY to the source dir ./app/tests/@subdir. Make  * sure to run it before using any of the GIMP functions.  **/
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
name|gchar
modifier|*
name|gimpdir
init|=
name|NULL
decl_stmt|;
comment|/* GIMP_TESTING_ABS_TOP_SRCDIR is set by the automake test runner,    * see Makefile.am    */
name|gimpdir
operator|=
name|g_build_filename
argument_list|(
name|g_getenv
argument_list|(
literal|"GIMP_TESTING_ABS_TOP_SRCDIR"
argument_list|)
argument_list|,
literal|"app/tests"
argument_list|,
name|subdir
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_setenv
argument_list|(
literal|"GIMP2_DIRECTORY"
argument_list|,
name|gimpdir
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|gimpdir
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
name|gchar
modifier|*
name|menus_dir
init|=
name|NULL
decl_stmt|;
name|menus_dir
operator|=
name|gimp_test_utils_get_source_subdir
argument_list|(
literal|"menus"
argument_list|)
expr_stmt|;
name|g_setenv
argument_list|(
literal|"GIMP_TESTING_MENUS_DIR"
argument_list|,
name|menus_dir
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|menus_dir
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_test_utils_get_source_subdir:  * @subdir:  *  * Returns: The source directory $top_srcdir/@subdir.  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_test_utils_get_source_subdir (const gchar * subdir)
name|gimp_test_utils_get_source_subdir
parameter_list|(
specifier|const
name|gchar
modifier|*
name|subdir
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|abs_top_srcdir
init|=
name|g_getenv
argument_list|(
literal|"GIMP_TESTING_ABS_TOP_SRCDIR"
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|abs_top_srcdir
condition|)
name|g_printerr
argument_list|(
literal|"The env var GIMP_TESTING_ABS_TOP_SRCDIR is not set, you are probably\n"
literal|"running in a debugger. Set it manually to e.g. ~/source/gimp"
argument_list|)
expr_stmt|;
comment|/* GIMP_TESTING_ABS_TOP_SRCDIR is set by the automake test runner,    * see Makefile.am    */
return|return
name|g_build_filename
argument_list|(
name|g_getenv
argument_list|(
literal|"GIMP_TESTING_ABS_TOP_SRCDIR"
argument_list|)
argument_list|,
name|subdir
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

end_unit

