begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimp-user-install.c  * Copyright (C) 2000-2008 Michael Natterer and Sven Neumann  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/* This file contains functions to help migrate the settings from a  * previous GIMP version to be used with the current (newer) version.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<errno.h>
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
file|<sys/types.h>
end_include

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
file|<glib/gstdio.h>
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_include
include|#
directive|include
file|<libgimpbase/gimpwin32-io.h>
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
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpconfig-file.h"
end_include

begin_include
include|#
directive|include
file|"config/gimprc.h"
end_include

begin_include
include|#
directive|include
file|"gimp-templates.h"
end_include

begin_include
include|#
directive|include
file|"gimp-tags.h"
end_include

begin_include
include|#
directive|include
file|"gimp-user-install.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_struct
DECL|struct|_GimpUserInstall
struct|struct
name|_GimpUserInstall
block|{
DECL|member|verbose
name|gboolean
name|verbose
decl_stmt|;
DECL|member|old_dir
name|gchar
modifier|*
name|old_dir
decl_stmt|;
DECL|member|old_major
name|gint
name|old_major
decl_stmt|;
DECL|member|old_minor
name|gint
name|old_minor
decl_stmt|;
DECL|member|migrate
specifier|const
name|gchar
modifier|*
name|migrate
decl_stmt|;
DECL|member|log
name|GimpUserInstallLogFunc
name|log
decl_stmt|;
DECL|member|log_data
name|gpointer
name|log_data
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon28d342e40103
block|{
DECL|enumerator|USER_INSTALL_MKDIR
name|USER_INSTALL_MKDIR
block|,
comment|/* Create the directory        */
DECL|enumerator|USER_INSTALL_COPY
name|USER_INSTALL_COPY
comment|/* Copy from sysconf directory */
DECL|typedef|GimpUserInstallAction
block|}
name|GimpUserInstallAction
typedef|;
end_typedef

begin_struct
specifier|static
specifier|const
struct|struct
DECL|struct|__anon28d342e40208
block|{
DECL|member|name
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|action
name|GimpUserInstallAction
name|action
decl_stmt|;
block|}
DECL|variable|gimp_user_install_items
name|gimp_user_install_items
index|[]
init|=
block|{
block|{
literal|"gtkrc"
block|,
name|USER_INSTALL_COPY
block|}
block|,
block|{
literal|"menurc"
block|,
name|USER_INSTALL_COPY
block|}
block|,
block|{
literal|"brushes"
block|,
name|USER_INSTALL_MKDIR
block|}
block|,
block|{
literal|"dynamics"
block|,
name|USER_INSTALL_MKDIR
block|}
block|,
block|{
literal|"fonts"
block|,
name|USER_INSTALL_MKDIR
block|}
block|,
block|{
literal|"gradients"
block|,
name|USER_INSTALL_MKDIR
block|}
block|,
block|{
literal|"palettes"
block|,
name|USER_INSTALL_MKDIR
block|}
block|,
block|{
literal|"patterns"
block|,
name|USER_INSTALL_MKDIR
block|}
block|,
block|{
literal|"tool-presets"
block|,
name|USER_INSTALL_MKDIR
block|}
block|,
block|{
literal|"plug-ins"
block|,
name|USER_INSTALL_MKDIR
block|}
block|,
block|{
literal|"modules"
block|,
name|USER_INSTALL_MKDIR
block|}
block|,
block|{
literal|"interpreters"
block|,
name|USER_INSTALL_MKDIR
block|}
block|,
block|{
literal|"environ"
block|,
name|USER_INSTALL_MKDIR
block|}
block|,
block|{
literal|"scripts"
block|,
name|USER_INSTALL_MKDIR
block|}
block|,
block|{
literal|"templates"
block|,
name|USER_INSTALL_MKDIR
block|}
block|,
block|{
literal|"themes"
block|,
name|USER_INSTALL_MKDIR
block|}
block|,
block|{
literal|"tmp"
block|,
name|USER_INSTALL_MKDIR
block|}
block|,
block|{
literal|"curves"
block|,
name|USER_INSTALL_MKDIR
block|}
block|,
block|{
literal|"levels"
block|,
name|USER_INSTALL_MKDIR
block|}
block|,
block|{
literal|"filters"
block|,
name|USER_INSTALL_MKDIR
block|}
block|,
block|{
literal|"fractalexplorer"
block|,
name|USER_INSTALL_MKDIR
block|}
block|,
block|{
literal|"gfig"
block|,
name|USER_INSTALL_MKDIR
block|}
block|,
block|{
literal|"gflare"
block|,
name|USER_INSTALL_MKDIR
block|}
block|,
block|{
literal|"gimpressionist"
block|,
name|USER_INSTALL_MKDIR
block|}
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|gboolean
name|user_install_detect_old
parameter_list|(
name|GimpUserInstall
modifier|*
name|install
parameter_list|,
specifier|const
name|gchar
modifier|*
name|gimp_dir
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gchar
modifier|*
name|user_install_old_style_gimpdir
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|user_install_log
parameter_list|(
name|GimpUserInstall
modifier|*
name|install
parameter_list|,
specifier|const
name|gchar
modifier|*
name|format
parameter_list|,
modifier|...
parameter_list|)
function_decl|G_GNUC_PRINTF
parameter_list|(
function_decl|2
operator|,
function_decl|3
end_function_decl

begin_empty_stmt
unit|)
empty_stmt|;
end_empty_stmt

begin_function_decl
specifier|static
name|void
name|user_install_log_newline
parameter_list|(
name|GimpUserInstall
modifier|*
name|install
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|user_install_log_error
parameter_list|(
name|GimpUserInstall
modifier|*
name|install
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|user_install_mkdir
parameter_list|(
name|GimpUserInstall
modifier|*
name|install
parameter_list|,
specifier|const
name|gchar
modifier|*
name|dirname
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|user_install_mkdir_with_parents
parameter_list|(
name|GimpUserInstall
modifier|*
name|install
parameter_list|,
specifier|const
name|gchar
modifier|*
name|dirname
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|user_install_file_copy
parameter_list|(
name|GimpUserInstall
modifier|*
name|install
parameter_list|,
specifier|const
name|gchar
modifier|*
name|source
parameter_list|,
specifier|const
name|gchar
modifier|*
name|dest
parameter_list|,
specifier|const
name|gchar
modifier|*
name|old_options_regexp
parameter_list|,
name|GRegexEvalCallback
name|update_callback
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|user_install_dir_copy
parameter_list|(
name|GimpUserInstall
modifier|*
name|install
parameter_list|,
specifier|const
name|gchar
modifier|*
name|source
parameter_list|,
specifier|const
name|gchar
modifier|*
name|base
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|user_install_create_files
parameter_list|(
name|GimpUserInstall
modifier|*
name|install
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|user_install_migrate_files
parameter_list|(
name|GimpUserInstall
modifier|*
name|install
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpUserInstall
modifier|*
DECL|function|gimp_user_install_new (gboolean verbose)
name|gimp_user_install_new
parameter_list|(
name|gboolean
name|verbose
parameter_list|)
block|{
name|GimpUserInstall
modifier|*
name|install
init|=
name|g_slice_new0
argument_list|(
name|GimpUserInstall
argument_list|)
decl_stmt|;
name|install
operator|->
name|verbose
operator|=
name|verbose
expr_stmt|;
name|user_install_detect_old
argument_list|(
name|install
argument_list|,
name|gimp_directory
argument_list|()
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|install
operator|->
name|old_dir
condition|)
block|{
comment|/* if the default XDG-style config directory was not found, try        * the "old-style" path in the home folder.        */
name|gchar
modifier|*
name|dir
init|=
name|user_install_old_style_gimpdir
argument_list|()
decl_stmt|;
name|user_install_detect_old
argument_list|(
name|install
argument_list|,
name|dir
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|dir
argument_list|)
expr_stmt|;
block|}
return|return
name|install
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_user_install_run (GimpUserInstall * install)
name|gimp_user_install_run
parameter_list|(
name|GimpUserInstall
modifier|*
name|install
parameter_list|)
block|{
name|gchar
modifier|*
name|dirname
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|install
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|dirname
operator|=
name|g_filename_display_name
argument_list|(
name|gimp_directory
argument_list|()
argument_list|)
expr_stmt|;
if|if
condition|(
name|install
operator|->
name|migrate
condition|)
name|user_install_log
argument_list|(
name|install
argument_list|,
name|_
argument_list|(
literal|"It seems you have used GIMP %s before.  "
literal|"GIMP will now migrate your user settings to '%s'."
argument_list|)
argument_list|,
name|install
operator|->
name|migrate
argument_list|,
name|dirname
argument_list|)
expr_stmt|;
else|else
name|user_install_log
argument_list|(
name|install
argument_list|,
name|_
argument_list|(
literal|"It appears that you are using GIMP for the "
literal|"first time.  GIMP will now create a folder "
literal|"named '%s' and copy some files to it."
argument_list|)
argument_list|,
name|dirname
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|dirname
argument_list|)
expr_stmt|;
name|user_install_log_newline
argument_list|(
name|install
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|user_install_mkdir_with_parents
argument_list|(
name|install
argument_list|,
name|gimp_directory
argument_list|()
argument_list|)
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
name|install
operator|->
name|migrate
condition|)
if|if
condition|(
operator|!
name|user_install_migrate_files
argument_list|(
name|install
argument_list|)
condition|)
return|return
name|FALSE
return|;
return|return
name|user_install_create_files
argument_list|(
name|install
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_user_install_free (GimpUserInstall * install)
name|gimp_user_install_free
parameter_list|(
name|GimpUserInstall
modifier|*
name|install
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|install
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|install
operator|->
name|old_dir
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|GimpUserInstall
argument_list|,
name|install
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_user_install_set_log_handler (GimpUserInstall * install,GimpUserInstallLogFunc log,gpointer user_data)
name|gimp_user_install_set_log_handler
parameter_list|(
name|GimpUserInstall
modifier|*
name|install
parameter_list|,
name|GimpUserInstallLogFunc
name|log
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|install
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|install
operator|->
name|log
operator|=
name|log
expr_stmt|;
name|install
operator|->
name|log_data
operator|=
name|user_data
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  Local functions  */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|user_install_detect_old (GimpUserInstall * install,const gchar * gimp_dir)
name|user_install_detect_old
parameter_list|(
name|GimpUserInstall
modifier|*
name|install
parameter_list|,
specifier|const
name|gchar
modifier|*
name|gimp_dir
parameter_list|)
block|{
name|gchar
modifier|*
name|dir
init|=
name|g_strdup
argument_list|(
name|gimp_dir
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|version
decl_stmt|;
name|gboolean
name|migrate
init|=
name|FALSE
decl_stmt|;
name|version
operator|=
name|strstr
argument_list|(
name|dir
argument_list|,
name|GIMP_APP_VERSION
argument_list|)
expr_stmt|;
if|if
condition|(
name|version
condition|)
block|{
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
operator|(
name|GIMP_MINOR_VERSION
operator|&
operator|~
literal|1
operator|)
init|;
name|i
operator|>=
literal|0
condition|;
name|i
operator|-=
literal|2
control|)
block|{
comment|/*  we assume that GIMP_APP_VERSION is in the form '2.x'  */
name|g_snprintf
argument_list|(
name|version
operator|+
literal|2
argument_list|,
literal|2
argument_list|,
literal|"%d"
argument_list|,
name|i
argument_list|)
expr_stmt|;
name|migrate
operator|=
name|g_file_test
argument_list|(
name|dir
argument_list|,
name|G_FILE_TEST_IS_DIR
argument_list|)
expr_stmt|;
if|if
condition|(
name|migrate
condition|)
block|{
ifdef|#
directive|ifdef
name|GIMP_UNSTABLE
name|g_printerr
argument_list|(
literal|"gimp-user-install: migrating from %s\n"
argument_list|,
name|dir
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|install
operator|->
name|old_major
operator|=
literal|2
expr_stmt|;
name|install
operator|->
name|old_minor
operator|=
name|i
expr_stmt|;
break|break;
block|}
block|}
block|}
if|if
condition|(
name|migrate
condition|)
block|{
name|install
operator|->
name|old_dir
operator|=
name|dir
expr_stmt|;
name|install
operator|->
name|migrate
operator|=
operator|(
specifier|const
name|gchar
operator|*
operator|)
name|version
expr_stmt|;
block|}
else|else
block|{
name|g_free
argument_list|(
name|dir
argument_list|)
expr_stmt|;
block|}
return|return
name|migrate
return|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|user_install_old_style_gimpdir (void)
name|user_install_old_style_gimpdir
parameter_list|(
name|void
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|home_dir
init|=
name|g_get_home_dir
argument_list|()
decl_stmt|;
name|gchar
modifier|*
name|gimp_dir
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|home_dir
condition|)
block|{
name|gimp_dir
operator|=
name|g_build_filename
argument_list|(
name|home_dir
argument_list|,
literal|".gimp-"
name|GIMP_APP_VERSION
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gchar
modifier|*
name|user_name
init|=
name|g_strdup
argument_list|(
name|g_get_user_name
argument_list|()
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|subdir_name
decl_stmt|;
ifdef|#
directive|ifdef
name|G_OS_WIN32
name|gchar
modifier|*
name|p
init|=
name|user_name
decl_stmt|;
while|while
condition|(
operator|*
name|p
condition|)
block|{
comment|/* Replace funny characters in the user name with an            * underscore. The code below also replaces some            * characters that in fact are legal in file names, but            * who cares, as long as the definitely illegal ones are            * caught.            */
if|if
condition|(
operator|!
name|g_ascii_isalnum
argument_list|(
operator|*
name|p
argument_list|)
operator|&&
operator|!
name|strchr
argument_list|(
literal|"-.,@="
argument_list|,
operator|*
name|p
argument_list|)
condition|)
operator|*
name|p
operator|=
literal|'_'
expr_stmt|;
name|p
operator|++
expr_stmt|;
block|}
endif|#
directive|endif
ifndef|#
directive|ifndef
name|G_OS_WIN32
name|g_message
argument_list|(
literal|"warning: no home directory."
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|subdir_name
operator|=
name|g_strconcat
argument_list|(
literal|".gimp-"
name|GIMP_APP_VERSION
literal|"."
argument_list|,
name|user_name
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_dir
operator|=
name|g_build_filename
argument_list|(
name|gimp_data_directory
argument_list|()
argument_list|,
name|subdir_name
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|user_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|subdir_name
argument_list|)
expr_stmt|;
block|}
return|return
name|gimp_dir
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|user_install_log (GimpUserInstall * install,const gchar * format,...)
name|user_install_log
parameter_list|(
name|GimpUserInstall
modifier|*
name|install
parameter_list|,
specifier|const
name|gchar
modifier|*
name|format
parameter_list|,
modifier|...
parameter_list|)
block|{
name|va_list
name|args
decl_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|format
argument_list|)
expr_stmt|;
if|if
condition|(
name|format
condition|)
block|{
name|gchar
modifier|*
name|message
init|=
name|g_strdup_vprintf
argument_list|(
name|format
argument_list|,
name|args
argument_list|)
decl_stmt|;
if|if
condition|(
name|install
operator|->
name|verbose
condition|)
name|g_print
argument_list|(
literal|"%s\n"
argument_list|,
name|message
argument_list|)
expr_stmt|;
if|if
condition|(
name|install
operator|->
name|log
condition|)
name|install
operator|->
name|log
argument_list|(
name|message
argument_list|,
name|FALSE
argument_list|,
name|install
operator|->
name|log_data
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|message
argument_list|)
expr_stmt|;
block|}
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|user_install_log_newline (GimpUserInstall * install)
name|user_install_log_newline
parameter_list|(
name|GimpUserInstall
modifier|*
name|install
parameter_list|)
block|{
if|if
condition|(
name|install
operator|->
name|verbose
condition|)
name|g_print
argument_list|(
literal|"\n"
argument_list|)
expr_stmt|;
if|if
condition|(
name|install
operator|->
name|log
condition|)
name|install
operator|->
name|log
argument_list|(
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|install
operator|->
name|log_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|user_install_log_error (GimpUserInstall * install,GError ** error)
name|user_install_log_error
parameter_list|(
name|GimpUserInstall
modifier|*
name|install
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
if|if
condition|(
name|error
operator|&&
operator|*
name|error
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|message
init|=
operator|(
operator|(
operator|*
name|error
operator|)
operator|->
name|message
condition|?
operator|(
operator|*
name|error
operator|)
operator|->
name|message
else|:
literal|"(unknown error)"
operator|)
decl_stmt|;
if|if
condition|(
name|install
operator|->
name|log
condition|)
name|install
operator|->
name|log
argument_list|(
name|message
argument_list|,
name|TRUE
argument_list|,
name|install
operator|->
name|log_data
argument_list|)
expr_stmt|;
else|else
name|g_print
argument_list|(
literal|"error: %s\n"
argument_list|,
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
name|error
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|user_install_file_copy (GimpUserInstall * install,const gchar * source,const gchar * dest,const gchar * old_options_regexp,GRegexEvalCallback update_callback)
name|user_install_file_copy
parameter_list|(
name|GimpUserInstall
modifier|*
name|install
parameter_list|,
specifier|const
name|gchar
modifier|*
name|source
parameter_list|,
specifier|const
name|gchar
modifier|*
name|dest
parameter_list|,
specifier|const
name|gchar
modifier|*
name|old_options_regexp
parameter_list|,
name|GRegexEvalCallback
name|update_callback
parameter_list|)
block|{
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|gboolean
name|success
decl_stmt|;
name|user_install_log
argument_list|(
name|install
argument_list|,
name|_
argument_list|(
literal|"Copying file '%s' from '%s'..."
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|dest
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|source
argument_list|)
argument_list|)
expr_stmt|;
name|success
operator|=
name|gimp_config_file_copy
argument_list|(
name|source
argument_list|,
name|dest
argument_list|,
name|old_options_regexp
argument_list|,
name|update_callback
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
name|user_install_log_error
argument_list|(
name|install
argument_list|,
operator|&
name|error
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
DECL|function|user_install_mkdir (GimpUserInstall * install,const gchar * dirname)
name|user_install_mkdir
parameter_list|(
name|GimpUserInstall
modifier|*
name|install
parameter_list|,
specifier|const
name|gchar
modifier|*
name|dirname
parameter_list|)
block|{
name|user_install_log
argument_list|(
name|install
argument_list|,
name|_
argument_list|(
literal|"Creating folder '%s'..."
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|dirname
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_mkdir
argument_list|(
name|dirname
argument_list|,
name|S_IRUSR
operator||
name|S_IWUSR
operator||
name|S_IXUSR
operator||
name|S_IRGRP
operator||
name|S_IXGRP
operator||
name|S_IROTH
operator||
name|S_IXOTH
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|g_set_error
argument_list|(
operator|&
name|error
argument_list|,
name|G_FILE_ERROR
argument_list|,
name|g_file_error_from_errno
argument_list|(
name|errno
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Cannot create folder '%s': %s"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|dirname
argument_list|)
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
name|user_install_log_error
argument_list|(
name|install
argument_list|,
operator|&
name|error
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

begin_function
specifier|static
name|gboolean
DECL|function|user_install_mkdir_with_parents (GimpUserInstall * install,const gchar * dirname)
name|user_install_mkdir_with_parents
parameter_list|(
name|GimpUserInstall
modifier|*
name|install
parameter_list|,
specifier|const
name|gchar
modifier|*
name|dirname
parameter_list|)
block|{
name|user_install_log
argument_list|(
name|install
argument_list|,
name|_
argument_list|(
literal|"Creating folder '%s'..."
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|dirname
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_mkdir_with_parents
argument_list|(
name|dirname
argument_list|,
name|S_IRUSR
operator||
name|S_IWUSR
operator||
name|S_IXUSR
operator||
name|S_IRGRP
operator||
name|S_IXGRP
operator||
name|S_IROTH
operator||
name|S_IXOTH
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|g_set_error
argument_list|(
operator|&
name|error
argument_list|,
name|G_FILE_ERROR
argument_list|,
name|g_file_error_from_errno
argument_list|(
name|errno
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Cannot create folder '%s': %s"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|dirname
argument_list|)
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
name|user_install_log_error
argument_list|(
name|install
argument_list|,
operator|&
name|error
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
comment|/* The regexp pattern of all options changed from previous menurc.  * Add any pattern that we want to recognize for replacement in the menurc of  * the next release*/
end_comment

begin_define
DECL|macro|MENURC_OVER20_UPDATE_PATTERN
define|#
directive|define
name|MENURC_OVER20_UPDATE_PATTERN
value|"NOMATCH^"
end_define

begin_comment
comment|/**  * callback to use for updating any change value in the menurc.  * data is unused (always NULL).  * The updated value will be matched line by line.  */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|user_update_menurc_over20 (const GMatchInfo * matched_value,GString * new_value,gpointer data)
name|user_update_menurc_over20
parameter_list|(
specifier|const
name|GMatchInfo
modifier|*
name|matched_value
parameter_list|,
name|GString
modifier|*
name|new_value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gchar
modifier|*
name|match
decl_stmt|;
name|match
operator|=
name|g_match_info_fetch
argument_list|(
name|matched_value
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/* This is an example of how to use it.    * If view-close were to be renamed to file-close for instance, we'd add:    if (strcmp (match, "\"<Actions>/view/view-close\"") == 0)     g_string_append (new_value, "\"<Actions>/file/file-close\"");   else   */
comment|/* Should not happen. Just in case we match something unexpected by mistake. */
name|g_string_append
argument_list|(
name|new_value
argument_list|,
name|match
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|match
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|user_install_dir_copy (GimpUserInstall * install,const gchar * source,const gchar * base)
name|user_install_dir_copy
parameter_list|(
name|GimpUserInstall
modifier|*
name|install
parameter_list|,
specifier|const
name|gchar
modifier|*
name|source
parameter_list|,
specifier|const
name|gchar
modifier|*
name|base
parameter_list|)
block|{
name|GDir
modifier|*
name|source_dir
init|=
name|NULL
decl_stmt|;
name|GDir
modifier|*
name|dest_dir
init|=
name|NULL
decl_stmt|;
name|gchar
name|dest
index|[
literal|1024
index|]
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|basename
decl_stmt|;
name|gchar
modifier|*
name|dirname
decl_stmt|;
name|gboolean
name|success
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
block|{
name|gchar
modifier|*
name|basename
init|=
name|g_path_get_basename
argument_list|(
name|source
argument_list|)
decl_stmt|;
name|dirname
operator|=
name|g_build_filename
argument_list|(
name|base
argument_list|,
name|basename
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|basename
argument_list|)
expr_stmt|;
block|}
name|success
operator|=
name|user_install_mkdir
argument_list|(
name|install
argument_list|,
name|dirname
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|success
condition|)
goto|goto
name|error
goto|;
name|success
operator|=
operator|(
name|dest_dir
operator|=
name|g_dir_open
argument_list|(
name|dirname
argument_list|,
literal|0
argument_list|,
operator|&
name|error
argument_list|)
operator|)
operator|!=
name|NULL
expr_stmt|;
if|if
condition|(
operator|!
name|success
condition|)
goto|goto
name|error
goto|;
name|success
operator|=
operator|(
name|source_dir
operator|=
name|g_dir_open
argument_list|(
name|source
argument_list|,
literal|0
argument_list|,
operator|&
name|error
argument_list|)
operator|)
operator|!=
name|NULL
expr_stmt|;
if|if
condition|(
operator|!
name|success
condition|)
goto|goto
name|error
goto|;
while|while
condition|(
operator|(
name|basename
operator|=
name|g_dir_read_name
argument_list|(
name|source_dir
argument_list|)
operator|)
operator|!=
name|NULL
condition|)
block|{
name|gchar
modifier|*
name|name
init|=
name|g_build_filename
argument_list|(
name|source
argument_list|,
name|basename
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
if|if
condition|(
name|g_file_test
argument_list|(
name|name
argument_list|,
name|G_FILE_TEST_IS_REGULAR
argument_list|)
condition|)
block|{
name|g_snprintf
argument_list|(
name|dest
argument_list|,
sizeof|sizeof
argument_list|(
name|dest
argument_list|)
argument_list|,
literal|"%s%c%s"
argument_list|,
name|dirname
argument_list|,
name|G_DIR_SEPARATOR
argument_list|,
name|basename
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|user_install_file_copy
argument_list|(
name|install
argument_list|,
name|name
argument_list|,
name|dest
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
goto|goto
name|error
goto|;
block|}
block|}
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
block|}
name|error
label|:
name|user_install_log_error
argument_list|(
name|install
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|source_dir
condition|)
name|g_dir_close
argument_list|(
name|source_dir
argument_list|)
expr_stmt|;
if|if
condition|(
name|dest_dir
condition|)
name|g_dir_close
argument_list|(
name|dest_dir
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|dirname
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
DECL|function|user_install_create_files (GimpUserInstall * install)
name|user_install_create_files
parameter_list|(
name|GimpUserInstall
modifier|*
name|install
parameter_list|)
block|{
name|gchar
name|dest
index|[
literal|1024
index|]
decl_stmt|;
name|gchar
name|source
index|[
literal|1024
index|]
decl_stmt|;
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|G_N_ELEMENTS
argument_list|(
name|gimp_user_install_items
argument_list|)
condition|;
name|i
operator|++
control|)
block|{
name|g_snprintf
argument_list|(
name|dest
argument_list|,
sizeof|sizeof
argument_list|(
name|dest
argument_list|)
argument_list|,
literal|"%s%c%s"
argument_list|,
name|gimp_directory
argument_list|()
argument_list|,
name|G_DIR_SEPARATOR
argument_list|,
name|gimp_user_install_items
index|[
name|i
index|]
operator|.
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_file_test
argument_list|(
name|dest
argument_list|,
name|G_FILE_TEST_EXISTS
argument_list|)
condition|)
continue|continue;
switch|switch
condition|(
name|gimp_user_install_items
index|[
name|i
index|]
operator|.
name|action
condition|)
block|{
case|case
name|USER_INSTALL_MKDIR
case|:
if|if
condition|(
operator|!
name|user_install_mkdir
argument_list|(
name|install
argument_list|,
name|dest
argument_list|)
condition|)
return|return
name|FALSE
return|;
break|break;
case|case
name|USER_INSTALL_COPY
case|:
name|g_snprintf
argument_list|(
name|source
argument_list|,
sizeof|sizeof
argument_list|(
name|source
argument_list|)
argument_list|,
literal|"%s%c%s"
argument_list|,
name|gimp_sysconf_directory
argument_list|()
argument_list|,
name|G_DIR_SEPARATOR
argument_list|,
name|gimp_user_install_items
index|[
name|i
index|]
operator|.
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|user_install_file_copy
argument_list|(
name|install
argument_list|,
name|source
argument_list|,
name|dest
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
condition|)
return|return
name|FALSE
return|;
break|break;
block|}
block|}
name|g_snprintf
argument_list|(
name|dest
argument_list|,
sizeof|sizeof
argument_list|(
name|dest
argument_list|)
argument_list|,
literal|"%s%c%s"
argument_list|,
name|gimp_directory
argument_list|()
argument_list|,
name|G_DIR_SEPARATOR
argument_list|,
literal|"tags.xml"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|g_file_test
argument_list|(
name|dest
argument_list|,
name|G_FILE_TEST_IS_REGULAR
argument_list|)
condition|)
block|{
comment|/* if there was no tags.xml, install it with default tag set.        */
if|if
condition|(
operator|!
name|gimp_tags_user_install
argument_list|()
condition|)
block|{
return|return
name|FALSE
return|;
block|}
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|user_install_migrate_files (GimpUserInstall * install)
name|user_install_migrate_files
parameter_list|(
name|GimpUserInstall
modifier|*
name|install
parameter_list|)
block|{
name|GDir
modifier|*
name|dir
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|basename
decl_stmt|;
name|gchar
name|dest
index|[
literal|1024
index|]
decl_stmt|;
name|GimpRc
modifier|*
name|gimprc
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|dir
operator|=
name|g_dir_open
argument_list|(
name|install
operator|->
name|old_dir
argument_list|,
literal|0
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|dir
condition|)
block|{
name|user_install_log_error
argument_list|(
name|install
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
while|while
condition|(
operator|(
name|basename
operator|=
name|g_dir_read_name
argument_list|(
name|dir
argument_list|)
operator|)
operator|!=
name|NULL
condition|)
block|{
name|gchar
modifier|*
name|source
init|=
name|g_build_filename
argument_list|(
name|install
operator|->
name|old_dir
argument_list|,
name|basename
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|update_pattern
init|=
name|NULL
decl_stmt|;
name|GRegexEvalCallback
name|update_callback
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|g_file_test
argument_list|(
name|source
argument_list|,
name|G_FILE_TEST_IS_REGULAR
argument_list|)
condition|)
block|{
comment|/*  skip these files for all old versions  */
if|if
condition|(
name|strcmp
argument_list|(
name|basename
argument_list|,
literal|"documents"
argument_list|)
operator|==
literal|0
operator|||
name|g_str_has_prefix
argument_list|(
name|basename
argument_list|,
literal|"gimpswap."
argument_list|)
operator|||
name|strcmp
argument_list|(
name|basename
argument_list|,
literal|"pluginrc"
argument_list|)
operator|==
literal|0
operator|||
name|strcmp
argument_list|(
name|basename
argument_list|,
literal|"themerc"
argument_list|)
operator|==
literal|0
operator|||
name|strcmp
argument_list|(
name|basename
argument_list|,
literal|"toolrc"
argument_list|)
operator|==
literal|0
condition|)
block|{
goto|goto
name|next_file
goto|;
block|}
if|if
condition|(
name|strcmp
argument_list|(
name|basename
argument_list|,
literal|"menurc"
argument_list|)
operator|==
literal|0
condition|)
block|{
comment|/*  skip menurc for gimp 2.0 as the format has changed  */
if|if
condition|(
name|install
operator|->
name|old_minor
operator|==
literal|0
condition|)
goto|goto
name|next_file
goto|;
name|update_pattern
operator|=
name|MENURC_OVER20_UPDATE_PATTERN
expr_stmt|;
name|update_callback
operator|=
name|user_update_menurc_over20
expr_stmt|;
block|}
name|g_snprintf
argument_list|(
name|dest
argument_list|,
sizeof|sizeof
argument_list|(
name|dest
argument_list|)
argument_list|,
literal|"%s%c%s"
argument_list|,
name|gimp_directory
argument_list|()
argument_list|,
name|G_DIR_SEPARATOR
argument_list|,
name|basename
argument_list|)
expr_stmt|;
name|user_install_file_copy
argument_list|(
name|install
argument_list|,
name|source
argument_list|,
name|dest
argument_list|,
name|update_pattern
argument_list|,
name|update_callback
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|g_file_test
argument_list|(
name|source
argument_list|,
name|G_FILE_TEST_IS_DIR
argument_list|)
condition|)
block|{
comment|/*  skip these directories for all old versions  */
if|if
condition|(
name|strcmp
argument_list|(
name|basename
argument_list|,
literal|"tmp"
argument_list|)
operator|==
literal|0
operator|||
name|strcmp
argument_list|(
name|basename
argument_list|,
literal|"tool-options"
argument_list|)
operator|==
literal|0
condition|)
block|{
goto|goto
name|next_file
goto|;
block|}
name|user_install_dir_copy
argument_list|(
name|install
argument_list|,
name|source
argument_list|,
name|gimp_directory
argument_list|()
argument_list|)
expr_stmt|;
block|}
name|next_file
label|:
name|g_free
argument_list|(
name|source
argument_list|)
expr_stmt|;
block|}
comment|/*  create the tmp directory that was explicitly not copied  */
name|g_snprintf
argument_list|(
name|dest
argument_list|,
sizeof|sizeof
argument_list|(
name|dest
argument_list|)
argument_list|,
literal|"%s%c%s"
argument_list|,
name|gimp_directory
argument_list|()
argument_list|,
name|G_DIR_SEPARATOR
argument_list|,
literal|"tmp"
argument_list|)
expr_stmt|;
name|user_install_mkdir
argument_list|(
name|install
argument_list|,
name|dest
argument_list|)
expr_stmt|;
name|g_dir_close
argument_list|(
name|dir
argument_list|)
expr_stmt|;
name|gimp_templates_migrate
argument_list|(
name|install
operator|->
name|old_dir
argument_list|)
expr_stmt|;
name|gimprc
operator|=
name|gimp_rc_new
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_rc_migrate
argument_list|(
name|gimprc
argument_list|)
expr_stmt|;
name|gimp_rc_save
argument_list|(
name|gimprc
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|gimprc
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

end_unit

