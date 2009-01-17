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
DECL|function|gimp_config_file_copy (const gchar * source,const gchar * dest,GError ** error)
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
argument_list|,
literal|1
argument_list|,
sizeof|sizeof
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|sfile
argument_list|)
operator|)
operator|>
literal|0
condition|)
block|{
if|if
condition|(
name|fwrite
argument_list|(
name|buffer
argument_list|,
literal|1
argument_list|,
name|nbytes
argument_list|,
name|dfile
argument_list|)
operator|<
name|nbytes
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

