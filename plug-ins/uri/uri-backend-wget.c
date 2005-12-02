begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* Author: Josh MacDonald. */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
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
file|<errno.h>
end_include

begin_include
include|#
directive|include
file|<sys/param.h>
end_include

begin_include
include|#
directive|include
file|<sys/wait.h>
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
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpui.h>
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_define
DECL|macro|TIMEOUT
define|#
directive|define
name|TIMEOUT
value|300
end_define

begin_define
DECL|macro|BUFSIZE
define|#
directive|define
name|BUFSIZE
value|1024
end_define

begin_function
name|gboolean
DECL|function|uri_backend_init (const gchar * plugin_name,gboolean run,GimpRunMode run_mode,GError ** error)
name|uri_backend_init
parameter_list|(
specifier|const
name|gchar
modifier|*
name|plugin_name
parameter_list|,
name|gboolean
name|run
parameter_list|,
name|GimpRunMode
name|run_mode
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|void
DECL|function|uri_backend_shutdown (void)
name|uri_backend_shutdown
parameter_list|(
name|void
parameter_list|)
block|{ }
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|uri_backend_get_load_protocols (void)
name|uri_backend_get_load_protocols
parameter_list|(
name|void
parameter_list|)
block|{
return|return
literal|"http:,https:,ftp:"
return|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|uri_backend_get_save_protocols (void)
name|uri_backend_get_save_protocols
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|uri_backend_load_image (const gchar * uri,const gchar * tmpname,GimpRunMode run_mode,GError ** error)
name|uri_backend_load_image
parameter_list|(
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tmpname
parameter_list|,
name|GimpRunMode
name|run_mode
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gint
name|pid
decl_stmt|;
name|gint
name|p
index|[
literal|2
index|]
decl_stmt|;
if|if
condition|(
name|pipe
argument_list|(
name|p
argument_list|)
operator|!=
literal|0
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|"pipe() failed: %s"
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
operator|(
name|pid
operator|=
name|fork
argument_list|()
operator|)
operator|<
literal|0
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|"fork() failed: %s"
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
elseif|else
if|if
condition|(
name|pid
operator|==
literal|0
condition|)
block|{
name|gchar
name|timeout_str
index|[
literal|16
index|]
decl_stmt|;
name|close
argument_list|(
name|p
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
name|close
argument_list|(
literal|2
argument_list|)
expr_stmt|;
name|dup
argument_list|(
name|p
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
name|close
argument_list|(
name|p
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|HAVE_PUTENV
comment|/* produce deterministic output */
name|putenv
argument_list|(
literal|"LANGUAGE=C"
argument_list|)
expr_stmt|;
name|putenv
argument_list|(
literal|"LC_ALL=C"
argument_list|)
expr_stmt|;
name|putenv
argument_list|(
literal|"LANG=C"
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|g_snprintf
argument_list|(
name|timeout_str
argument_list|,
sizeof|sizeof
argument_list|(
name|timeout_str
argument_list|)
argument_list|,
literal|"%d"
argument_list|,
name|TIMEOUT
argument_list|)
expr_stmt|;
name|execlp
argument_list|(
literal|"wget"
argument_list|,
literal|"wget"
argument_list|,
literal|"-v"
argument_list|,
literal|"-e"
argument_list|,
literal|"server-response=off"
argument_list|,
literal|"-T"
argument_list|,
name|timeout_str
argument_list|,
name|uri
argument_list|,
literal|"-O"
argument_list|,
name|tmpname
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_set_error
argument_list|(
name|error
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|"exec() failed: wget: %s"
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
name|_exit
argument_list|(
literal|127
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|FILE
modifier|*
name|input
decl_stmt|;
name|gchar
name|buf
index|[
name|BUFSIZE
index|]
decl_stmt|;
name|gboolean
name|seen_resolve
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|connected
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|redirect
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|file_found
init|=
name|FALSE
decl_stmt|;
name|gchar
name|sizestr
index|[
literal|37
index|]
decl_stmt|;
name|gchar
modifier|*
name|endptr
decl_stmt|;
name|guint64
name|size
init|=
literal|0
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|;
name|gchar
name|dot
decl_stmt|;
name|guint64
name|kilobytes
init|=
literal|0
decl_stmt|;
name|gboolean
name|finished
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|debug
init|=
name|FALSE
decl_stmt|;
name|gchar
modifier|*
name|memsize
decl_stmt|;
name|gchar
modifier|*
name|message
decl_stmt|;
name|gchar
modifier|*
name|timeout_msg
decl_stmt|;
DECL|macro|DEBUG (x)
define|#
directive|define
name|DEBUG
parameter_list|(
name|x
parameter_list|)
value|if (debug) g_printerr (x)
name|close
argument_list|(
name|p
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
name|input
operator|=
name|fdopen
argument_list|(
name|p
index|[
literal|0
index|]
argument_list|,
literal|"r"
argument_list|)
expr_stmt|;
comment|/*  hardcoded and not-really-foolproof scanning of wget putput  */
name|wget_begin
label|:
comment|/* Eat any Location lines */
if|if
condition|(
name|redirect
operator|&&
name|fgets
argument_list|(
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
name|input
argument_list|)
operator|==
name|NULL
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"wget exited abnormally on URI '%s'"
argument_list|)
argument_list|,
name|uri
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|redirect
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|fgets
argument_list|(
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
name|input
argument_list|)
operator|==
name|NULL
condition|)
block|{
comment|/*  no message here because failing on the first line means            *  that wget was not found            */
return|return
name|FALSE
return|;
block|}
name|DEBUG
argument_list|(
name|buf
argument_list|)
expr_stmt|;
comment|/*  The second line is the local copy of the file  */
if|if
condition|(
name|fgets
argument_list|(
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
name|input
argument_list|)
operator|==
name|NULL
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"wget exited abnormally on URI '%s'"
argument_list|)
argument_list|,
name|uri
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|DEBUG
argument_list|(
name|buf
argument_list|)
expr_stmt|;
comment|/*  The third line is "Connecting to..."  */
name|timeout_msg
operator|=
name|g_strdup_printf
argument_list|(
name|ngettext
argument_list|(
literal|"(timeout is %d second)"
argument_list|,
literal|"(timeout is %d seconds)"
argument_list|,
name|TIMEOUT
argument_list|)
argument_list|,
name|TIMEOUT
argument_list|)
expr_stmt|;
name|gimp_progress_init_printf
argument_list|(
literal|"%s %s"
argument_list|,
name|_
argument_list|(
literal|"Connecting to server"
argument_list|)
argument_list|,
name|timeout_msg
argument_list|)
expr_stmt|;
name|read_connect
label|:
if|if
condition|(
name|fgets
argument_list|(
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
name|input
argument_list|)
operator|==
name|NULL
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"wget exited abnormally on URI '%s'"
argument_list|)
argument_list|,
name|uri
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
elseif|else
if|if
condition|(
name|strstr
argument_list|(
name|buf
argument_list|,
literal|"connected"
argument_list|)
condition|)
block|{
name|connected
operator|=
name|TRUE
expr_stmt|;
block|}
comment|/* newer wgets have a "Resolving foo" line, so eat it */
elseif|else
if|if
condition|(
operator|!
name|seen_resolve
operator|&&
name|strstr
argument_list|(
name|buf
argument_list|,
literal|"Resolving"
argument_list|)
condition|)
block|{
name|seen_resolve
operator|=
name|TRUE
expr_stmt|;
goto|goto
name|read_connect
goto|;
block|}
name|DEBUG
argument_list|(
name|buf
argument_list|)
expr_stmt|;
comment|/*  The fourth line is either the network request or an error  */
name|gimp_progress_set_text_printf
argument_list|(
literal|"%s %s"
argument_list|,
name|_
argument_list|(
literal|"Opening URI"
argument_list|)
argument_list|,
name|timeout_msg
argument_list|)
expr_stmt|;
if|if
condition|(
name|fgets
argument_list|(
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
name|input
argument_list|)
operator|==
name|NULL
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"wget exited abnormally on URI '%s'"
argument_list|)
argument_list|,
name|uri
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
elseif|else
if|if
condition|(
operator|!
name|connected
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"A network error occurred: %s"
argument_list|)
argument_list|,
name|buf
argument_list|)
expr_stmt|;
name|DEBUG
argument_list|(
name|buf
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
elseif|else
if|if
condition|(
name|strstr
argument_list|(
name|buf
argument_list|,
literal|"302 Found"
argument_list|)
condition|)
block|{
name|DEBUG
argument_list|(
name|buf
argument_list|)
expr_stmt|;
name|connected
operator|=
name|FALSE
expr_stmt|;
name|seen_resolve
operator|=
name|FALSE
expr_stmt|;
name|redirect
operator|=
name|TRUE
expr_stmt|;
goto|goto
name|wget_begin
goto|;
block|}
name|DEBUG
argument_list|(
name|buf
argument_list|)
expr_stmt|;
comment|/*  The fifth line is either the length of the file or an error  */
if|if
condition|(
name|fgets
argument_list|(
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
name|input
argument_list|)
operator|==
name|NULL
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"wget exited abnormally on URI '%s'"
argument_list|)
argument_list|,
name|uri
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
elseif|else
if|if
condition|(
name|strstr
argument_list|(
name|buf
argument_list|,
literal|"Length"
argument_list|)
condition|)
block|{
name|file_found
operator|=
name|TRUE
expr_stmt|;
block|}
else|else
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"A network error occurred: %s"
argument_list|)
argument_list|,
name|buf
argument_list|)
expr_stmt|;
name|DEBUG
argument_list|(
name|buf
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|DEBUG
argument_list|(
name|buf
argument_list|)
expr_stmt|;
if|if
condition|(
name|sscanf
argument_list|(
name|buf
argument_list|,
literal|"Length: %37s"
argument_list|,
name|sizestr
argument_list|)
operator|!=
literal|1
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|"Could not parse wget's file length message"
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
comment|/*  strip away commas  */
for|for
control|(
name|i
operator|=
literal|0
operator|,
name|j
operator|=
literal|0
init|;
name|i
operator|<
sizeof|sizeof
argument_list|(
name|sizestr
argument_list|)
condition|;
name|i
operator|++
operator|,
name|j
operator|++
control|)
block|{
if|if
condition|(
name|sizestr
index|[
name|i
index|]
operator|==
literal|','
condition|)
name|i
operator|++
expr_stmt|;
name|sizestr
index|[
name|j
index|]
operator|=
name|sizestr
index|[
name|i
index|]
expr_stmt|;
if|if
condition|(
name|sizestr
index|[
name|j
index|]
operator|==
literal|'\0'
condition|)
break|break;
block|}
if|if
condition|(
operator|*
name|sizestr
operator|!=
literal|'\0'
condition|)
block|{
name|size
operator|=
name|g_ascii_strtoull
argument_list|(
name|sizestr
argument_list|,
operator|&
name|endptr
argument_list|,
literal|10
argument_list|)
expr_stmt|;
if|if
condition|(
operator|*
name|endptr
operator|!=
literal|'\0'
operator|||
name|size
operator|==
name|G_MAXUINT64
condition|)
name|size
operator|=
literal|0
expr_stmt|;
block|}
comment|/*  Start the actual download...  */
if|if
condition|(
name|size
operator|>
literal|0
condition|)
block|{
name|memsize
operator|=
name|gimp_memsize_to_string
argument_list|(
name|size
argument_list|)
expr_stmt|;
name|message
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Downloading %s of image data"
argument_list|)
argument_list|,
name|memsize
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|message
operator|=
name|g_strdup
argument_list|(
name|_
argument_list|(
literal|"Downloading unknown amount of image data"
argument_list|)
argument_list|)
expr_stmt|;
name|memsize
operator|=
name|NULL
expr_stmt|;
block|}
name|gimp_progress_set_text_printf
argument_list|(
literal|"%s %s"
argument_list|,
name|message
argument_list|,
name|timeout_msg
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|message
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|memsize
argument_list|)
expr_stmt|;
comment|/*  Switch to byte parsing wget's output...  */
while|while
condition|(
literal|1
condition|)
block|{
name|dot
operator|=
name|fgetc
argument_list|(
name|input
argument_list|)
expr_stmt|;
if|if
condition|(
name|feof
argument_list|(
name|input
argument_list|)
condition|)
break|break;
if|if
condition|(
name|debug
condition|)
block|{
name|fputc
argument_list|(
name|dot
argument_list|,
name|stderr
argument_list|)
expr_stmt|;
name|fflush
argument_list|(
name|stderr
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|dot
operator|==
literal|'.'
condition|)
comment|/* one kilobyte */
block|{
name|kilobytes
operator|++
expr_stmt|;
if|if
condition|(
name|size
operator|>
literal|0
condition|)
block|{
name|gimp_progress_update
argument_list|(
call|(
name|gdouble
call|)
argument_list|(
name|kilobytes
operator|*
literal|1024
argument_list|)
operator|/
operator|(
name|gdouble
operator|)
name|size
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|memsize
operator|=
name|gimp_memsize_to_string
argument_list|(
name|kilobytes
operator|*
literal|1024
argument_list|)
expr_stmt|;
name|gimp_progress_set_text_printf
argument_list|(
name|_
argument_list|(
literal|"Downloaded %s of image data"
argument_list|)
argument_list|,
name|memsize
argument_list|)
expr_stmt|;
name|gimp_progress_pulse
argument_list|()
expr_stmt|;
name|g_free
argument_list|(
name|memsize
argument_list|)
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|dot
operator|==
literal|':'
condition|)
comment|/* the time string contains a ':' */
block|{
name|fgets
argument_list|(
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
name|input
argument_list|)
expr_stmt|;
name|DEBUG
argument_list|(
name|buf
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|strstr
argument_list|(
name|buf
argument_list|,
literal|"error"
argument_list|)
condition|)
block|{
name|finished
operator|=
name|TRUE
expr_stmt|;
name|gimp_progress_update
argument_list|(
literal|1.0
argument_list|)
expr_stmt|;
block|}
break|break;
block|}
block|}
if|if
condition|(
operator|!
name|finished
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|"wget exited before finishing downloading URI\n'%s'"
argument_list|,
name|uri
argument_list|)
expr_stmt|;
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
name|gboolean
DECL|function|uri_backend_save_image (const gchar * uri,const gchar * tmpname,GimpRunMode run_mode,GError ** error)
name|uri_backend_save_image
parameter_list|(
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tmpname
parameter_list|,
name|GimpRunMode
name|run_mode
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|"EEK"
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

end_unit

