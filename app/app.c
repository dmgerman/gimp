begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/* Win32 language lookup table:  * Copyright (C) 2007-2008 Dieter Verfaillie<dieterv@optionexplicit.be>  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<locale.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_SYS_PARAM_H
end_ifdef

begin_include
include|#
directive|include
file|<sys/param.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_UNISTD_H
end_ifdef

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_include
include|#
directive|include
file|<windows.h>
end_include

begin_include
include|#
directive|include
file|<winnls.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/core-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimprc.h"
end_include

begin_include
include|#
directive|include
file|"base/base.h"
end_include

begin_include
include|#
directive|include
file|"base/tile-swap.h"
end_include

begin_include
include|#
directive|include
file|"gegl/gimp-gegl.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp-user-install.h"
end_include

begin_include
include|#
directive|include
file|"file/file-open.h"
end_include

begin_ifndef
ifndef|#
directive|ifndef
name|GIMP_CONSOLE_COMPILATION
end_ifndef

begin_include
include|#
directive|include
file|"dialogs/user-install-dialog.h"
end_include

begin_include
include|#
directive|include
file|"gui/gui.h"
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"app.h"
end_include

begin_include
include|#
directive|include
file|"batch.h"
end_include

begin_include
include|#
directive|include
file|"errors.h"
end_include

begin_include
include|#
directive|include
file|"units.h"
end_include

begin_include
include|#
directive|include
file|"gimp-debug.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  local prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|app_init_update_noop
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
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|app_init_language
parameter_list|(
specifier|const
name|gchar
modifier|*
name|language
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|app_exit_after_callback
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gboolean
name|kill_it
parameter_list|,
name|GMainLoop
modifier|*
name|loop
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|app_libs_init (GOptionContext * context,gboolean no_interface)
name|app_libs_init
parameter_list|(
name|GOptionContext
modifier|*
name|context
parameter_list|,
name|gboolean
name|no_interface
parameter_list|)
block|{
name|g_type_init
argument_list|()
expr_stmt|;
name|g_option_context_add_group
argument_list|(
name|context
argument_list|,
name|gegl_get_option_group
argument_list|()
argument_list|)
expr_stmt|;
ifndef|#
directive|ifndef
name|GIMP_CONSOLE_COMPILATION
if|if
condition|(
operator|!
name|no_interface
condition|)
block|{
name|gui_libs_init
argument_list|(
name|context
argument_list|)
expr_stmt|;
block|}
endif|#
directive|endif
block|}
end_function

begin_function
name|void
DECL|function|app_abort (gboolean no_interface,const gchar * abort_message)
name|app_abort
parameter_list|(
name|gboolean
name|no_interface
parameter_list|,
specifier|const
name|gchar
modifier|*
name|abort_message
parameter_list|)
block|{
ifndef|#
directive|ifndef
name|GIMP_CONSOLE_COMPILATION
if|if
condition|(
name|no_interface
condition|)
endif|#
directive|endif
block|{
name|g_print
argument_list|(
literal|"%s\n\n"
argument_list|,
name|abort_message
argument_list|)
expr_stmt|;
block|}
ifndef|#
directive|ifndef
name|GIMP_CONSOLE_COMPILATION
else|else
block|{
name|gui_abort
argument_list|(
name|abort_message
argument_list|)
expr_stmt|;
block|}
endif|#
directive|endif
name|app_exit
argument_list|(
name|EXIT_FAILURE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|app_exit (gint status)
name|app_exit
parameter_list|(
name|gint
name|status
parameter_list|)
block|{
name|exit
argument_list|(
name|status
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|app_run (const gchar * full_prog_name,const gchar ** filenames,const gchar * alternate_system_gimprc,const gchar * alternate_gimprc,const gchar * session_name,const gchar * batch_interpreter,const gchar ** batch_commands,gboolean as_new,gboolean no_interface,gboolean no_data,gboolean no_fonts,gboolean no_splash,gboolean be_verbose,gboolean use_shm,gboolean use_cpu_accel,gboolean console_messages,gboolean use_debug_handler,GimpStackTraceMode stack_trace_mode,GimpPDBCompatMode pdb_compat_mode)
name|app_run
parameter_list|(
specifier|const
name|gchar
modifier|*
name|full_prog_name
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|filenames
parameter_list|,
specifier|const
name|gchar
modifier|*
name|alternate_system_gimprc
parameter_list|,
specifier|const
name|gchar
modifier|*
name|alternate_gimprc
parameter_list|,
specifier|const
name|gchar
modifier|*
name|session_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|batch_interpreter
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|batch_commands
parameter_list|,
name|gboolean
name|as_new
parameter_list|,
name|gboolean
name|no_interface
parameter_list|,
name|gboolean
name|no_data
parameter_list|,
name|gboolean
name|no_fonts
parameter_list|,
name|gboolean
name|no_splash
parameter_list|,
name|gboolean
name|be_verbose
parameter_list|,
name|gboolean
name|use_shm
parameter_list|,
name|gboolean
name|use_cpu_accel
parameter_list|,
name|gboolean
name|console_messages
parameter_list|,
name|gboolean
name|use_debug_handler
parameter_list|,
name|GimpStackTraceMode
name|stack_trace_mode
parameter_list|,
name|GimpPDBCompatMode
name|pdb_compat_mode
parameter_list|)
block|{
name|GimpInitStatusFunc
name|update_status_func
init|=
name|NULL
decl_stmt|;
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|GimpBaseConfig
modifier|*
name|config
decl_stmt|;
name|GMainLoop
modifier|*
name|loop
decl_stmt|;
name|gboolean
name|swap_is_ok
decl_stmt|;
comment|/*  Create an instance of the "Gimp" object which is the root of the    *  core object system    */
name|gimp
operator|=
name|gimp_new
argument_list|(
name|full_prog_name
argument_list|,
name|session_name
argument_list|,
name|be_verbose
argument_list|,
name|no_data
argument_list|,
name|no_fonts
argument_list|,
name|no_interface
argument_list|,
name|use_shm
argument_list|,
name|console_messages
argument_list|,
name|stack_trace_mode
argument_list|,
name|pdb_compat_mode
argument_list|)
expr_stmt|;
name|errors_init
argument_list|(
name|gimp
argument_list|,
name|full_prog_name
argument_list|,
name|use_debug_handler
argument_list|,
name|stack_trace_mode
argument_list|)
expr_stmt|;
name|units_init
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
comment|/*  Check if the user's gimp_directory exists    */
if|if
condition|(
operator|!
name|g_file_test
argument_list|(
name|gimp_directory
argument_list|()
argument_list|,
name|G_FILE_TEST_IS_DIR
argument_list|)
condition|)
block|{
name|GimpUserInstall
modifier|*
name|install
init|=
name|gimp_user_install_new
argument_list|(
name|be_verbose
argument_list|)
decl_stmt|;
ifdef|#
directive|ifdef
name|GIMP_CONSOLE_COMPILATION
name|gimp_user_install_run
argument_list|(
name|install
argument_list|)
expr_stmt|;
else|#
directive|else
if|if
condition|(
operator|!
operator|(
name|no_interface
condition|?
name|gimp_user_install_run
argument_list|(
name|install
argument_list|)
else|:
name|user_install_dialog_run
argument_list|(
name|install
argument_list|)
operator|)
condition|)
name|exit
argument_list|(
name|EXIT_FAILURE
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|gimp_user_install_free
argument_list|(
name|install
argument_list|)
expr_stmt|;
block|}
name|gimp_load_config
argument_list|(
name|gimp
argument_list|,
name|alternate_system_gimprc
argument_list|,
name|alternate_gimprc
argument_list|)
expr_stmt|;
name|config
operator|=
name|GIMP_BASE_CONFIG
argument_list|(
name|gimp
operator|->
name|config
argument_list|)
expr_stmt|;
comment|/*  change the locale if a language if specified  */
name|app_init_language
argument_list|(
name|gimp
operator|->
name|config
operator|->
name|language
argument_list|)
expr_stmt|;
comment|/*  initialize lowlevel stuff  */
name|swap_is_ok
operator|=
name|base_init
argument_list|(
name|config
argument_list|,
name|be_verbose
argument_list|,
name|use_cpu_accel
argument_list|)
expr_stmt|;
name|gimp_gegl_init
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
ifndef|#
directive|ifndef
name|GIMP_CONSOLE_COMPILATION
if|if
condition|(
operator|!
name|no_interface
condition|)
name|update_status_func
operator|=
name|gui_init
argument_list|(
name|gimp
argument_list|,
name|no_splash
argument_list|)
expr_stmt|;
endif|#
directive|endif
if|if
condition|(
operator|!
name|update_status_func
condition|)
name|update_status_func
operator|=
name|app_init_update_noop
expr_stmt|;
comment|/*  Create all members of the global Gimp instance which need an already    *  parsed gimprc, e.g. the data factories    */
name|gimp_initialize
argument_list|(
name|gimp
argument_list|,
name|update_status_func
argument_list|)
expr_stmt|;
comment|/*  Load all data files    */
name|gimp_restore
argument_list|(
name|gimp
argument_list|,
name|update_status_func
argument_list|)
expr_stmt|;
comment|/* display a warning when no test swap file could be generated */
if|if
condition|(
operator|!
name|swap_is_ok
condition|)
block|{
name|gchar
modifier|*
name|path
init|=
name|gimp_config_path_expand
argument_list|(
name|config
operator|->
name|swap_path
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Unable to open a test swap file.\n\n"
literal|"To avoid data loss, please check the location "
literal|"and permissions of the swap directory defined in "
literal|"your Preferences (currently \"%s\")."
argument_list|)
argument_list|,
name|path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
block|}
comment|/*  enable autosave late so we don't autosave when the    *  monitor resolution is set in gui_init()    */
name|gimp_rc_set_autosave
argument_list|(
name|GIMP_RC
argument_list|(
name|gimp
operator|->
name|edit_config
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/*  Load the images given on the command-line.    */
if|if
condition|(
name|filenames
condition|)
block|{
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|filenames
index|[
name|i
index|]
operator|!=
name|NULL
condition|;
name|i
operator|++
control|)
name|file_open_from_command_line
argument_list|(
name|gimp
argument_list|,
name|filenames
index|[
name|i
index|]
argument_list|,
name|as_new
argument_list|)
expr_stmt|;
block|}
name|batch_run
argument_list|(
name|gimp
argument_list|,
name|batch_interpreter
argument_list|,
name|batch_commands
argument_list|)
expr_stmt|;
name|loop
operator|=
name|g_main_loop_new
argument_list|(
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_signal_connect_after
argument_list|(
name|gimp
argument_list|,
literal|"exit"
argument_list|,
name|G_CALLBACK
argument_list|(
name|app_exit_after_callback
argument_list|)
argument_list|,
name|loop
argument_list|)
expr_stmt|;
name|gimp_threads_leave
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|g_main_loop_run
argument_list|(
name|loop
argument_list|)
expr_stmt|;
name|gimp_threads_enter
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|g_main_loop_unref
argument_list|(
name|loop
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|gimp_debug_instances
argument_list|()
expr_stmt|;
name|errors_exit
argument_list|()
expr_stmt|;
name|gegl_exit
argument_list|()
expr_stmt|;
name|base_exit
argument_list|()
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|app_init_update_noop (const gchar * text1,const gchar * text2,gdouble percentage)
name|app_init_update_noop
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
block|{
comment|/*  deliberately do nothing  */
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|app_init_language (const gchar * language)
name|app_init_language
parameter_list|(
specifier|const
name|gchar
modifier|*
name|language
parameter_list|)
block|{
ifdef|#
directive|ifdef
name|G_OS_WIN32
if|if
condition|(
operator|!
name|language
condition|)
block|{
comment|/* FIXME: This is a hack. gettext doesn't pick the right language        * by default on Windows, so we enforce the right one. The        * following code is an adaptation of Python code from        * pynicotine. For reasons why this approach is needed, and why        * the GetLocaleInfo() approach in other libs falls flat, see:        * http://blogs.msdn.com/b/michkap/archive/2007/04/15/2146890.aspx        */
switch|switch
condition|(
name|GetUserDefaultUILanguage
argument_list|()
condition|)
block|{
case|case
literal|1078
case|:
name|language
operator|=
literal|"af"
expr_stmt|;
comment|/* Afrikaans - South Africa */
break|break;
case|case
literal|1052
case|:
name|language
operator|=
literal|"sq"
expr_stmt|;
comment|/* Albanian - Albania */
break|break;
case|case
literal|1118
case|:
name|language
operator|=
literal|"am"
expr_stmt|;
comment|/* Amharic - Ethiopia */
break|break;
case|case
literal|1025
case|:
name|language
operator|=
literal|"ar"
expr_stmt|;
comment|/* Arabic - Saudi Arabia */
break|break;
case|case
literal|5121
case|:
name|language
operator|=
literal|"ar"
expr_stmt|;
comment|/* Arabic - Algeria */
break|break;
case|case
literal|15361
case|:
name|language
operator|=
literal|"ar"
expr_stmt|;
comment|/* Arabic - Bahrain */
break|break;
case|case
literal|3073
case|:
name|language
operator|=
literal|"ar"
expr_stmt|;
comment|/* Arabic - Egypt */
break|break;
case|case
literal|2049
case|:
name|language
operator|=
literal|"ar"
expr_stmt|;
comment|/* Arabic - Iraq */
break|break;
case|case
literal|11265
case|:
name|language
operator|=
literal|"ar"
expr_stmt|;
comment|/* Arabic - Jordan */
break|break;
case|case
literal|13313
case|:
name|language
operator|=
literal|"ar"
expr_stmt|;
comment|/* Arabic - Kuwait */
break|break;
case|case
literal|12289
case|:
name|language
operator|=
literal|"ar"
expr_stmt|;
comment|/* Arabic - Lebanon */
break|break;
case|case
literal|4097
case|:
name|language
operator|=
literal|"ar"
expr_stmt|;
comment|/* Arabic - Libya */
break|break;
case|case
literal|6145
case|:
name|language
operator|=
literal|"ar"
expr_stmt|;
comment|/* Arabic - Morocco */
break|break;
case|case
literal|8193
case|:
name|language
operator|=
literal|"ar"
expr_stmt|;
comment|/* Arabic - Oman */
break|break;
case|case
literal|16385
case|:
name|language
operator|=
literal|"ar"
expr_stmt|;
comment|/* Arabic - Qatar */
break|break;
case|case
literal|10241
case|:
name|language
operator|=
literal|"ar"
expr_stmt|;
comment|/* Arabic - Syria */
break|break;
case|case
literal|7169
case|:
name|language
operator|=
literal|"ar"
expr_stmt|;
comment|/* Arabic - Tunisia */
break|break;
case|case
literal|14337
case|:
name|language
operator|=
literal|"ar"
expr_stmt|;
comment|/* Arabic - U.A.E. */
break|break;
case|case
literal|9217
case|:
name|language
operator|=
literal|"ar"
expr_stmt|;
comment|/* Arabic - Yemen */
break|break;
case|case
literal|1067
case|:
name|language
operator|=
literal|"hy"
expr_stmt|;
comment|/* Armenian - Armenia */
break|break;
case|case
literal|1101
case|:
name|language
operator|=
literal|"as"
expr_stmt|;
comment|/* Assamese */
break|break;
case|case
literal|2092
case|:
name|language
operator|=
name|NULL
expr_stmt|;
comment|/* Azeri (Cyrillic) */
break|break;
case|case
literal|1068
case|:
name|language
operator|=
name|NULL
expr_stmt|;
comment|/* Azeri (Latin) */
break|break;
case|case
literal|1069
case|:
name|language
operator|=
literal|"eu"
expr_stmt|;
comment|/* Basque */
break|break;
case|case
literal|1059
case|:
name|language
operator|=
literal|"be"
expr_stmt|;
comment|/* Belarusian */
break|break;
case|case
literal|1093
case|:
name|language
operator|=
literal|"bn"
expr_stmt|;
comment|/* Bengali (India) */
break|break;
case|case
literal|2117
case|:
name|language
operator|=
literal|"bn"
expr_stmt|;
comment|/* Bengali (Bangladesh) */
break|break;
case|case
literal|5146
case|:
name|language
operator|=
literal|"bs"
expr_stmt|;
comment|/* Bosnian (Bosnia/Herzegovina) */
break|break;
case|case
literal|1026
case|:
name|language
operator|=
literal|"bg"
expr_stmt|;
comment|/* Bulgarian */
break|break;
case|case
literal|1109
case|:
name|language
operator|=
literal|"my"
expr_stmt|;
comment|/* Burmese */
break|break;
case|case
literal|1027
case|:
name|language
operator|=
literal|"ca"
expr_stmt|;
comment|/* Catalan */
break|break;
case|case
literal|1116
case|:
name|language
operator|=
name|NULL
expr_stmt|;
comment|/* Cherokee - United States */
break|break;
case|case
literal|2052
case|:
name|language
operator|=
literal|"zh"
expr_stmt|;
comment|/* Chinese - People"s Republic of China */
break|break;
case|case
literal|4100
case|:
name|language
operator|=
literal|"zh"
expr_stmt|;
comment|/* Chinese - Singapore */
break|break;
case|case
literal|1028
case|:
name|language
operator|=
literal|"zh"
expr_stmt|;
comment|/* Chinese - Taiwan */
break|break;
case|case
literal|3076
case|:
name|language
operator|=
literal|"zh"
expr_stmt|;
comment|/* Chinese - Hong Kong SAR */
break|break;
case|case
literal|5124
case|:
name|language
operator|=
literal|"zh"
expr_stmt|;
comment|/* Chinese - Macao SAR */
break|break;
case|case
literal|1050
case|:
name|language
operator|=
literal|"hr"
expr_stmt|;
comment|/* Croatian */
break|break;
case|case
literal|4122
case|:
name|language
operator|=
literal|"hr"
expr_stmt|;
comment|/* Croatian (Bosnia/Herzegovina) */
break|break;
case|case
literal|1029
case|:
name|language
operator|=
literal|"cs"
expr_stmt|;
comment|/* Czech */
break|break;
case|case
literal|1030
case|:
name|language
operator|=
literal|"da"
expr_stmt|;
comment|/* Danish */
break|break;
case|case
literal|1125
case|:
name|language
operator|=
literal|"dv"
expr_stmt|;
comment|/* Divehi */
break|break;
case|case
literal|1043
case|:
name|language
operator|=
literal|"nl"
expr_stmt|;
comment|/* Dutch - Netherlands */
break|break;
case|case
literal|2067
case|:
name|language
operator|=
literal|"nl"
expr_stmt|;
comment|/* Dutch - Belgium */
break|break;
case|case
literal|1126
case|:
name|language
operator|=
name|NULL
expr_stmt|;
comment|/* Edo */
break|break;
case|case
literal|1033
case|:
name|language
operator|=
literal|"en"
expr_stmt|;
comment|/* English - United States */
break|break;
case|case
literal|2057
case|:
name|language
operator|=
literal|"en"
expr_stmt|;
comment|/* English - United Kingdom */
break|break;
case|case
literal|3081
case|:
name|language
operator|=
literal|"en"
expr_stmt|;
comment|/* English - Australia */
break|break;
case|case
literal|10249
case|:
name|language
operator|=
literal|"en"
expr_stmt|;
comment|/* English - Belize */
break|break;
case|case
literal|4105
case|:
name|language
operator|=
literal|"en"
expr_stmt|;
comment|/* English - Canada */
break|break;
case|case
literal|9225
case|:
name|language
operator|=
literal|"en"
expr_stmt|;
comment|/* English - Caribbean */
break|break;
case|case
literal|15369
case|:
name|language
operator|=
literal|"en"
expr_stmt|;
comment|/* English - Hong Kong SAR */
break|break;
case|case
literal|16393
case|:
name|language
operator|=
literal|"en"
expr_stmt|;
comment|/* English - India */
break|break;
case|case
literal|14345
case|:
name|language
operator|=
literal|"en"
expr_stmt|;
comment|/* English - Indonesia */
break|break;
case|case
literal|6153
case|:
name|language
operator|=
literal|"en"
expr_stmt|;
comment|/* English - Ireland */
break|break;
case|case
literal|8201
case|:
name|language
operator|=
literal|"en"
expr_stmt|;
comment|/* English - Jamaica */
break|break;
case|case
literal|17417
case|:
name|language
operator|=
literal|"en"
expr_stmt|;
comment|/* English - Malaysia */
break|break;
case|case
literal|5129
case|:
name|language
operator|=
literal|"en"
expr_stmt|;
comment|/* English - New Zealand */
break|break;
case|case
literal|13321
case|:
name|language
operator|=
literal|"en"
expr_stmt|;
comment|/* English - Philippines */
break|break;
case|case
literal|18441
case|:
name|language
operator|=
literal|"en"
expr_stmt|;
comment|/* English - Singapore */
break|break;
case|case
literal|7177
case|:
name|language
operator|=
literal|"en"
expr_stmt|;
comment|/* English - South Africa */
break|break;
case|case
literal|11273
case|:
name|language
operator|=
literal|"en"
expr_stmt|;
comment|/* English - Trinidad */
break|break;
case|case
literal|12297
case|:
name|language
operator|=
literal|"en"
expr_stmt|;
comment|/* English - Zimbabwe */
break|break;
case|case
literal|1061
case|:
name|language
operator|=
literal|"et"
expr_stmt|;
comment|/* Estonian */
break|break;
case|case
literal|1080
case|:
name|language
operator|=
literal|"fo"
expr_stmt|;
comment|/* Faroese */
break|break;
case|case
literal|1065
case|:
name|language
operator|=
name|NULL
expr_stmt|;
comment|/* Farsi */
break|break;
case|case
literal|1124
case|:
name|language
operator|=
name|NULL
expr_stmt|;
comment|/* Filipino */
break|break;
case|case
literal|1035
case|:
name|language
operator|=
literal|"fi"
expr_stmt|;
comment|/* Finnish */
break|break;
case|case
literal|1036
case|:
name|language
operator|=
literal|"fr"
expr_stmt|;
comment|/* French - France */
break|break;
case|case
literal|2060
case|:
name|language
operator|=
literal|"fr"
expr_stmt|;
comment|/* French - Belgium */
break|break;
case|case
literal|11276
case|:
name|language
operator|=
literal|"fr"
expr_stmt|;
comment|/* French - Cameroon */
break|break;
case|case
literal|3084
case|:
name|language
operator|=
literal|"fr"
expr_stmt|;
comment|/* French - Canada */
break|break;
case|case
literal|9228
case|:
name|language
operator|=
literal|"fr"
expr_stmt|;
comment|/* French - Democratic Rep. of Congo */
break|break;
case|case
literal|12300
case|:
name|language
operator|=
literal|"fr"
expr_stmt|;
comment|/* French - Cote d"Ivoire */
break|break;
case|case
literal|15372
case|:
name|language
operator|=
literal|"fr"
expr_stmt|;
comment|/* French - Haiti */
break|break;
case|case
literal|5132
case|:
name|language
operator|=
literal|"fr"
expr_stmt|;
comment|/* French - Luxembourg */
break|break;
case|case
literal|13324
case|:
name|language
operator|=
literal|"fr"
expr_stmt|;
comment|/* French - Mali */
break|break;
case|case
literal|6156
case|:
name|language
operator|=
literal|"fr"
expr_stmt|;
comment|/* French - Monaco */
break|break;
case|case
literal|14348
case|:
name|language
operator|=
literal|"fr"
expr_stmt|;
comment|/* French - Morocco */
break|break;
case|case
literal|58380
case|:
name|language
operator|=
literal|"fr"
expr_stmt|;
comment|/* French - North Africa */
break|break;
case|case
literal|8204
case|:
name|language
operator|=
literal|"fr"
expr_stmt|;
comment|/* French - Reunion */
break|break;
case|case
literal|10252
case|:
name|language
operator|=
literal|"fr"
expr_stmt|;
comment|/* French - Senegal */
break|break;
case|case
literal|4108
case|:
name|language
operator|=
literal|"fr"
expr_stmt|;
comment|/* French - Switzerland */
break|break;
case|case
literal|7180
case|:
name|language
operator|=
literal|"fr"
expr_stmt|;
comment|/* French - West Indies */
break|break;
case|case
literal|1122
case|:
name|language
operator|=
literal|"fy"
expr_stmt|;
comment|/* Frisian - Netherlands */
break|break;
case|case
literal|1127
case|:
name|language
operator|=
name|NULL
expr_stmt|;
comment|/* Fulfulde - Nigeria */
break|break;
case|case
literal|1071
case|:
name|language
operator|=
literal|"mk"
expr_stmt|;
comment|/* FYRO Macedonian */
break|break;
case|case
literal|2108
case|:
name|language
operator|=
literal|"ga"
expr_stmt|;
comment|/* Gaelic (Ireland) */
break|break;
case|case
literal|1084
case|:
name|language
operator|=
literal|"gd"
expr_stmt|;
comment|/* Gaelic (Scotland) */
break|break;
case|case
literal|1110
case|:
name|language
operator|=
literal|"gl"
expr_stmt|;
comment|/* Galician */
break|break;
case|case
literal|1079
case|:
name|language
operator|=
literal|"ka"
expr_stmt|;
comment|/* Georgian */
break|break;
case|case
literal|1031
case|:
name|language
operator|=
literal|"de"
expr_stmt|;
comment|/* German - Germany */
break|break;
case|case
literal|3079
case|:
name|language
operator|=
literal|"de"
expr_stmt|;
comment|/* German - Austria */
break|break;
case|case
literal|5127
case|:
name|language
operator|=
literal|"de"
expr_stmt|;
comment|/* German - Liechtenstein */
break|break;
case|case
literal|4103
case|:
name|language
operator|=
literal|"de"
expr_stmt|;
comment|/* German - Luxembourg */
break|break;
case|case
literal|2055
case|:
name|language
operator|=
literal|"de"
expr_stmt|;
comment|/* German - Switzerland */
break|break;
case|case
literal|1032
case|:
name|language
operator|=
literal|"el"
expr_stmt|;
comment|/* Greek */
break|break;
case|case
literal|1140
case|:
name|language
operator|=
literal|"gn"
expr_stmt|;
comment|/* Guarani - Paraguay */
break|break;
case|case
literal|1095
case|:
name|language
operator|=
literal|"gu"
expr_stmt|;
comment|/* Gujarati */
break|break;
case|case
literal|1128
case|:
name|language
operator|=
literal|"ha"
expr_stmt|;
comment|/* Hausa - Nigeria */
break|break;
case|case
literal|1141
case|:
name|language
operator|=
name|NULL
expr_stmt|;
comment|/* Hawaiian - United States */
break|break;
case|case
literal|1037
case|:
name|language
operator|=
literal|"he"
expr_stmt|;
comment|/* Hebrew */
break|break;
case|case
literal|1081
case|:
name|language
operator|=
literal|"hi"
expr_stmt|;
comment|/* Hindi */
break|break;
case|case
literal|1038
case|:
name|language
operator|=
literal|"hu"
expr_stmt|;
comment|/* Hungarian */
break|break;
case|case
literal|1129
case|:
name|language
operator|=
name|NULL
expr_stmt|;
comment|/* Ibibio - Nigeria */
break|break;
case|case
literal|1039
case|:
name|language
operator|=
literal|"is"
expr_stmt|;
comment|/* Icelandic */
break|break;
case|case
literal|1136
case|:
name|language
operator|=
literal|"ig"
expr_stmt|;
comment|/* Igbo - Nigeria */
break|break;
case|case
literal|1057
case|:
name|language
operator|=
literal|"id"
expr_stmt|;
comment|/* Indonesian */
break|break;
case|case
literal|1117
case|:
name|language
operator|=
literal|"iu"
expr_stmt|;
comment|/* Inuktitut */
break|break;
case|case
literal|1040
case|:
name|language
operator|=
literal|"it"
expr_stmt|;
comment|/* Italian - Italy */
break|break;
case|case
literal|2064
case|:
name|language
operator|=
literal|"it"
expr_stmt|;
comment|/* Italian - Switzerland */
break|break;
case|case
literal|1041
case|:
name|language
operator|=
literal|"ja"
expr_stmt|;
comment|/* Japanese */
break|break;
case|case
literal|1099
case|:
name|language
operator|=
literal|"kn"
expr_stmt|;
comment|/* Kannada */
break|break;
case|case
literal|1137
case|:
name|language
operator|=
literal|"kr"
expr_stmt|;
comment|/* Kanuri - Nigeria */
break|break;
case|case
literal|2144
case|:
name|language
operator|=
literal|"ks"
expr_stmt|;
comment|/* Kashmiri */
break|break;
case|case
literal|1120
case|:
name|language
operator|=
literal|"ks"
expr_stmt|;
comment|/* Kashmiri (Arabic) */
break|break;
case|case
literal|1087
case|:
name|language
operator|=
literal|"kk"
expr_stmt|;
comment|/* Kazakh */
break|break;
case|case
literal|1107
case|:
name|language
operator|=
literal|"km"
expr_stmt|;
comment|/* Khmer */
break|break;
case|case
literal|1111
case|:
name|language
operator|=
name|NULL
expr_stmt|;
comment|/* Konkani */
break|break;
case|case
literal|1042
case|:
name|language
operator|=
literal|"ko"
expr_stmt|;
comment|/* Korean */
break|break;
case|case
literal|1088
case|:
name|language
operator|=
literal|"ky"
expr_stmt|;
comment|/* Kyrgyz (Cyrillic) */
break|break;
case|case
literal|1108
case|:
name|language
operator|=
literal|"lo"
expr_stmt|;
comment|/* Lao */
break|break;
case|case
literal|1142
case|:
name|language
operator|=
literal|"la"
expr_stmt|;
comment|/* Latin */
break|break;
case|case
literal|1062
case|:
name|language
operator|=
literal|"lv"
expr_stmt|;
comment|/* Latvian */
break|break;
case|case
literal|1063
case|:
name|language
operator|=
literal|"lt"
expr_stmt|;
comment|/* Lithuanian */
break|break;
case|case
literal|1086
case|:
name|language
operator|=
literal|"ms"
expr_stmt|;
comment|/* Malay - Malaysia */
break|break;
case|case
literal|2110
case|:
name|language
operator|=
literal|"ms"
expr_stmt|;
comment|/* Malay - Brunei Darussalam */
break|break;
case|case
literal|1100
case|:
name|language
operator|=
literal|"ml"
expr_stmt|;
comment|/* Malayalam */
break|break;
case|case
literal|1082
case|:
name|language
operator|=
literal|"mt"
expr_stmt|;
comment|/* Maltese */
break|break;
case|case
literal|1112
case|:
name|language
operator|=
name|NULL
expr_stmt|;
comment|/* Manipuri */
break|break;
case|case
literal|1153
case|:
name|language
operator|=
literal|"mi"
expr_stmt|;
comment|/* Maori - New Zealand */
break|break;
case|case
literal|1102
case|:
name|language
operator|=
literal|"mr"
expr_stmt|;
comment|/* Marathi */
break|break;
case|case
literal|1104
case|:
name|language
operator|=
literal|"mn"
expr_stmt|;
comment|/* Mongolian (Cyrillic) */
break|break;
case|case
literal|2128
case|:
name|language
operator|=
literal|"mn"
expr_stmt|;
comment|/* Mongolian (Mongolian) */
break|break;
case|case
literal|1121
case|:
name|language
operator|=
literal|"ne"
expr_stmt|;
comment|/* Nepali */
break|break;
case|case
literal|2145
case|:
name|language
operator|=
literal|"ne"
expr_stmt|;
comment|/* Nepali - India */
break|break;
case|case
literal|1044
case|:
name|language
operator|=
literal|"no"
expr_stmt|;
comment|/* Norwegian (Bokmï¿ï¾¥l) */
break|break;
case|case
literal|2068
case|:
name|language
operator|=
literal|"no"
expr_stmt|;
comment|/* Norwegian (Nynorsk) */
break|break;
case|case
literal|1096
case|:
name|language
operator|=
literal|"or"
expr_stmt|;
comment|/* Oriya */
break|break;
case|case
literal|1138
case|:
name|language
operator|=
literal|"om"
expr_stmt|;
comment|/* Oromo */
break|break;
case|case
literal|1145
case|:
name|language
operator|=
name|NULL
expr_stmt|;
comment|/* Papiamentu */
break|break;
case|case
literal|1123
case|:
name|language
operator|=
literal|"ps"
expr_stmt|;
comment|/* Pashto */
break|break;
case|case
literal|1045
case|:
name|language
operator|=
literal|"pl"
expr_stmt|;
comment|/* Polish */
break|break;
case|case
literal|1046
case|:
name|language
operator|=
literal|"pt"
expr_stmt|;
comment|/* Portuguese - Brazil */
break|break;
case|case
literal|2070
case|:
name|language
operator|=
literal|"pt"
expr_stmt|;
comment|/* Portuguese - Portugal */
break|break;
case|case
literal|1094
case|:
name|language
operator|=
literal|"pa"
expr_stmt|;
comment|/* Punjabi */
break|break;
case|case
literal|2118
case|:
name|language
operator|=
literal|"pa"
expr_stmt|;
comment|/* Punjabi (Pakistan) */
break|break;
case|case
literal|1131
case|:
name|language
operator|=
literal|"qu"
expr_stmt|;
comment|/* Quecha - Bolivia */
break|break;
case|case
literal|2155
case|:
name|language
operator|=
literal|"qu"
expr_stmt|;
comment|/* Quecha - Ecuador */
break|break;
case|case
literal|3179
case|:
name|language
operator|=
literal|"qu"
expr_stmt|;
comment|/* Quecha - Peru */
break|break;
case|case
literal|1047
case|:
name|language
operator|=
literal|"rm"
expr_stmt|;
comment|/* Rhaeto-Romanic */
break|break;
case|case
literal|1048
case|:
name|language
operator|=
literal|"ro"
expr_stmt|;
comment|/* Romanian */
break|break;
case|case
literal|2072
case|:
name|language
operator|=
literal|"ro"
expr_stmt|;
comment|/* Romanian - Moldava */
break|break;
case|case
literal|1049
case|:
name|language
operator|=
literal|"ru"
expr_stmt|;
comment|/* Russian */
break|break;
case|case
literal|2073
case|:
name|language
operator|=
literal|"ru"
expr_stmt|;
comment|/* Russian - Moldava */
break|break;
case|case
literal|1083
case|:
name|language
operator|=
name|NULL
expr_stmt|;
comment|/* Sami (Lappish) */
break|break;
case|case
literal|1103
case|:
name|language
operator|=
literal|"sa"
expr_stmt|;
comment|/* Sanskrit */
break|break;
case|case
literal|1132
case|:
name|language
operator|=
name|NULL
expr_stmt|;
comment|/* Sepedi */
break|break;
case|case
literal|3098
case|:
name|language
operator|=
literal|"sr"
expr_stmt|;
comment|/* Serbian (Cyrillic) */
break|break;
case|case
literal|2074
case|:
name|language
operator|=
literal|"sr"
expr_stmt|;
comment|/* Serbian (Latin) */
break|break;
case|case
literal|1113
case|:
name|language
operator|=
literal|"sd"
expr_stmt|;
comment|/* Sindhi - India */
break|break;
case|case
literal|2137
case|:
name|language
operator|=
literal|"sd"
expr_stmt|;
comment|/* Sindhi - Pakistan */
break|break;
case|case
literal|1115
case|:
name|language
operator|=
literal|"si"
expr_stmt|;
comment|/* Sinhalese - Sri Lanka */
break|break;
case|case
literal|1051
case|:
name|language
operator|=
literal|"sk"
expr_stmt|;
comment|/* Slovak */
break|break;
case|case
literal|1060
case|:
name|language
operator|=
literal|"sl"
expr_stmt|;
comment|/* Slovenian */
break|break;
case|case
literal|1143
case|:
name|language
operator|=
literal|"so"
expr_stmt|;
comment|/* Somali */
break|break;
case|case
literal|1070
case|:
name|language
operator|=
name|NULL
expr_stmt|;
comment|/* Sorbian */
break|break;
case|case
literal|3082
case|:
name|language
operator|=
literal|"es"
expr_stmt|;
comment|/* Spanish - Spain (Modern Sort) */
break|break;
case|case
literal|1034
case|:
name|language
operator|=
literal|"es"
expr_stmt|;
comment|/* Spanish - Spain (Traditional Sort) */
break|break;
case|case
literal|11274
case|:
name|language
operator|=
literal|"es"
expr_stmt|;
comment|/* Spanish - Argentina */
break|break;
case|case
literal|16394
case|:
name|language
operator|=
literal|"es"
expr_stmt|;
comment|/* Spanish - Bolivia */
break|break;
case|case
literal|13322
case|:
name|language
operator|=
literal|"es"
expr_stmt|;
comment|/* Spanish - Chile */
break|break;
case|case
literal|9226
case|:
name|language
operator|=
literal|"es"
expr_stmt|;
comment|/* Spanish - Colombia */
break|break;
case|case
literal|5130
case|:
name|language
operator|=
literal|"es"
expr_stmt|;
comment|/* Spanish - Costa Rica */
break|break;
case|case
literal|7178
case|:
name|language
operator|=
literal|"es"
expr_stmt|;
comment|/* Spanish - Dominican Republic */
break|break;
case|case
literal|12298
case|:
name|language
operator|=
literal|"es"
expr_stmt|;
comment|/* Spanish - Ecuador */
break|break;
case|case
literal|17418
case|:
name|language
operator|=
literal|"es"
expr_stmt|;
comment|/* Spanish - El Salvador */
break|break;
case|case
literal|4106
case|:
name|language
operator|=
literal|"es"
expr_stmt|;
comment|/* Spanish - Guatemala */
break|break;
case|case
literal|18442
case|:
name|language
operator|=
literal|"es"
expr_stmt|;
comment|/* Spanish - Honduras */
break|break;
case|case
literal|58378
case|:
name|language
operator|=
literal|"es"
expr_stmt|;
comment|/* Spanish - Latin America */
break|break;
case|case
literal|2058
case|:
name|language
operator|=
literal|"es"
expr_stmt|;
comment|/* Spanish - Mexico */
break|break;
case|case
literal|19466
case|:
name|language
operator|=
literal|"es"
expr_stmt|;
comment|/* Spanish - Nicaragua */
break|break;
case|case
literal|6154
case|:
name|language
operator|=
literal|"es"
expr_stmt|;
comment|/* Spanish - Panama */
break|break;
case|case
literal|15370
case|:
name|language
operator|=
literal|"es"
expr_stmt|;
comment|/* Spanish - Paraguay */
break|break;
case|case
literal|10250
case|:
name|language
operator|=
literal|"es"
expr_stmt|;
comment|/* Spanish - Peru */
break|break;
case|case
literal|20490
case|:
name|language
operator|=
literal|"es"
expr_stmt|;
comment|/* Spanish - Puerto Rico */
break|break;
case|case
literal|21514
case|:
name|language
operator|=
literal|"es"
expr_stmt|;
comment|/* Spanish - United States */
break|break;
case|case
literal|14346
case|:
name|language
operator|=
literal|"es"
expr_stmt|;
comment|/* Spanish - Uruguay */
break|break;
case|case
literal|8202
case|:
name|language
operator|=
literal|"es"
expr_stmt|;
comment|/* Spanish - Venezuela */
break|break;
case|case
literal|1072
case|:
name|language
operator|=
name|NULL
expr_stmt|;
comment|/* Sutu */
break|break;
case|case
literal|1089
case|:
name|language
operator|=
literal|"sw"
expr_stmt|;
comment|/* Swahili */
break|break;
case|case
literal|1053
case|:
name|language
operator|=
literal|"sv"
expr_stmt|;
comment|/* Swedish */
break|break;
case|case
literal|2077
case|:
name|language
operator|=
literal|"sv"
expr_stmt|;
comment|/* Swedish - Finland */
break|break;
case|case
literal|1114
case|:
name|language
operator|=
name|NULL
expr_stmt|;
comment|/* Syriac */
break|break;
case|case
literal|1064
case|:
name|language
operator|=
literal|"tg"
expr_stmt|;
comment|/* Tajik */
break|break;
case|case
literal|1119
case|:
name|language
operator|=
name|NULL
expr_stmt|;
comment|/* Tamazight (Arabic) */
break|break;
case|case
literal|2143
case|:
name|language
operator|=
name|NULL
expr_stmt|;
comment|/* Tamazight (Latin) */
break|break;
case|case
literal|1097
case|:
name|language
operator|=
literal|"ta"
expr_stmt|;
comment|/* Tamil */
break|break;
case|case
literal|1092
case|:
name|language
operator|=
literal|"tt"
expr_stmt|;
comment|/* Tatar */
break|break;
case|case
literal|1098
case|:
name|language
operator|=
literal|"te"
expr_stmt|;
comment|/* Telugu */
break|break;
case|case
literal|1054
case|:
name|language
operator|=
literal|"th"
expr_stmt|;
comment|/* Thai */
break|break;
case|case
literal|2129
case|:
name|language
operator|=
literal|"bo"
expr_stmt|;
comment|/* Tibetan - Bhutan */
break|break;
case|case
literal|1105
case|:
name|language
operator|=
literal|"bo"
expr_stmt|;
comment|/* Tibetan - People"s Republic of China */
break|break;
case|case
literal|2163
case|:
name|language
operator|=
literal|"ti"
expr_stmt|;
comment|/* Tigrigna - Eritrea */
break|break;
case|case
literal|1139
case|:
name|language
operator|=
literal|"ti"
expr_stmt|;
comment|/* Tigrigna - Ethiopia */
break|break;
case|case
literal|1073
case|:
name|language
operator|=
literal|"ts"
expr_stmt|;
comment|/* Tsonga */
break|break;
case|case
literal|1074
case|:
name|language
operator|=
literal|"tn"
expr_stmt|;
comment|/* Tswana */
break|break;
case|case
literal|1055
case|:
name|language
operator|=
literal|"tr"
expr_stmt|;
comment|/* Turkish */
break|break;
case|case
literal|1090
case|:
name|language
operator|=
literal|"tk"
expr_stmt|;
comment|/* Turkmen */
break|break;
case|case
literal|1152
case|:
name|language
operator|=
literal|"ug"
expr_stmt|;
comment|/* Uighur - China */
break|break;
case|case
literal|1058
case|:
name|language
operator|=
literal|"uk"
expr_stmt|;
comment|/* Ukrainian */
break|break;
case|case
literal|1056
case|:
name|language
operator|=
literal|"ur"
expr_stmt|;
comment|/* Urdu */
break|break;
case|case
literal|2080
case|:
name|language
operator|=
literal|"ur"
expr_stmt|;
comment|/* Urdu - India */
break|break;
case|case
literal|2115
case|:
name|language
operator|=
literal|"uz"
expr_stmt|;
comment|/* Uzbek (Cyrillic) */
break|break;
case|case
literal|1091
case|:
name|language
operator|=
literal|"uz"
expr_stmt|;
comment|/* Uzbek (Latin) */
break|break;
case|case
literal|1075
case|:
name|language
operator|=
literal|"ve"
expr_stmt|;
comment|/* Venda */
break|break;
case|case
literal|1066
case|:
name|language
operator|=
literal|"vi"
expr_stmt|;
comment|/* Vietnamese */
break|break;
case|case
literal|1106
case|:
name|language
operator|=
literal|"cy"
expr_stmt|;
comment|/* Welsh */
break|break;
case|case
literal|1076
case|:
name|language
operator|=
literal|"xh"
expr_stmt|;
comment|/* Xhosa */
break|break;
case|case
literal|1144
case|:
name|language
operator|=
name|NULL
expr_stmt|;
comment|/* Yi */
break|break;
case|case
literal|1085
case|:
name|language
operator|=
literal|"yi"
expr_stmt|;
comment|/* Yiddish */
break|break;
case|case
literal|1130
case|:
name|language
operator|=
literal|"yo"
expr_stmt|;
comment|/* Yoruba */
break|break;
case|case
literal|1077
case|:
name|language
operator|=
literal|"zu"
expr_stmt|;
comment|/* Zulu */
break|break;
default|default:
name|language
operator|=
name|NULL
expr_stmt|;
block|}
block|}
endif|#
directive|endif
comment|/*  We already set the locale according to the environment, so just    *  return early if no language is set in gimprc.    */
if|if
condition|(
operator|!
name|language
condition|)
return|return;
name|g_setenv
argument_list|(
literal|"LANGUAGE"
argument_list|,
name|language
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|setlocale
argument_list|(
name|LC_ALL
argument_list|,
literal|""
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|app_exit_after_callback (Gimp * gimp,gboolean kill_it,GMainLoop * loop)
name|app_exit_after_callback
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gboolean
name|kill_it
parameter_list|,
name|GMainLoop
modifier|*
name|loop
parameter_list|)
block|{
if|if
condition|(
name|gimp
operator|->
name|be_verbose
condition|)
name|g_print
argument_list|(
literal|"EXIT: %s\n"
argument_list|,
name|G_STRFUNC
argument_list|)
expr_stmt|;
comment|/*    *  In stable releases, we simply call exit() here. This speeds up    *  the process of quitting GIMP and also works around the problem    *  that plug-ins might still be running.    *    *  In unstable releases, we shut down GIMP properly in an attempt    *  to catch possible problems in our finalizers.    */
ifdef|#
directive|ifdef
name|GIMP_UNSTABLE
name|g_main_loop_quit
argument_list|(
name|loop
argument_list|)
expr_stmt|;
else|#
directive|else
name|gegl_exit
argument_list|()
expr_stmt|;
comment|/*  make sure that the swap files are removed before we quit */
name|tile_swap_exit
argument_list|()
expr_stmt|;
name|exit
argument_list|(
name|EXIT_SUCCESS
argument_list|)
expr_stmt|;
endif|#
directive|endif
return|return
name|FALSE
return|;
block|}
end_function

end_unit

