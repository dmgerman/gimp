begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpConfigWriter  * Copyright (C) 2003  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|<fcntl.h>
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
file|<sys/types.h>
end_include

begin_include
include|#
directive|include
file|<sys/stat.h>
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
file|<io.h>
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
file|"gimpconfig-error.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-serialize.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfigwriter.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_struct
DECL|struct|_GimpConfigWriter
struct|struct
name|_GimpConfigWriter
block|{
DECL|member|fd
name|gint
name|fd
decl_stmt|;
DECL|member|filename
name|gchar
modifier|*
name|filename
decl_stmt|;
DECL|member|tmpname
name|gchar
modifier|*
name|tmpname
decl_stmt|;
DECL|member|error
name|GError
modifier|*
name|error
decl_stmt|;
DECL|member|buffer
name|GString
modifier|*
name|buffer
decl_stmt|;
DECL|member|comment
name|gboolean
name|comment
decl_stmt|;
DECL|member|depth
name|gint
name|depth
decl_stmt|;
DECL|member|marker
name|gint
name|marker
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
specifier|inline
name|void
name|gimp_config_writer_flush
parameter_list|(
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
specifier|inline
name|void
name|gimp_config_writer_newline
parameter_list|(
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_config_writer_close_file
parameter_list|(
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/**  * gimp_config_writer_new_file:  * @filename: a filename  * @atomic: if %TRUE the file is written atomically  * @header: text to include as comment at the top of the file  * @error: return location for errors  *  * Creates a new #GimpConfigWriter and sets it up to write to  * @filename. If @atomic is %TRUE, a temporary file is used to avoid  * possible race conditions. The temporary file is then moved to  * @filename when the writer is closed.  *  * Return value: a new #GimpConfigWriter or %NULL in case of an error  **/
end_comment

begin_function
name|GimpConfigWriter
modifier|*
DECL|function|gimp_config_writer_new_file (const gchar * filename,gboolean atomic,const gchar * header,GError ** error)
name|gimp_config_writer_new_file
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gboolean
name|atomic
parameter_list|,
specifier|const
name|gchar
modifier|*
name|header
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpConfigWriter
modifier|*
name|writer
decl_stmt|;
name|gchar
modifier|*
name|tmpname
init|=
name|NULL
decl_stmt|;
name|gint
name|fd
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|filename
operator|!=
name|NULL
argument_list|,
name|NULL
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
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|atomic
condition|)
block|{
name|tmpname
operator|=
name|g_strconcat
argument_list|(
name|filename
argument_list|,
literal|"XXXXXX"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|fd
operator|=
name|g_mkstemp
argument_list|(
name|tmpname
argument_list|)
expr_stmt|;
if|if
condition|(
name|fd
operator|==
operator|-
literal|1
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_CONFIG_ERROR
argument_list|,
name|GIMP_CONFIG_ERROR_WRITE
argument_list|,
name|_
argument_list|(
literal|"Could not create temporary file for '%s': %s"
argument_list|)
argument_list|,
name|filename
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tmpname
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
block|}
else|else
block|{
name|fd
operator|=
name|creat
argument_list|(
name|filename
argument_list|,
literal|0644
argument_list|)
expr_stmt|;
if|if
condition|(
name|fd
operator|==
operator|-
literal|1
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_CONFIG_ERROR
argument_list|,
name|GIMP_CONFIG_ERROR_WRITE
argument_list|,
name|_
argument_list|(
literal|"Could not open '%s' for writing: %s"
argument_list|)
argument_list|,
name|filename
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
block|}
name|writer
operator|=
name|g_new0
argument_list|(
name|GimpConfigWriter
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|writer
operator|->
name|fd
operator|=
name|fd
expr_stmt|;
name|writer
operator|->
name|filename
operator|=
name|g_strdup
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|writer
operator|->
name|tmpname
operator|=
name|tmpname
expr_stmt|;
name|writer
operator|->
name|buffer
operator|=
name|g_string_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|header
condition|)
block|{
name|gimp_config_writer_comment
argument_list|(
name|writer
argument_list|,
name|header
argument_list|)
expr_stmt|;
name|gimp_config_writer_linefeed
argument_list|(
name|writer
argument_list|)
expr_stmt|;
block|}
return|return
name|writer
return|;
block|}
end_function

begin_function
name|GimpConfigWriter
modifier|*
DECL|function|gimp_config_writer_new_fd (gint fd)
name|gimp_config_writer_new_fd
parameter_list|(
name|gint
name|fd
parameter_list|)
block|{
name|GimpConfigWriter
modifier|*
name|writer
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|fd
operator|>
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|writer
operator|=
name|g_new0
argument_list|(
name|GimpConfigWriter
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|writer
operator|->
name|fd
operator|=
name|fd
expr_stmt|;
name|writer
operator|->
name|buffer
operator|=
name|g_string_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
return|return
name|writer
return|;
block|}
end_function

begin_function
name|GimpConfigWriter
modifier|*
DECL|function|gimp_config_writer_new_string (GString * string)
name|gimp_config_writer_new_string
parameter_list|(
name|GString
modifier|*
name|string
parameter_list|)
block|{
name|GimpConfigWriter
modifier|*
name|writer
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|string
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|writer
operator|=
name|g_new0
argument_list|(
name|GimpConfigWriter
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|writer
operator|->
name|buffer
operator|=
name|string
expr_stmt|;
return|return
name|writer
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_config_writer_comment_mode:  * @writer: a #GimpConfigWriter  * @enable: %TRUE to enable comment mode, %FALSE to disable it  *  * This function toggles whether the @writer should create commented  * or uncommented output. This feature is used to generate the  * system-wide installed gimprc that documents the default settings.  *  * Since comments have to start at the beginning of a line, this  * funtion will insert a newline if necessary.  **/
end_comment

begin_function
name|void
DECL|function|gimp_config_writer_comment_mode (GimpConfigWriter * writer,gboolean enable)
name|gimp_config_writer_comment_mode
parameter_list|(
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|,
name|gboolean
name|enable
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|writer
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|writer
operator|->
name|error
condition|)
return|return;
name|enable
operator|=
operator|(
name|enable
condition|?
name|TRUE
else|:
name|FALSE
operator|)
expr_stmt|;
if|if
condition|(
name|writer
operator|->
name|comment
operator|==
name|enable
condition|)
return|return;
name|writer
operator|->
name|comment
operator|=
name|enable
expr_stmt|;
if|if
condition|(
name|enable
condition|)
block|{
if|if
condition|(
name|writer
operator|->
name|buffer
operator|->
name|len
operator|==
literal|0
condition|)
name|g_string_append_len
argument_list|(
name|writer
operator|->
name|buffer
argument_list|,
literal|"# "
argument_list|,
literal|2
argument_list|)
expr_stmt|;
else|else
name|gimp_config_writer_newline
argument_list|(
name|writer
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_config_writer_open:  * @writer: a #GimpConfigWriter  * @name: name of the element to open  *  * This function writes the opening parenthese followed by @name.  * It also increases the indentation level and sets a mark that  * can be used by gimp_config_writer_revert().  **/
end_comment

begin_function
name|void
DECL|function|gimp_config_writer_open (GimpConfigWriter * writer,const gchar * name)
name|gimp_config_writer_open
parameter_list|(
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|writer
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|name
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|writer
operator|->
name|error
condition|)
return|return;
comment|/* store the current buffer length so we can revert to this state */
name|writer
operator|->
name|marker
operator|=
name|writer
operator|->
name|buffer
operator|->
name|len
expr_stmt|;
if|if
condition|(
name|writer
operator|->
name|depth
operator|>
literal|0
condition|)
name|gimp_config_writer_newline
argument_list|(
name|writer
argument_list|)
expr_stmt|;
name|writer
operator|->
name|depth
operator|++
expr_stmt|;
name|g_string_append_printf
argument_list|(
name|writer
operator|->
name|buffer
argument_list|,
literal|"(%s"
argument_list|,
name|name
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_config_writer_print:  * @writer: a #GimpConfigWriter  * @string: a string to write  * @len: number of bytes from @string or -1 if @string is NUL-terminated.  *  * Appends a space followed by @string to the @writer. Note that string  * must not contain any special characters that might need to be escaped.  **/
end_comment

begin_function
name|void
DECL|function|gimp_config_writer_print (GimpConfigWriter * writer,const gchar * string,gint len)
name|gimp_config_writer_print
parameter_list|(
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|,
specifier|const
name|gchar
modifier|*
name|string
parameter_list|,
name|gint
name|len
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|writer
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|len
operator|==
literal|0
operator|||
name|string
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|writer
operator|->
name|error
condition|)
return|return;
if|if
condition|(
name|len
operator|<
literal|0
condition|)
name|len
operator|=
name|strlen
argument_list|(
name|string
argument_list|)
expr_stmt|;
if|if
condition|(
name|len
condition|)
block|{
name|g_string_append_c
argument_list|(
name|writer
operator|->
name|buffer
argument_list|,
literal|' '
argument_list|)
expr_stmt|;
name|g_string_append_len
argument_list|(
name|writer
operator|->
name|buffer
argument_list|,
name|string
argument_list|,
name|len
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_config_writer_printf:  * @writer: a #GimpConfigWriter  * @format: a format string as described for g_strdup_printf().  * @Varargs: list of arguments according to @format  *  * A printf-like function for #GimpConfigWriter.  **/
end_comment

begin_function
name|void
DECL|function|gimp_config_writer_printf (GimpConfigWriter * writer,const gchar * format,...)
name|gimp_config_writer_printf
parameter_list|(
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|,
specifier|const
name|gchar
modifier|*
name|format
parameter_list|,
modifier|...
parameter_list|)
block|{
name|gchar
modifier|*
name|buffer
decl_stmt|;
name|va_list
name|args
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|writer
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|format
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|writer
operator|->
name|error
condition|)
return|return;
name|va_start
argument_list|(
name|args
argument_list|,
name|format
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|g_strdup_vprintf
argument_list|(
name|format
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
name|g_string_append_c
argument_list|(
name|writer
operator|->
name|buffer
argument_list|,
literal|' '
argument_list|)
expr_stmt|;
name|g_string_append
argument_list|(
name|writer
operator|->
name|buffer
argument_list|,
name|buffer
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_config_writer_string:  * @writer: a #GimpConfigWriter  * @string: a NUL-terminated string  *  * Writes a string value to @writer. The @string is quoted and special  * characters are escaped.  **/
end_comment

begin_function
name|void
DECL|function|gimp_config_writer_string (GimpConfigWriter * writer,const gchar * string)
name|gimp_config_writer_string
parameter_list|(
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|,
specifier|const
name|gchar
modifier|*
name|string
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|writer
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|writer
operator|->
name|error
condition|)
return|return;
name|g_string_append_c
argument_list|(
name|writer
operator|->
name|buffer
argument_list|,
literal|' '
argument_list|)
expr_stmt|;
name|gimp_config_string_append_escaped
argument_list|(
name|writer
operator|->
name|buffer
argument_list|,
name|string
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_config_writer_revert:  * @writer: a #GimpConfigWriter  *  * Reverts all changes to @writer that were done since the last call  * to gimp_config_writer_open(). This can only work if you didn't call  * gimp_config_writer_close() yet.  **/
end_comment

begin_function
name|void
DECL|function|gimp_config_writer_revert (GimpConfigWriter * writer)
name|gimp_config_writer_revert
parameter_list|(
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|writer
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|writer
operator|->
name|depth
operator|>
literal|0
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|writer
operator|->
name|marker
operator|!=
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|writer
operator|->
name|error
condition|)
return|return;
name|g_string_truncate
argument_list|(
name|writer
operator|->
name|buffer
argument_list|,
name|writer
operator|->
name|marker
argument_list|)
expr_stmt|;
name|writer
operator|->
name|depth
operator|--
expr_stmt|;
name|writer
operator|->
name|marker
operator|=
operator|-
literal|1
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_config_writer_close:  * @writer: a #GimpConfigWriter  *  * Closes an element opened with gimp_config_writer_open().  **/
end_comment

begin_function
name|void
DECL|function|gimp_config_writer_close (GimpConfigWriter * writer)
name|gimp_config_writer_close
parameter_list|(
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|writer
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|writer
operator|->
name|depth
operator|>
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|writer
operator|->
name|error
condition|)
return|return;
name|g_string_append_c
argument_list|(
name|writer
operator|->
name|buffer
argument_list|,
literal|')'
argument_list|)
expr_stmt|;
if|if
condition|(
operator|--
name|writer
operator|->
name|depth
operator|==
literal|0
condition|)
block|{
name|g_string_append_c
argument_list|(
name|writer
operator|->
name|buffer
argument_list|,
literal|'\n'
argument_list|)
expr_stmt|;
if|if
condition|(
name|writer
operator|->
name|fd
condition|)
name|gimp_config_writer_flush
argument_list|(
name|writer
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_config_writer_finish:  * @writer: a #GimpConfigWriter  * @footer: text to include as comment at the bottom of the file  * @error: return location for possible errors  *  * This function finishes the work of @writer and frees it afterwards.  * It closes all open elements, appends an optional comment and  * releases all resources allocated by @writer. You must not access  * the @writer afterwards.  *  * Return value: %TRUE if everything could be successfully written,  *               %FALSE otherwise  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_config_writer_finish (GimpConfigWriter * writer,const gchar * footer,GError ** error)
name|gimp_config_writer_finish
parameter_list|(
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|,
specifier|const
name|gchar
modifier|*
name|footer
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|writer
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
if|if
condition|(
name|writer
operator|->
name|depth
operator|<
literal|0
condition|)
block|{
name|g_warning
argument_list|(
literal|"gimp_config_writer_finish: depth< 0 !!"
argument_list|)
expr_stmt|;
block|}
else|else
block|{
while|while
condition|(
name|writer
operator|->
name|depth
condition|)
name|gimp_config_writer_close
argument_list|(
name|writer
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|footer
condition|)
block|{
name|gimp_config_writer_linefeed
argument_list|(
name|writer
argument_list|)
expr_stmt|;
name|gimp_config_writer_comment
argument_list|(
name|writer
argument_list|,
name|footer
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|writer
operator|->
name|fd
condition|)
block|{
name|success
operator|=
name|gimp_config_writer_close_file
argument_list|(
name|writer
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|writer
operator|->
name|filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|writer
operator|->
name|tmpname
argument_list|)
expr_stmt|;
name|g_string_free
argument_list|(
name|writer
operator|->
name|buffer
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|success
operator|=
name|TRUE
expr_stmt|;
block|}
name|g_free
argument_list|(
name|writer
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_config_writer_linefeed (GimpConfigWriter * writer)
name|gimp_config_writer_linefeed
parameter_list|(
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|writer
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|writer
operator|->
name|error
condition|)
return|return;
if|if
condition|(
name|writer
operator|->
name|buffer
operator|->
name|len
operator|==
literal|0
operator|&&
operator|!
name|writer
operator|->
name|comment
condition|)
block|{
if|if
condition|(
name|write
argument_list|(
name|writer
operator|->
name|fd
argument_list|,
literal|"\n"
argument_list|,
literal|1
argument_list|)
operator|<
literal|0
condition|)
name|g_set_error
argument_list|(
operator|&
name|writer
operator|->
name|error
argument_list|,
name|GIMP_CONFIG_ERROR
argument_list|,
name|GIMP_CONFIG_ERROR_WRITE
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_config_writer_newline
argument_list|(
name|writer
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_config_writer_comment:  * @writer: a #GimpConfigWriter  * @comment: the comment to write (ASCII only)  *  * Appends the @comment to @str and inserts linebreaks and hash-marks to  * format it as a comment. Note that this function does not handle non-ASCII  * characters.  **/
end_comment

begin_function
name|void
DECL|function|gimp_config_writer_comment (GimpConfigWriter * writer,const gchar * comment)
name|gimp_config_writer_comment
parameter_list|(
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|,
specifier|const
name|gchar
modifier|*
name|comment
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|s
decl_stmt|;
name|gboolean
name|comment_mode
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|len
decl_stmt|,
name|space
decl_stmt|;
DECL|macro|LINE_LENGTH
define|#
directive|define
name|LINE_LENGTH
value|75
name|g_return_if_fail
argument_list|(
name|writer
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|writer
operator|->
name|depth
operator|==
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|writer
operator|->
name|error
condition|)
return|return;
if|if
condition|(
operator|!
name|comment
condition|)
return|return;
name|comment_mode
operator|=
name|writer
operator|->
name|comment
expr_stmt|;
name|gimp_config_writer_comment_mode
argument_list|(
name|writer
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|len
operator|=
name|strlen
argument_list|(
name|comment
argument_list|)
expr_stmt|;
while|while
condition|(
name|len
operator|>
literal|0
condition|)
block|{
for|for
control|(
name|s
operator|=
name|comment
operator|,
name|i
operator|=
literal|0
operator|,
name|space
operator|=
literal|0
init|;
operator|*
name|s
operator|!=
literal|'\n'
operator|&&
operator|(
name|i
operator|<=
name|LINE_LENGTH
operator|||
name|space
operator|==
literal|0
operator|)
operator|&&
name|i
operator|<
name|len
condition|;
name|s
operator|++
operator|,
name|i
operator|++
control|)
block|{
if|if
condition|(
name|g_ascii_isspace
argument_list|(
operator|*
name|s
argument_list|)
condition|)
name|space
operator|=
name|i
expr_stmt|;
block|}
if|if
condition|(
name|i
operator|>
name|LINE_LENGTH
operator|&&
name|space
operator|&&
operator|*
name|s
operator|!=
literal|'\n'
condition|)
name|i
operator|=
name|space
expr_stmt|;
name|g_string_append_len
argument_list|(
name|writer
operator|->
name|buffer
argument_list|,
name|comment
argument_list|,
name|i
argument_list|)
expr_stmt|;
name|i
operator|++
expr_stmt|;
name|comment
operator|+=
name|i
expr_stmt|;
name|len
operator|-=
name|i
expr_stmt|;
if|if
condition|(
name|len
operator|>
literal|0
condition|)
name|gimp_config_writer_newline
argument_list|(
name|writer
argument_list|)
expr_stmt|;
block|}
name|gimp_config_writer_comment_mode
argument_list|(
name|writer
argument_list|,
name|comment_mode
argument_list|)
expr_stmt|;
name|gimp_config_writer_newline
argument_list|(
name|writer
argument_list|)
expr_stmt|;
if|if
condition|(
name|writer
operator|->
name|depth
operator|==
literal|0
condition|)
name|gimp_config_writer_flush
argument_list|(
name|writer
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|LINE_LENGTH
block|}
end_function

begin_function
specifier|static
specifier|inline
name|void
DECL|function|gimp_config_writer_flush (GimpConfigWriter * writer)
name|gimp_config_writer_flush
parameter_list|(
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|)
block|{
if|if
condition|(
name|write
argument_list|(
name|writer
operator|->
name|fd
argument_list|,
name|writer
operator|->
name|buffer
operator|->
name|str
argument_list|,
name|writer
operator|->
name|buffer
operator|->
name|len
argument_list|)
operator|<
literal|0
condition|)
name|g_set_error
argument_list|(
operator|&
name|writer
operator|->
name|error
argument_list|,
name|GIMP_CONFIG_ERROR
argument_list|,
name|GIMP_CONFIG_ERROR_WRITE
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
name|g_string_truncate
argument_list|(
name|writer
operator|->
name|buffer
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
specifier|inline
name|void
DECL|function|gimp_config_writer_newline (GimpConfigWriter * writer)
name|gimp_config_writer_newline
parameter_list|(
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|g_string_append_c
argument_list|(
name|writer
operator|->
name|buffer
argument_list|,
literal|'\n'
argument_list|)
expr_stmt|;
if|if
condition|(
name|writer
operator|->
name|comment
condition|)
name|g_string_append_len
argument_list|(
name|writer
operator|->
name|buffer
argument_list|,
literal|"# "
argument_list|,
literal|2
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|writer
operator|->
name|depth
condition|;
name|i
operator|++
control|)
name|g_string_append_len
argument_list|(
name|writer
operator|->
name|buffer
argument_list|,
literal|"    "
argument_list|,
literal|4
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_config_writer_close_file (GimpConfigWriter * writer,GError ** error)
name|gimp_config_writer_close_file
parameter_list|(
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|writer
operator|->
name|fd
operator|!=
literal|0
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|writer
operator|->
name|filename
condition|)
return|return
name|TRUE
return|;
if|if
condition|(
name|writer
operator|->
name|error
condition|)
block|{
name|close
argument_list|(
name|writer
operator|->
name|fd
argument_list|)
expr_stmt|;
if|if
condition|(
name|writer
operator|->
name|tmpname
condition|)
name|unlink
argument_list|(
name|writer
operator|->
name|tmpname
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
if|if
condition|(
name|close
argument_list|(
name|writer
operator|->
name|fd
argument_list|)
operator|!=
literal|0
condition|)
block|{
if|if
condition|(
name|writer
operator|->
name|tmpname
condition|)
block|{
if|if
condition|(
name|g_file_test
argument_list|(
name|writer
operator|->
name|filename
argument_list|,
name|G_FILE_TEST_EXISTS
argument_list|)
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_CONFIG_ERROR
argument_list|,
name|GIMP_CONFIG_ERROR_WRITE
argument_list|,
name|_
argument_list|(
literal|"Error writing to temporary file for '%s': %s\n"
literal|"The original file has not been touched."
argument_list|)
argument_list|,
name|writer
operator|->
name|filename
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_CONFIG_ERROR
argument_list|,
name|GIMP_CONFIG_ERROR_WRITE
argument_list|,
name|_
argument_list|(
literal|"Error writing to temporary file for '%s': %s\n"
literal|"No file has been created."
argument_list|)
argument_list|,
name|writer
operator|->
name|filename
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|unlink
argument_list|(
name|writer
operator|->
name|tmpname
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_CONFIG_ERROR
argument_list|,
name|GIMP_CONFIG_ERROR_WRITE
argument_list|,
name|_
argument_list|(
literal|"Error writing to '%s': %s"
argument_list|)
argument_list|,
name|writer
operator|->
name|filename
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
block|}
return|return
name|FALSE
return|;
block|}
if|if
condition|(
name|writer
operator|->
name|tmpname
condition|)
block|{
ifdef|#
directive|ifdef
name|G_OS_WIN32
comment|/* win32 rename can't overwrite */
name|unlink
argument_list|(
name|writer
operator|->
name|filename
argument_list|)
expr_stmt|;
endif|#
directive|endif
if|if
condition|(
name|rename
argument_list|(
name|writer
operator|->
name|tmpname
argument_list|,
name|writer
operator|->
name|filename
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_CONFIG_ERROR
argument_list|,
name|GIMP_CONFIG_ERROR_WRITE
argument_list|,
name|_
argument_list|(
literal|"Could not create '%s': %s"
argument_list|)
argument_list|,
name|writer
operator|->
name|filename
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
name|unlink
argument_list|(
name|writer
operator|->
name|tmpname
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

end_unit

