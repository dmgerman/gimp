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

end_unit

