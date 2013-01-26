begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * File Utitility functions for GimpConfig.  * Copyright (C) 2001-2003  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<sys/types.h>
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|<glib/gstdio.h>
end_include

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

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_include
include|#
directive|include
file|"libgimpbase/gimpwin32-io.h"
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"config-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-file.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
name|gboolean
DECL|function|gimp_config_file_copy (const gchar * source,const gchar * dest,const gchar * old_options_pattern,GRegexEvalCallback update_callback,GError ** error)
name|gimp_config_file_copy
parameter_list|(
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
name|old_options_pattern
parameter_list|,
name|GRegexEvalCallback
name|update_callback
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gchar
name|buffer
index|[
literal|8192
index|]
decl_stmt|;
name|FILE
modifier|*
name|sfile
decl_stmt|;
name|FILE
modifier|*
name|dfile
decl_stmt|;
name|struct
name|stat
name|stat_buf
decl_stmt|;
name|gint
name|nbytes
decl_stmt|;
name|gint
name|unwritten_len
init|=
literal|0
decl_stmt|;
name|GRegex
modifier|*
name|old_options_regexp
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|old_options_pattern
operator|&&
name|update_callback
condition|)
block|{
name|old_options_regexp
operator|=
name|g_regex_new
argument_list|(
name|old_options_pattern
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|error
argument_list|)
expr_stmt|;
comment|/* error set by g_regex_new. */
if|if
condition|(
operator|!
name|old_options_regexp
condition|)
return|return
name|FALSE
return|;
block|}
name|sfile
operator|=
name|g_fopen
argument_list|(
name|source
argument_list|,
literal|"rb"
argument_list|)
expr_stmt|;
if|if
condition|(
name|sfile
operator|==
name|NULL
condition|)
block|{
name|g_set_error
argument_list|(
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
literal|"Could not open '%s' for reading: %s"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|source
argument_list|)
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|old_options_regexp
condition|)
name|g_regex_unref
argument_list|(
name|old_options_regexp
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|dfile
operator|=
name|g_fopen
argument_list|(
name|dest
argument_list|,
literal|"wb"
argument_list|)
expr_stmt|;
if|if
condition|(
name|dfile
operator|==
name|NULL
condition|)
block|{
name|g_set_error
argument_list|(
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
literal|"Could not open '%s' for writing: %s"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|dest
argument_list|)
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|sfile
argument_list|)
expr_stmt|;
if|if
condition|(
name|old_options_regexp
condition|)
name|g_regex_unref
argument_list|(
name|old_options_regexp
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
while|while
condition|(
operator|(
name|nbytes
operator|=
name|fread
argument_list|(
name|buffer
operator|+
name|unwritten_len
argument_list|,
literal|1
argument_list|,
sizeof|sizeof
argument_list|(
name|buffer
argument_list|)
operator|-
name|unwritten_len
argument_list|,
name|sfile
argument_list|)
operator|)
operator|>
literal|0
operator|||
name|unwritten_len
condition|)
block|{
name|size_t
name|read_len
init|=
name|nbytes
operator|+
name|unwritten_len
decl_stmt|;
name|size_t
name|write_len
decl_stmt|;
name|gchar
modifier|*
name|eol
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|write_bytes
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|old_options_regexp
operator|&&
name|update_callback
condition|)
block|{
name|eol
operator|=
name|g_strrstr_len
argument_list|(
name|buffer
argument_list|,
name|read_len
argument_list|,
literal|"\n"
argument_list|)
expr_stmt|;
if|if
condition|(
name|eol
condition|)
block|{
operator|*
name|eol
operator|=
literal|'\0'
expr_stmt|;
name|read_len
operator|=
name|strlen
argument_list|(
name|buffer
argument_list|)
operator|+
literal|1
expr_stmt|;
operator|*
name|eol
operator|++
operator|=
literal|'\n'
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|feof
argument_list|(
name|sfile
argument_list|)
condition|)
block|{
comment|/* We are in unlikely case where a single config line is                * longer than the buffer!                */
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_CONFIG_ERROR
argument_list|,
name|GIMP_CONFIG_ERROR_PARSE
argument_list|,
name|_
argument_list|(
literal|"Error parsing '%s': line longer than %"
name|G_GINT64_FORMAT
literal|" characters."
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|source
argument_list|)
argument_list|,
operator|(
name|gint64
operator|)
sizeof|sizeof
argument_list|(
name|buffer
argument_list|)
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|sfile
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|dfile
argument_list|)
expr_stmt|;
name|g_regex_unref
argument_list|(
name|old_options_regexp
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|write_bytes
operator|=
name|g_regex_replace_eval
argument_list|(
name|old_options_regexp
argument_list|,
name|buffer
argument_list|,
name|read_len
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|update_callback
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|write_bytes
operator|==
name|NULL
condition|)
block|{
comment|/* error already set. */
name|fclose
argument_list|(
name|sfile
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|dfile
argument_list|)
expr_stmt|;
name|g_regex_unref
argument_list|(
name|old_options_regexp
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|write_len
operator|=
name|strlen
argument_list|(
name|write_bytes
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|write_bytes
operator|=
name|buffer
expr_stmt|;
name|write_len
operator|=
name|read_len
expr_stmt|;
block|}
if|if
condition|(
name|fwrite
argument_list|(
name|write_bytes
argument_list|,
literal|1
argument_list|,
name|write_len
argument_list|,
name|dfile
argument_list|)
operator|<
name|write_len
condition|)
block|{
name|g_set_error
argument_list|(
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
literal|"Error writing '%s': %s"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|dest
argument_list|)
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|old_options_regexp
operator|&&
name|update_callback
condition|)
block|{
name|g_free
argument_list|(
name|write_bytes
argument_list|)
expr_stmt|;
name|g_regex_unref
argument_list|(
name|old_options_regexp
argument_list|)
expr_stmt|;
block|}
name|fclose
argument_list|(
name|sfile
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|dfile
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
if|if
condition|(
name|old_options_regexp
operator|&&
name|update_callback
condition|)
block|{
name|g_free
argument_list|(
name|write_bytes
argument_list|)
expr_stmt|;
if|if
condition|(
name|eol
condition|)
block|{
name|unwritten_len
operator|=
name|nbytes
operator|+
name|unwritten_len
operator|-
name|read_len
expr_stmt|;
name|memmove
argument_list|(
name|buffer
argument_list|,
name|eol
argument_list|,
name|unwritten_len
argument_list|)
expr_stmt|;
block|}
else|else
comment|/* EOF */
break|break;
block|}
block|}
if|if
condition|(
name|ferror
argument_list|(
name|sfile
argument_list|)
condition|)
block|{
name|g_set_error
argument_list|(
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
literal|"Error reading '%s': %s"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|source
argument_list|)
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|sfile
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|dfile
argument_list|)
expr_stmt|;
if|if
condition|(
name|old_options_regexp
condition|)
name|g_regex_unref
argument_list|(
name|old_options_regexp
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|fclose
argument_list|(
name|sfile
argument_list|)
expr_stmt|;
if|if
condition|(
name|fclose
argument_list|(
name|dfile
argument_list|)
operator|==
name|EOF
condition|)
block|{
name|g_set_error
argument_list|(
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
literal|"Error writing '%s': %s"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|dest
argument_list|)
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|old_options_regexp
condition|)
name|g_regex_unref
argument_list|(
name|old_options_regexp
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
if|if
condition|(
name|g_stat
argument_list|(
name|source
argument_list|,
operator|&
name|stat_buf
argument_list|)
operator|==
literal|0
condition|)
block|{
name|g_chmod
argument_list|(
name|dest
argument_list|,
name|stat_buf
operator|.
name|st_mode
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|old_options_regexp
condition|)
name|g_regex_unref
argument_list|(
name|old_options_regexp
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_config_file_backup_on_error (const gchar * filename,const gchar * name,GError ** error)
name|gimp_config_file_backup_on_error
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gchar
modifier|*
name|backup
decl_stmt|;
name|gboolean
name|success
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|filename
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|name
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|backup
operator|=
name|g_strconcat
argument_list|(
name|filename
argument_list|,
literal|"~"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|success
operator|=
name|gimp_config_file_copy
argument_list|(
name|filename
argument_list|,
name|backup
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|g_message
argument_list|(
name|_
argument_list|(
literal|"There was an error parsing your '%s' file. "
literal|"Default values will be used. A backup of your "
literal|"configuration has been created at '%s'."
argument_list|)
argument_list|,
name|name
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|backup
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|backup
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

end_unit

