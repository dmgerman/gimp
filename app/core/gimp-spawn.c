begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimp-spawn.c  * Copyright (C) 2018 Ell  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_VFORK
end_ifdef

begin_include
include|#
directive|include
file|<sys/types.h>
end_include

begin_include
include|#
directive|include
file|<sys/wait.h>
end_include

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_include
include|#
directive|include
file|<errno.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_FCNTL_H
end_ifdef

begin_include
include|#
directive|include
file|<fcntl.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

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

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimp-spawn.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_VFORK
end_ifdef

begin_comment
comment|/* copied from glib */
end_comment

begin_function
specifier|static
name|gint
DECL|function|exec_err_to_g_error (gint en)
name|exec_err_to_g_error
parameter_list|(
name|gint
name|en
parameter_list|)
block|{
switch|switch
condition|(
name|en
condition|)
block|{
ifdef|#
directive|ifdef
name|EACCES
case|case
name|EACCES
case|:
return|return
name|G_SPAWN_ERROR_ACCES
return|;
break|break;
endif|#
directive|endif
ifdef|#
directive|ifdef
name|EPERM
case|case
name|EPERM
case|:
return|return
name|G_SPAWN_ERROR_PERM
return|;
break|break;
endif|#
directive|endif
ifdef|#
directive|ifdef
name|E2BIG
case|case
name|E2BIG
case|:
return|return
name|G_SPAWN_ERROR_TOO_BIG
return|;
break|break;
endif|#
directive|endif
ifdef|#
directive|ifdef
name|ENOEXEC
case|case
name|ENOEXEC
case|:
return|return
name|G_SPAWN_ERROR_NOEXEC
return|;
break|break;
endif|#
directive|endif
ifdef|#
directive|ifdef
name|ENAMETOOLONG
case|case
name|ENAMETOOLONG
case|:
return|return
name|G_SPAWN_ERROR_NAMETOOLONG
return|;
break|break;
endif|#
directive|endif
ifdef|#
directive|ifdef
name|ENOENT
case|case
name|ENOENT
case|:
return|return
name|G_SPAWN_ERROR_NOENT
return|;
break|break;
endif|#
directive|endif
ifdef|#
directive|ifdef
name|ENOMEM
case|case
name|ENOMEM
case|:
return|return
name|G_SPAWN_ERROR_NOMEM
return|;
break|break;
endif|#
directive|endif
ifdef|#
directive|ifdef
name|ENOTDIR
case|case
name|ENOTDIR
case|:
return|return
name|G_SPAWN_ERROR_NOTDIR
return|;
break|break;
endif|#
directive|endif
ifdef|#
directive|ifdef
name|ELOOP
case|case
name|ELOOP
case|:
return|return
name|G_SPAWN_ERROR_LOOP
return|;
break|break;
endif|#
directive|endif
ifdef|#
directive|ifdef
name|ETXTBUSY
case|case
name|ETXTBUSY
case|:
return|return
name|G_SPAWN_ERROR_TXTBUSY
return|;
break|break;
endif|#
directive|endif
ifdef|#
directive|ifdef
name|EIO
case|case
name|EIO
case|:
return|return
name|G_SPAWN_ERROR_IO
return|;
break|break;
endif|#
directive|endif
ifdef|#
directive|ifdef
name|ENFILE
case|case
name|ENFILE
case|:
return|return
name|G_SPAWN_ERROR_NFILE
return|;
break|break;
endif|#
directive|endif
ifdef|#
directive|ifdef
name|EMFILE
case|case
name|EMFILE
case|:
return|return
name|G_SPAWN_ERROR_MFILE
return|;
break|break;
endif|#
directive|endif
ifdef|#
directive|ifdef
name|EINVAL
case|case
name|EINVAL
case|:
return|return
name|G_SPAWN_ERROR_INVAL
return|;
break|break;
endif|#
directive|endif
ifdef|#
directive|ifdef
name|EISDIR
case|case
name|EISDIR
case|:
return|return
name|G_SPAWN_ERROR_ISDIR
return|;
break|break;
endif|#
directive|endif
ifdef|#
directive|ifdef
name|ELIBBAD
case|case
name|ELIBBAD
case|:
return|return
name|G_SPAWN_ERROR_LIBBAD
return|;
break|break;
endif|#
directive|endif
default|default:
return|return
name|G_SPAWN_ERROR_FAILED
return|;
break|break;
block|}
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* HAVE_VFORK */
end_comment

begin_function
name|gboolean
DECL|function|gimp_spawn_async (gchar ** argv,gchar ** envp,GSpawnFlags flags,GPid * child_pid,GError ** error)
name|gimp_spawn_async
parameter_list|(
name|gchar
modifier|*
modifier|*
name|argv
parameter_list|,
name|gchar
modifier|*
modifier|*
name|envp
parameter_list|,
name|GSpawnFlags
name|flags
parameter_list|,
name|GPid
modifier|*
name|child_pid
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|argv
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|HAVE_VFORK
if|if
condition|(
name|flags
operator|==
operator|(
name|G_SPAWN_LEAVE_DESCRIPTORS_OPEN
operator||
name|G_SPAWN_DO_NOT_REAP_CHILD
operator||
name|G_SPAWN_CHILD_INHERITS_STDIN
operator|)
condition|)
block|{
name|pid_t
name|pid
decl_stmt|;
name|pid
operator|=
name|vfork
argument_list|()
expr_stmt|;
if|if
condition|(
name|pid
operator|<
literal|0
condition|)
block|{
name|gint
name|errsv
init|=
name|errno
decl_stmt|;
name|g_set_error
argument_list|(
name|error
argument_list|,
name|G_SPAWN_ERROR
argument_list|,
name|G_SPAWN_ERROR_FORK
argument_list|,
name|_
argument_list|(
literal|"Failed to fork (%s)"
argument_list|)
argument_list|,
name|g_strerror
argument_list|(
name|errsv
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
elseif|else
if|if
condition|(
name|pid
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|envp
condition|)
name|execve
argument_list|(
name|argv
index|[
literal|0
index|]
argument_list|,
name|argv
argument_list|,
name|envp
argument_list|)
expr_stmt|;
else|else
name|execv
argument_list|(
name|argv
index|[
literal|0
index|]
argument_list|,
name|argv
argument_list|)
expr_stmt|;
name|_exit
argument_list|(
name|errno
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|int
name|status
init|=
operator|-
literal|1
decl_stmt|;
name|pid_t
name|result
decl_stmt|;
name|result
operator|=
name|waitpid
argument_list|(
name|pid
argument_list|,
operator|&
name|status
argument_list|,
name|WNOHANG
argument_list|)
expr_stmt|;
if|if
condition|(
name|result
condition|)
block|{
if|if
condition|(
name|result
operator|<
literal|0
condition|)
block|{
name|g_warning
argument_list|(
literal|"waitpid() should not fail in "
literal|"gimp_spawn_async()"
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|WIFEXITED
argument_list|(
name|status
argument_list|)
condition|)
name|status
operator|=
name|WEXITSTATUS
argument_list|(
name|status
argument_list|)
expr_stmt|;
else|else
name|status
operator|=
operator|-
literal|1
expr_stmt|;
name|g_set_error
argument_list|(
name|error
argument_list|,
name|G_SPAWN_ERROR
argument_list|,
name|exec_err_to_g_error
argument_list|(
name|status
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Failed to execute child process â%sâ (%s)"
argument_list|)
argument_list|,
name|argv
index|[
literal|0
index|]
argument_list|,
name|g_strerror
argument_list|(
name|status
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
if|if
condition|(
name|child_pid
condition|)
operator|*
name|child_pid
operator|=
name|pid
expr_stmt|;
return|return
name|TRUE
return|;
block|}
block|}
endif|#
directive|endif
comment|/* HAVE_VFORK */
return|return
name|g_spawn_async
argument_list|(
name|NULL
argument_list|,
name|argv
argument_list|,
name|envp
argument_list|,
name|flags
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|child_pid
argument_list|,
name|error
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_spawn_set_cloexec (gint fd)
name|gimp_spawn_set_cloexec
parameter_list|(
name|gint
name|fd
parameter_list|)
block|{
if|#
directive|if
name|defined
argument_list|(
name|G_OS_WIN32
argument_list|)
name|SetHandleInformation
argument_list|(
operator|(
name|HANDLE
operator|)
name|_get_osfhandle
argument_list|(
name|fd
argument_list|)
argument_list|,
name|HANDLE_FLAG_INHERIT
argument_list|,
literal|0
argument_list|)
expr_stmt|;
elif|#
directive|elif
name|defined
argument_list|(
name|HAVE_FCNTL_H
argument_list|)
name|fcntl
argument_list|(
name|fd
argument_list|,
name|F_SETFD
argument_list|,
name|fcntl
argument_list|(
name|fd
argument_list|,
name|F_GETFD
argument_list|,
literal|0
argument_list|)
operator||
name|FD_CLOEXEC
argument_list|)
expr_stmt|;
elif|#
directive|elif
name|defined
argument_list|(
name|__GNUC__
argument_list|)
warning|#
directive|warning
warning|gimp_spawn_set_cloexec() is not implemented for the target platform
endif|#
directive|endif
block|}
end_function

end_unit

