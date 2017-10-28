begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 2011 Martin Nordholts  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"dialogs/dialogs-types.h"
end_include

begin_include
include|#
directive|include
file|"tests.h"
end_include

begin_include
include|#
directive|include
file|"gimp-test-session-utils.h"
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
value|g_test_add_func ("/gimp-session-2-8-compatibility-single-window/" #function, \                    function);
end_define

begin_define
DECL|macro|SKIP_TEST (function)
define|#
directive|define
name|SKIP_TEST
parameter_list|(
name|function
parameter_list|)
define|\
value|g_test_add_func ("/gimp-session-2-8-compatibility-single-window/subprocess/" #function, \                    function);
end_define

begin_comment
comment|/**  * Tests that a multi-window sessionrc in GIMP 2.8 format is loaded  * and written (thus also interpreted) like we expect.  **/
end_comment

begin_function
specifier|static
name|void
DECL|function|read_and_write_session_files (void)
name|read_and_write_session_files
parameter_list|(
name|void
parameter_list|)
block|{
name|gimp_test_session_load_and_write_session_files
argument_list|(
literal|"sessionrc-2-8-single-window"
argument_list|,
literal|"dockrc-2-8"
argument_list|,
literal|"sessionrc-expected-single-window"
argument_list|,
literal|"dockrc-expected"
argument_list|,
name|TRUE
comment|/*single_window_mode*/
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
ifdef|#
directive|ifdef
name|HAVE_XVFB_RUN
name|ADD_TEST
argument_list|(
name|read_and_write_session_files
argument_list|)
expr_stmt|;
else|#
directive|else
name|SKIP_TEST
argument_list|(
name|read_and_write_session_files
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* Don't bother freeing stuff, the process is short-lived */
ifdef|#
directive|ifdef
name|HAVE_XVFB_RUN
return|return
name|g_test_run
argument_list|()
return|;
else|#
directive|else
return|return
name|GIMP_EXIT_TEST_SKIPPED
return|;
endif|#
directive|endif
block|}
end_function

end_unit

