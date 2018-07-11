begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpConfigWriter  * Copyright (C) 2003  Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<gio/gio.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_include
include|#
directive|include
file|<gio/gwin32outputstream.h>
end_include

begin_else
else|#
directive|else
end_else

begin_include
include|#
directive|include
file|<gio/gunixoutputstream.h>
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
file|"gimpconfigtypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfigwriter.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-iface.h"
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
file|"libgimp/libgimp-intl.h"
end_include

begin_comment
comment|/**  * SECTION: gimpconfigwriter  * @title: GimpConfigWriter  * @short_description: Functions for writing config info to a file for  *                     libgimpconfig.  *  * Functions for writing config info to a file for libgimpconfig.  **/
end_comment

begin_struct
DECL|struct|_GimpConfigWriter
struct|struct
name|_GimpConfigWriter
block|{
DECL|member|output
name|GOutputStream
modifier|*
name|output
decl_stmt|;
DECL|member|file
name|GFile
modifier|*
name|file
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
name|gimp_config_writer_close_output
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
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|writer
operator|->
name|output
condition|)
return|return;
if|if
condition|(
operator|!
name|g_output_stream_write_all
argument_list|(
name|writer
operator|->
name|output
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
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
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
name|_
argument_list|(
literal|"Error writing to '%s': %s"
argument_list|)
argument_list|,
name|writer
operator|->
name|file
condition|?
name|gimp_file_get_utf8_name
argument_list|(
name|writer
operator|->
name|file
argument_list|)
else|:
literal|"output stream"
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
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

begin_comment
comment|/**  * gimp_config_writer_new_file:  * @filename: a filename  * @atomic: if %TRUE the file is written atomically  * @header: text to include as comment at the top of the file  * @error: return location for errors  *  * Creates a new #GimpConfigWriter and sets it up to write to  * @filename. If @atomic is %TRUE, a temporary file is used to avoid  * possible race conditions. The temporary file is then moved to  * @filename when the writer is closed.  *  * Return value: a new #GimpConfigWriter or %NULL in case of an error  *  * Since: 2.4  **/
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
name|GFile
modifier|*
name|file
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
name|file
operator|=
name|g_file_new_for_path
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|writer
operator|=
name|gimp_config_writer_new_gfile
argument_list|(
name|file
argument_list|,
name|atomic
argument_list|,
name|header
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
return|return
name|writer
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_config_writer_new_gfile:  * @file: a #GFile  * @atomic: if %TRUE the file is written atomically  * @header: text to include as comment at the top of the file  * @error: return location for errors  *  * Creates a new #GimpConfigWriter and sets it up to write to  * @file. If @atomic is %TRUE, a temporary file is used to avoid  * possible race conditions. The temporary file is then moved to @file  * when the writer is closed.  *  * Return value: a new #GimpConfigWriter or %NULL in case of an error  *  * Since: 2.10  **/
end_comment

begin_function
name|GimpConfigWriter
modifier|*
DECL|function|gimp_config_writer_new_gfile (GFile * file,gboolean atomic,const gchar * header,GError ** error)
name|gimp_config_writer_new_gfile
parameter_list|(
name|GFile
modifier|*
name|file
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
name|GOutputStream
modifier|*
name|output
decl_stmt|;
name|GFile
modifier|*
name|dir
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_IS_FILE
argument_list|(
name|file
argument_list|)
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
name|dir
operator|=
name|g_file_get_parent
argument_list|(
name|file
argument_list|)
expr_stmt|;
if|if
condition|(
name|dir
operator|&&
operator|!
name|g_file_query_exists
argument_list|(
name|dir
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
if|if
condition|(
operator|!
name|g_file_make_directory_with_parents
argument_list|(
name|dir
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
condition|)
name|g_prefix_error
argument_list|(
name|error
argument_list|,
name|_
argument_list|(
literal|"Could not create directory '%s' for '%s': "
argument_list|)
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|dir
argument_list|)
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|file
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|dir
argument_list|)
expr_stmt|;
if|if
condition|(
name|error
operator|&&
operator|*
name|error
condition|)
return|return
name|NULL
return|;
if|if
condition|(
name|atomic
condition|)
block|{
name|output
operator|=
name|G_OUTPUT_STREAM
argument_list|(
name|g_file_replace
argument_list|(
name|file
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|G_FILE_CREATE_NONE
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|output
condition|)
name|g_prefix_error
argument_list|(
name|error
argument_list|,
name|_
argument_list|(
literal|"Could not create temporary file for '%s': "
argument_list|)
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|file
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|output
operator|=
name|G_OUTPUT_STREAM
argument_list|(
name|g_file_replace
argument_list|(
name|file
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|G_FILE_CREATE_REPLACE_DESTINATION
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|output
condition|)
return|return
name|NULL
return|;
name|writer
operator|=
name|g_slice_new0
argument_list|(
name|GimpConfigWriter
argument_list|)
expr_stmt|;
name|writer
operator|->
name|output
operator|=
name|output
expr_stmt|;
name|writer
operator|->
name|file
operator|=
name|g_object_ref
argument_list|(
name|file
argument_list|)
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

begin_comment
comment|/**  * gimp_config_writer_new_stream:  * @output: a #GOutputStream  * @header: text to include as comment at the top of the file  * @error: return location for errors  *  * Creates a new #GimpConfigWriter and sets it up to write to  * @output.  *  * Return value: a new #GimpConfigWriter or %NULL in case of an error  *  * Since: 2.10  **/
end_comment

begin_function
name|GimpConfigWriter
modifier|*
DECL|function|gimp_config_writer_new_stream (GOutputStream * output,const gchar * header,GError ** error)
name|gimp_config_writer_new_stream
parameter_list|(
name|GOutputStream
modifier|*
name|output
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
name|g_return_val_if_fail
argument_list|(
name|G_IS_OUTPUT_STREAM
argument_list|(
name|output
argument_list|)
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
name|writer
operator|=
name|g_slice_new0
argument_list|(
name|GimpConfigWriter
argument_list|)
expr_stmt|;
name|writer
operator|->
name|output
operator|=
name|g_object_ref
argument_list|(
name|output
argument_list|)
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

begin_comment
comment|/**  * gimp_config_writer_new_fd:  * @fd:  *  * Return value: a new #GimpConfigWriter or %NULL in case of an error  *  * Since: 2.4  **/
end_comment

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
name|g_slice_new0
argument_list|(
name|GimpConfigWriter
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|G_OS_WIN32
name|writer
operator|->
name|output
operator|=
name|g_win32_output_stream_new
argument_list|(
operator|(
name|gpointer
operator|)
name|fd
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
else|#
directive|else
name|writer
operator|->
name|output
operator|=
name|g_unix_output_stream_new
argument_list|(
name|fd
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
endif|#
directive|endif
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

begin_comment
comment|/**  * gimp_config_writer_new_string:  * @string:  *  * Return value: a new #GimpConfigWriter or %NULL in case of an error  *  * Since: 2.4  **/
end_comment

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
name|g_slice_new0
argument_list|(
name|GimpConfigWriter
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
comment|/**  * gimp_config_writer_comment_mode:  * @writer: a #GimpConfigWriter  * @enable: %TRUE to enable comment mode, %FALSE to disable it  *  * This function toggles whether the @writer should create commented  * or uncommented output. This feature is used to generate the  * system-wide installed gimprc that documents the default settings.  *  * Since comments have to start at the beginning of a line, this  * function will insert a newline if necessary.  *  * Since: 2.4  **/
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
comment|/**  * gimp_config_writer_open:  * @writer: a #GimpConfigWriter  * @name: name of the element to open  *  * This function writes the opening parenthesis followed by @name.  * It also increases the indentation level and sets a mark that  * can be used by gimp_config_writer_revert().  *  * Since: 2.4  **/
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
comment|/**  * gimp_config_writer_print:  * @writer: a #GimpConfigWriter  * @string: a string to write  * @len: number of bytes from @string or -1 if @string is NUL-terminated.  *  * Appends a space followed by @string to the @writer. Note that string  * must not contain any special characters that might need to be escaped.  *  * Since: 2.4  **/
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
comment|/**  * gimp_config_writer_printf:  * @writer: a #GimpConfigWriter  * @format: a format string as described for g_strdup_printf().  * @...: list of arguments according to @format  *  * A printf-like function for #GimpConfigWriter.  *  * Since: 2.4  **/
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
comment|/**  * gimp_config_writer_string:  * @writer: a #GimpConfigWriter  * @string: a NUL-terminated string  *  * Writes a string value to @writer. The @string is quoted and special  * characters are escaped.  *  * Since: 2.4  **/
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
comment|/**  * gimp_config_writer_identifier:  * @writer:     a #GimpConfigWriter  * @identifier: a NUL-terminated string  *  * Writes an identifier to @writer. The @string is *not* quoted and special  * characters are *not* escaped.  *  * Since: 2.4  **/
end_comment

begin_function
name|void
DECL|function|gimp_config_writer_identifier (GimpConfigWriter * writer,const gchar * identifier)
name|gimp_config_writer_identifier
parameter_list|(
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|,
specifier|const
name|gchar
modifier|*
name|identifier
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
name|identifier
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
name|g_string_append_printf
argument_list|(
name|writer
operator|->
name|buffer
argument_list|,
literal|" %s"
argument_list|,
name|identifier
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_config_writer_data:  * @writer: a #GimpConfigWriter  * @length:  * @data:  *  * Since: 2.4  **/
end_comment

begin_function
name|void
DECL|function|gimp_config_writer_data (GimpConfigWriter * writer,gint length,const guint8 * data)
name|gimp_config_writer_data
parameter_list|(
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|,
name|gint
name|length
parameter_list|,
specifier|const
name|guint8
modifier|*
name|data
parameter_list|)
block|{
name|gint
name|i
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
name|length
operator|>=
literal|0
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|data
operator|!=
name|NULL
operator|||
name|length
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
name|g_string_append
argument_list|(
name|writer
operator|->
name|buffer
argument_list|,
literal|" \""
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
name|length
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|g_ascii_isalpha
argument_list|(
name|data
index|[
name|i
index|]
argument_list|)
condition|)
name|g_string_append_c
argument_list|(
name|writer
operator|->
name|buffer
argument_list|,
name|data
index|[
name|i
index|]
argument_list|)
expr_stmt|;
else|else
name|g_string_append_printf
argument_list|(
name|writer
operator|->
name|buffer
argument_list|,
literal|"\\%o"
argument_list|,
name|data
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
name|g_string_append
argument_list|(
name|writer
operator|->
name|buffer
argument_list|,
literal|"\""
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_config_writer_revert:  * @writer: a #GimpConfigWriter  *  * Reverts all changes to @writer that were done since the last call  * to gimp_config_writer_open(). This can only work if you didn't call  * gimp_config_writer_close() yet.  *  * Since: 2.4  **/
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
if|if
condition|(
name|writer
operator|->
name|error
condition|)
return|return;
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
comment|/**  * gimp_config_writer_close:  * @writer: a #GimpConfigWriter  *  * Closes an element opened with gimp_config_writer_open().  *  * Since: 2.4  **/
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
if|if
condition|(
name|writer
operator|->
name|error
condition|)
return|return;
name|g_return_if_fail
argument_list|(
name|writer
operator|->
name|depth
operator|>
literal|0
argument_list|)
expr_stmt|;
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
name|gimp_config_writer_flush
argument_list|(
name|writer
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_config_writer_finish:  * @writer: a #GimpConfigWriter  * @footer: text to include as comment at the bottom of the file  * @error: return location for possible errors  *  * This function finishes the work of @writer and frees it afterwards.  * It closes all open elements, appends an optional comment and  * releases all resources allocated by @writer. You must not access  * the @writer afterwards.  *  * Return value: %TRUE if everything could be successfully written,  *               %FALSE otherwise  *  * Since: 2.4  **/
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
name|output
condition|)
block|{
name|success
operator|=
name|gimp_config_writer_close_output
argument_list|(
name|writer
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|writer
operator|->
name|file
condition|)
name|g_object_unref
argument_list|(
name|writer
operator|->
name|file
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
if|if
condition|(
name|writer
operator|->
name|error
condition|)
block|{
if|if
condition|(
name|error
operator|&&
operator|*
name|error
operator|==
name|NULL
condition|)
name|g_propagate_error
argument_list|(
name|error
argument_list|,
name|writer
operator|->
name|error
argument_list|)
expr_stmt|;
else|else
name|g_clear_error
argument_list|(
operator|&
name|writer
operator|->
name|error
argument_list|)
expr_stmt|;
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
name|g_slice_free
argument_list|(
name|GimpConfigWriter
argument_list|,
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
name|output
operator|&&
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
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|g_output_stream_write_all
argument_list|(
name|writer
operator|->
name|output
argument_list|,
literal|"\n"
argument_list|,
literal|1
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
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
name|_
argument_list|(
literal|"Error writing to '%s': %s"
argument_list|)
argument_list|,
name|writer
operator|->
name|file
condition|?
name|gimp_file_get_utf8_name
argument_list|(
name|writer
operator|->
name|file
argument_list|)
else|:
literal|"output stream"
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
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
comment|/**  * gimp_config_writer_comment:  * @writer: a #GimpConfigWriter  * @comment: the comment to write (ASCII only)  *  * Appends the @comment to @str and inserts linebreaks and hash-marks to  * format it as a comment. Note that this function does not handle non-ASCII  * characters.  *  * Since: 2.4  **/
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
if|if
condition|(
name|writer
operator|->
name|error
condition|)
return|return;
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
name|gboolean
DECL|function|gimp_config_writer_close_output (GimpConfigWriter * writer,GError ** error)
name|gimp_config_writer_close_output
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
name|output
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|writer
operator|->
name|error
condition|)
block|{
name|g_object_unref
argument_list|(
name|writer
operator|->
name|output
argument_list|)
expr_stmt|;
name|writer
operator|->
name|output
operator|=
name|NULL
expr_stmt|;
return|return
name|FALSE
return|;
block|}
if|if
condition|(
name|writer
operator|->
name|file
condition|)
block|{
name|GError
modifier|*
name|my_error
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|g_output_stream_close
argument_list|(
name|writer
operator|->
name|output
argument_list|,
name|NULL
argument_list|,
operator|&
name|my_error
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
literal|"Error writing '%s': %s"
argument_list|)
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|writer
operator|->
name|file
argument_list|)
argument_list|,
name|my_error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|my_error
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|writer
operator|->
name|output
argument_list|)
expr_stmt|;
name|writer
operator|->
name|output
operator|=
name|NULL
expr_stmt|;
return|return
name|FALSE
return|;
block|}
block|}
name|g_object_unref
argument_list|(
name|writer
operator|->
name|output
argument_list|)
expr_stmt|;
name|writer
operator|->
name|output
operator|=
name|NULL
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

end_unit

