begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 2009 Martin Nordholts  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__TESTS_H__
end_ifndef

begin_define
DECL|macro|__TESTS_H__
define|#
directive|define
name|__TESTS_H__
end_define

begin_comment
comment|/* Automake doc says:    "When no test protocol is in use, an exit status of 0 from a test    script will denote a success, an exit status of 77 a skipped test,    an exit status of 99 an hard error, and any other exit status will    denote a failure."     Unfortunately glib returns a SUCCESS when you skip tests, which is    not a reliable test feedback. So we hard-code the SKIPPED return    value. */
end_comment

begin_define
DECL|macro|GIMP_EXIT_TEST_SKIPPED
define|#
directive|define
name|GIMP_EXIT_TEST_SKIPPED
value|77
end_define

begin_function_decl
name|Gimp
modifier|*
name|gimp_init_for_testing
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Gimp
modifier|*
name|gimp_init_for_gui_testing
parameter_list|(
name|gboolean
name|show_gui
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Gimp
modifier|*
name|gimp_init_for_gui_testing_with_rc
parameter_list|(
name|gboolean
name|show_gui
parameter_list|,
name|GFile
modifier|*
name|gimprc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_test_run_temp_mainloop
parameter_list|(
name|guint32
name|running_time
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_test_run_mainloop_until_idle
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_test_bail_if_no_display
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __TESTS_H__ */
end_comment

end_unit

