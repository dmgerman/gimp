begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
file|<stdio.h>
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
file|<glib.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_include
include|#
directive|include
file|<process.h>
end_include

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
file|"gimpwire.h"
end_include

begin_typedef
DECL|typedef|WireHandler
typedef|typedef
name|struct
name|_WireHandler
name|WireHandler
typedef|;
end_typedef

begin_struct
DECL|struct|_WireHandler
struct|struct
name|_WireHandler
block|{
DECL|member|type
name|guint32
name|type
decl_stmt|;
DECL|member|read_func
name|WireReadFunc
name|read_func
decl_stmt|;
DECL|member|write_func
name|WireWriteFunc
name|write_func
decl_stmt|;
DECL|member|destroy_func
name|WireDestroyFunc
name|destroy_func
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|wire_init
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|guint
name|wire_hash
parameter_list|(
name|guint32
modifier|*
name|key
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|wire_compare
parameter_list|(
name|guint32
modifier|*
name|a
parameter_list|,
name|guint32
modifier|*
name|b
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|wire_ht
specifier|static
name|GHashTable
modifier|*
name|wire_ht
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|wire_read_func
specifier|static
name|WireIOFunc
name|wire_read_func
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|wire_write_func
specifier|static
name|WireIOFunc
name|wire_write_func
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|wire_flush_func
specifier|static
name|WireFlushFunc
name|wire_flush_func
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|wire_error_val
specifier|static
name|gboolean
name|wire_error_val
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|wire_register (guint32 type,WireReadFunc read_func,WireWriteFunc write_func,WireDestroyFunc destroy_func)
name|wire_register
parameter_list|(
name|guint32
name|type
parameter_list|,
name|WireReadFunc
name|read_func
parameter_list|,
name|WireWriteFunc
name|write_func
parameter_list|,
name|WireDestroyFunc
name|destroy_func
parameter_list|)
block|{
name|WireHandler
modifier|*
name|handler
decl_stmt|;
if|if
condition|(
operator|!
name|wire_ht
condition|)
name|wire_init
argument_list|()
expr_stmt|;
name|handler
operator|=
name|g_hash_table_lookup
argument_list|(
name|wire_ht
argument_list|,
operator|&
name|type
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|handler
condition|)
name|handler
operator|=
name|g_new
argument_list|(
name|WireHandler
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|handler
operator|->
name|type
operator|=
name|type
expr_stmt|;
name|handler
operator|->
name|read_func
operator|=
name|read_func
expr_stmt|;
name|handler
operator|->
name|write_func
operator|=
name|write_func
expr_stmt|;
name|handler
operator|->
name|destroy_func
operator|=
name|destroy_func
expr_stmt|;
name|g_hash_table_insert
argument_list|(
name|wire_ht
argument_list|,
operator|&
name|handler
operator|->
name|type
argument_list|,
name|handler
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|wire_set_reader (WireIOFunc read_func)
name|wire_set_reader
parameter_list|(
name|WireIOFunc
name|read_func
parameter_list|)
block|{
name|wire_read_func
operator|=
name|read_func
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|wire_set_writer (WireIOFunc write_func)
name|wire_set_writer
parameter_list|(
name|WireIOFunc
name|write_func
parameter_list|)
block|{
name|wire_write_func
operator|=
name|write_func
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|wire_set_flusher (WireFlushFunc flush_func)
name|wire_set_flusher
parameter_list|(
name|WireFlushFunc
name|flush_func
parameter_list|)
block|{
name|wire_flush_func
operator|=
name|flush_func
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|wire_read (GIOChannel * channel,guint8 * buf,gsize count,gpointer user_data)
name|wire_read
parameter_list|(
name|GIOChannel
modifier|*
name|channel
parameter_list|,
name|guint8
modifier|*
name|buf
parameter_list|,
name|gsize
name|count
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
if|if
condition|(
name|wire_read_func
condition|)
block|{
if|if
condition|(
operator|!
call|(
modifier|*
name|wire_read_func
call|)
argument_list|(
name|channel
argument_list|,
name|buf
argument_list|,
name|count
argument_list|,
name|user_data
argument_list|)
condition|)
block|{
name|g_warning
argument_list|(
literal|"%s: wire_read: error"
argument_list|,
name|g_get_prgname
argument_list|()
argument_list|)
expr_stmt|;
name|wire_error_val
operator|=
name|TRUE
expr_stmt|;
return|return
name|FALSE
return|;
block|}
block|}
else|else
block|{
name|GIOStatus
name|status
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|gsize
name|bytes
decl_stmt|;
while|while
condition|(
name|count
operator|>
literal|0
condition|)
block|{
do|do
block|{
name|bytes
operator|=
literal|0
expr_stmt|;
name|status
operator|=
name|g_io_channel_read_chars
argument_list|(
name|channel
argument_list|,
operator|(
name|gchar
operator|*
operator|)
name|buf
argument_list|,
name|count
argument_list|,
operator|&
name|bytes
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
do|while
condition|(
name|status
operator|==
name|G_IO_STATUS_AGAIN
condition|)
do|;
if|if
condition|(
name|status
operator|!=
name|G_IO_STATUS_NORMAL
condition|)
block|{
if|if
condition|(
name|error
condition|)
block|{
name|g_warning
argument_list|(
literal|"%s: wire_read(): error: %s"
argument_list|,
name|g_get_prgname
argument_list|()
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_error_free
argument_list|(
name|error
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_warning
argument_list|(
literal|"%s: wire_read(): error"
argument_list|,
name|g_get_prgname
argument_list|()
argument_list|)
expr_stmt|;
block|}
name|wire_error_val
operator|=
name|TRUE
expr_stmt|;
return|return
name|FALSE
return|;
block|}
if|if
condition|(
name|bytes
operator|==
literal|0
condition|)
block|{
name|g_warning
argument_list|(
literal|"%s: wire_read(): unexpected EOF"
argument_list|,
name|g_get_prgname
argument_list|()
argument_list|)
expr_stmt|;
name|wire_error_val
operator|=
name|TRUE
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|count
operator|-=
name|bytes
expr_stmt|;
name|buf
operator|+=
name|bytes
expr_stmt|;
block|}
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|wire_write (GIOChannel * channel,guint8 * buf,gsize count,gpointer user_data)
name|wire_write
parameter_list|(
name|GIOChannel
modifier|*
name|channel
parameter_list|,
name|guint8
modifier|*
name|buf
parameter_list|,
name|gsize
name|count
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
if|if
condition|(
name|wire_write_func
condition|)
block|{
if|if
condition|(
operator|!
call|(
modifier|*
name|wire_write_func
call|)
argument_list|(
name|channel
argument_list|,
name|buf
argument_list|,
name|count
argument_list|,
name|user_data
argument_list|)
condition|)
block|{
name|g_warning
argument_list|(
literal|"%s: wire_write: error"
argument_list|,
name|g_get_prgname
argument_list|()
argument_list|)
expr_stmt|;
name|wire_error_val
operator|=
name|TRUE
expr_stmt|;
return|return
name|FALSE
return|;
block|}
block|}
else|else
block|{
name|GIOStatus
name|status
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|gsize
name|bytes
decl_stmt|;
while|while
condition|(
name|count
operator|>
literal|0
condition|)
block|{
do|do
block|{
name|bytes
operator|=
literal|0
expr_stmt|;
name|status
operator|=
name|g_io_channel_write_chars
argument_list|(
name|channel
argument_list|,
operator|(
name|gchar
operator|*
operator|)
name|buf
argument_list|,
name|count
argument_list|,
operator|&
name|bytes
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
do|while
condition|(
name|status
operator|==
name|G_IO_STATUS_AGAIN
condition|)
do|;
if|if
condition|(
name|status
operator|!=
name|G_IO_STATUS_NORMAL
condition|)
block|{
if|if
condition|(
name|error
condition|)
block|{
name|g_warning
argument_list|(
literal|"%s: wire_write(): error: %s"
argument_list|,
name|g_get_prgname
argument_list|()
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_error_free
argument_list|(
name|error
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_warning
argument_list|(
literal|"%s: wire_write(): error"
argument_list|,
name|g_get_prgname
argument_list|()
argument_list|)
expr_stmt|;
block|}
name|wire_error_val
operator|=
name|TRUE
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|count
operator|-=
name|bytes
expr_stmt|;
name|buf
operator|+=
name|bytes
expr_stmt|;
block|}
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|wire_flush (GIOChannel * channel,gpointer user_data)
name|wire_flush
parameter_list|(
name|GIOChannel
modifier|*
name|channel
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
if|if
condition|(
name|wire_flush_func
condition|)
return|return
call|(
modifier|*
name|wire_flush_func
call|)
argument_list|(
name|channel
argument_list|,
name|user_data
argument_list|)
return|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|wire_error (void)
name|wire_error
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|wire_error_val
return|;
block|}
end_function

begin_function
name|void
DECL|function|wire_clear_error (void)
name|wire_clear_error
parameter_list|(
name|void
parameter_list|)
block|{
name|wire_error_val
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|wire_read_msg (GIOChannel * channel,WireMessage * msg,gpointer user_data)
name|wire_read_msg
parameter_list|(
name|GIOChannel
modifier|*
name|channel
parameter_list|,
name|WireMessage
modifier|*
name|msg
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|WireHandler
modifier|*
name|handler
decl_stmt|;
if|if
condition|(
name|wire_error_val
condition|)
return|return
operator|!
name|wire_error_val
return|;
if|if
condition|(
operator|!
name|wire_read_int32
argument_list|(
name|channel
argument_list|,
operator|&
name|msg
operator|->
name|type
argument_list|,
literal|1
argument_list|,
name|user_data
argument_list|)
condition|)
return|return
name|FALSE
return|;
name|handler
operator|=
name|g_hash_table_lookup
argument_list|(
name|wire_ht
argument_list|,
operator|&
name|msg
operator|->
name|type
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|handler
condition|)
name|g_error
argument_list|(
literal|"could not find handler for message: %d"
argument_list|,
name|msg
operator|->
name|type
argument_list|)
expr_stmt|;
call|(
modifier|*
name|handler
operator|->
name|read_func
call|)
argument_list|(
name|channel
argument_list|,
name|msg
argument_list|,
name|user_data
argument_list|)
expr_stmt|;
return|return
operator|!
name|wire_error_val
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|wire_write_msg (GIOChannel * channel,WireMessage * msg,gpointer user_data)
name|wire_write_msg
parameter_list|(
name|GIOChannel
modifier|*
name|channel
parameter_list|,
name|WireMessage
modifier|*
name|msg
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|WireHandler
modifier|*
name|handler
decl_stmt|;
if|if
condition|(
name|wire_error_val
condition|)
return|return
operator|!
name|wire_error_val
return|;
name|handler
operator|=
name|g_hash_table_lookup
argument_list|(
name|wire_ht
argument_list|,
operator|&
name|msg
operator|->
name|type
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|handler
condition|)
name|g_error
argument_list|(
literal|"could not find handler for message: %d"
argument_list|,
name|msg
operator|->
name|type
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|wire_write_int32
argument_list|(
name|channel
argument_list|,
operator|&
name|msg
operator|->
name|type
argument_list|,
literal|1
argument_list|,
name|user_data
argument_list|)
condition|)
return|return
name|FALSE
return|;
call|(
modifier|*
name|handler
operator|->
name|write_func
call|)
argument_list|(
name|channel
argument_list|,
name|msg
argument_list|,
name|user_data
argument_list|)
expr_stmt|;
return|return
operator|!
name|wire_error_val
return|;
block|}
end_function

begin_function
name|void
DECL|function|wire_destroy (WireMessage * msg)
name|wire_destroy
parameter_list|(
name|WireMessage
modifier|*
name|msg
parameter_list|)
block|{
name|WireHandler
modifier|*
name|handler
decl_stmt|;
name|handler
operator|=
name|g_hash_table_lookup
argument_list|(
name|wire_ht
argument_list|,
operator|&
name|msg
operator|->
name|type
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|handler
condition|)
name|g_error
argument_list|(
literal|"could not find handler for message: %d\n"
argument_list|,
name|msg
operator|->
name|type
argument_list|)
expr_stmt|;
call|(
modifier|*
name|handler
operator|->
name|destroy_func
call|)
argument_list|(
name|msg
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|wire_read_int32 (GIOChannel * channel,guint32 * data,gint count,gpointer user_data)
name|wire_read_int32
parameter_list|(
name|GIOChannel
modifier|*
name|channel
parameter_list|,
name|guint32
modifier|*
name|data
parameter_list|,
name|gint
name|count
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
if|if
condition|(
name|count
operator|>
literal|0
condition|)
block|{
if|if
condition|(
operator|!
name|wire_read_int8
argument_list|(
name|channel
argument_list|,
operator|(
name|guint8
operator|*
operator|)
name|data
argument_list|,
name|count
operator|*
literal|4
argument_list|,
name|user_data
argument_list|)
condition|)
return|return
name|FALSE
return|;
while|while
condition|(
name|count
operator|--
condition|)
block|{
operator|*
name|data
operator|=
name|g_ntohl
argument_list|(
operator|*
name|data
argument_list|)
expr_stmt|;
name|data
operator|++
expr_stmt|;
block|}
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|wire_read_int16 (GIOChannel * channel,guint16 * data,gint count,gpointer user_data)
name|wire_read_int16
parameter_list|(
name|GIOChannel
modifier|*
name|channel
parameter_list|,
name|guint16
modifier|*
name|data
parameter_list|,
name|gint
name|count
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
if|if
condition|(
name|count
operator|>
literal|0
condition|)
block|{
if|if
condition|(
operator|!
name|wire_read_int8
argument_list|(
name|channel
argument_list|,
operator|(
name|guint8
operator|*
operator|)
name|data
argument_list|,
name|count
operator|*
literal|2
argument_list|,
name|user_data
argument_list|)
condition|)
return|return
name|FALSE
return|;
while|while
condition|(
name|count
operator|--
condition|)
block|{
operator|*
name|data
operator|=
name|g_ntohs
argument_list|(
operator|*
name|data
argument_list|)
expr_stmt|;
name|data
operator|++
expr_stmt|;
block|}
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|wire_read_int8 (GIOChannel * channel,guint8 * data,gint count,gpointer user_data)
name|wire_read_int8
parameter_list|(
name|GIOChannel
modifier|*
name|channel
parameter_list|,
name|guint8
modifier|*
name|data
parameter_list|,
name|gint
name|count
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
return|return
name|wire_read
argument_list|(
name|channel
argument_list|,
name|data
argument_list|,
name|count
argument_list|,
name|user_data
argument_list|)
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|wire_read_double (GIOChannel * channel,gdouble * data,gint count,gpointer user_data)
name|wire_read_double
parameter_list|(
name|GIOChannel
modifier|*
name|channel
parameter_list|,
name|gdouble
modifier|*
name|data
parameter_list|,
name|gint
name|count
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
DECL|union|__anon29078e72010a
union|union
block|{
DECL|member|d
name|gdouble
name|d
decl_stmt|;
DECL|member|p
name|guint32
name|p
index|[
literal|2
index|]
decl_stmt|;
block|}
name|d
union|;
name|gint
name|i
decl_stmt|;
if|#
directive|if
operator|(
name|G_BYTE_ORDER
operator|==
name|G_LITTLE_ENDIAN
operator|)
name|guint32
name|swap
decl_stmt|;
endif|#
directive|endif
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|count
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
operator|!
name|wire_read_int8
argument_list|(
name|channel
argument_list|,
operator|(
name|guint8
operator|*
operator|)
operator|&
name|d
operator|.
name|d
argument_list|,
literal|8
argument_list|,
name|user_data
argument_list|)
condition|)
return|return
name|FALSE
return|;
if|#
directive|if
operator|(
name|G_BYTE_ORDER
operator|==
name|G_LITTLE_ENDIAN
operator|)
name|swap
operator|=
name|g_ntohl
argument_list|(
name|d
operator|.
name|p
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
name|d
operator|.
name|p
index|[
literal|1
index|]
operator|=
name|g_ntohl
argument_list|(
name|d
operator|.
name|p
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
name|d
operator|.
name|p
index|[
literal|0
index|]
operator|=
name|swap
expr_stmt|;
endif|#
directive|endif
name|data
index|[
name|i
index|]
operator|=
name|d
operator|.
name|d
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|wire_read_string (GIOChannel * channel,gchar ** data,gint count,gpointer user_data)
name|wire_read_string
parameter_list|(
name|GIOChannel
modifier|*
name|channel
parameter_list|,
name|gchar
modifier|*
modifier|*
name|data
parameter_list|,
name|gint
name|count
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|guint32
name|tmp
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
name|count
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
operator|!
name|wire_read_int32
argument_list|(
name|channel
argument_list|,
operator|&
name|tmp
argument_list|,
literal|1
argument_list|,
name|user_data
argument_list|)
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
name|tmp
operator|>
literal|0
condition|)
block|{
name|data
index|[
name|i
index|]
operator|=
name|g_new
argument_list|(
name|gchar
argument_list|,
name|tmp
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|wire_read_int8
argument_list|(
name|channel
argument_list|,
operator|(
name|guint8
operator|*
operator|)
name|data
index|[
name|i
index|]
argument_list|,
name|tmp
argument_list|,
name|user_data
argument_list|)
condition|)
block|{
name|g_free
argument_list|(
name|data
index|[
name|i
index|]
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
block|}
else|else
block|{
name|data
index|[
name|i
index|]
operator|=
name|NULL
expr_stmt|;
block|}
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|wire_write_int32 (GIOChannel * channel,guint32 * data,gint count,gpointer user_data)
name|wire_write_int32
parameter_list|(
name|GIOChannel
modifier|*
name|channel
parameter_list|,
name|guint32
modifier|*
name|data
parameter_list|,
name|gint
name|count
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|guint32
name|tmp
decl_stmt|;
name|gint
name|i
decl_stmt|;
if|if
condition|(
name|count
operator|>
literal|0
condition|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|count
condition|;
name|i
operator|++
control|)
block|{
name|tmp
operator|=
name|g_htonl
argument_list|(
name|data
index|[
name|i
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|wire_write_int8
argument_list|(
name|channel
argument_list|,
operator|(
name|guint8
operator|*
operator|)
operator|&
name|tmp
argument_list|,
literal|4
argument_list|,
name|user_data
argument_list|)
condition|)
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
DECL|function|wire_write_int16 (GIOChannel * channel,guint16 * data,gint count,gpointer user_data)
name|wire_write_int16
parameter_list|(
name|GIOChannel
modifier|*
name|channel
parameter_list|,
name|guint16
modifier|*
name|data
parameter_list|,
name|gint
name|count
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|guint16
name|tmp
decl_stmt|;
name|gint
name|i
decl_stmt|;
if|if
condition|(
name|count
operator|>
literal|0
condition|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|count
condition|;
name|i
operator|++
control|)
block|{
name|tmp
operator|=
name|g_htons
argument_list|(
name|data
index|[
name|i
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|wire_write_int8
argument_list|(
name|channel
argument_list|,
operator|(
name|guint8
operator|*
operator|)
operator|&
name|tmp
argument_list|,
literal|2
argument_list|,
name|user_data
argument_list|)
condition|)
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
DECL|function|wire_write_int8 (GIOChannel * channel,guint8 * data,gint count,gpointer user_data)
name|wire_write_int8
parameter_list|(
name|GIOChannel
modifier|*
name|channel
parameter_list|,
name|guint8
modifier|*
name|data
parameter_list|,
name|gint
name|count
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
return|return
name|wire_write
argument_list|(
name|channel
argument_list|,
name|data
argument_list|,
name|count
argument_list|,
name|user_data
argument_list|)
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|wire_write_double (GIOChannel * channel,gdouble * data,gint count,gpointer user_data)
name|wire_write_double
parameter_list|(
name|GIOChannel
modifier|*
name|channel
parameter_list|,
name|gdouble
modifier|*
name|data
parameter_list|,
name|gint
name|count
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
DECL|union|__anon29078e72020a
union|union
block|{
DECL|member|d
name|gdouble
name|d
decl_stmt|;
DECL|member|p
name|guint32
name|p
index|[
literal|2
index|]
decl_stmt|;
block|}
name|d
union|;
name|gint
name|i
decl_stmt|;
if|#
directive|if
operator|(
name|G_BYTE_ORDER
operator|==
name|G_LITTLE_ENDIAN
operator|)
name|guint32
name|swap
decl_stmt|;
endif|#
directive|endif
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|count
condition|;
name|i
operator|++
control|)
block|{
name|d
operator|.
name|d
operator|=
name|data
index|[
name|i
index|]
expr_stmt|;
if|#
directive|if
operator|(
name|G_BYTE_ORDER
operator|==
name|G_LITTLE_ENDIAN
operator|)
name|swap
operator|=
name|g_htonl
argument_list|(
name|d
operator|.
name|p
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
name|d
operator|.
name|p
index|[
literal|1
index|]
operator|=
name|g_htonl
argument_list|(
name|d
operator|.
name|p
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
name|d
operator|.
name|p
index|[
literal|0
index|]
operator|=
name|swap
expr_stmt|;
endif|#
directive|endif
if|if
condition|(
operator|!
name|wire_write_int8
argument_list|(
name|channel
argument_list|,
operator|(
name|guint8
operator|*
operator|)
operator|&
name|d
operator|.
name|d
argument_list|,
literal|8
argument_list|,
name|user_data
argument_list|)
condition|)
return|return
name|FALSE
return|;
if|#
directive|if
literal|0
block|{ 	gint j;  	g_print ("Wire representation of %f:\t", data[i]);  	for (j = 0; j< 8; j++) 	  { 	    g_print ("%02x ", ((guchar *) tmp)[j]); 	  }  	g_print ("\n");       }
endif|#
directive|endif
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|wire_write_string (GIOChannel * channel,gchar ** data,gint count,gpointer user_data)
name|wire_write_string
parameter_list|(
name|GIOChannel
modifier|*
name|channel
parameter_list|,
name|gchar
modifier|*
modifier|*
name|data
parameter_list|,
name|gint
name|count
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|guint32
name|tmp
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
name|count
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|data
index|[
name|i
index|]
condition|)
name|tmp
operator|=
name|strlen
argument_list|(
name|data
index|[
name|i
index|]
argument_list|)
operator|+
literal|1
expr_stmt|;
else|else
name|tmp
operator|=
literal|0
expr_stmt|;
if|if
condition|(
operator|!
name|wire_write_int32
argument_list|(
name|channel
argument_list|,
operator|&
name|tmp
argument_list|,
literal|1
argument_list|,
name|user_data
argument_list|)
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
name|tmp
operator|>
literal|0
condition|)
if|if
condition|(
operator|!
name|wire_write_int8
argument_list|(
name|channel
argument_list|,
operator|(
name|guint8
operator|*
operator|)
name|data
index|[
name|i
index|]
argument_list|,
name|tmp
argument_list|,
name|user_data
argument_list|)
condition|)
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
name|void
DECL|function|wire_init (void)
name|wire_init
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
operator|!
name|wire_ht
condition|)
block|{
name|wire_ht
operator|=
name|g_hash_table_new
argument_list|(
operator|(
name|GHashFunc
operator|)
name|wire_hash
argument_list|,
operator|(
name|GCompareFunc
operator|)
name|wire_compare
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|guint
DECL|function|wire_hash (guint32 * key)
name|wire_hash
parameter_list|(
name|guint32
modifier|*
name|key
parameter_list|)
block|{
return|return
operator|*
name|key
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|wire_compare (guint32 * a,guint32 * b)
name|wire_compare
parameter_list|(
name|guint32
modifier|*
name|a
parameter_list|,
name|guint32
modifier|*
name|b
parameter_list|)
block|{
return|return
operator|(
operator|*
name|a
operator|==
operator|*
name|b
operator|)
return|;
block|}
end_function

end_unit

