begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * URI plug-in, GIO/GVfs backend  * Copyright (C) 2008  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"uri-backend.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c59ead00103
block|{
DECL|enumerator|DOWNLOAD
name|DOWNLOAD
block|,
DECL|enumerator|UPLOAD
name|UPLOAD
DECL|typedef|Mode
block|}
name|Mode
typedef|;
end_typedef

begin_function_decl
specifier|static
name|gchar
modifier|*
name|get_protocols
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|copy_uri
parameter_list|(
specifier|const
name|gchar
modifier|*
name|src_uri
parameter_list|,
specifier|const
name|gchar
modifier|*
name|dest_uri
parameter_list|,
name|Mode
name|mode
parameter_list|,
name|GimpRunMode
name|run_mode
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|supported_protocols
specifier|static
name|gchar
modifier|*
name|supported_protocols
init|=
name|NULL
decl_stmt|;
end_decl_stmt

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
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
condition|)
block|{
name|gimp_ui_init
argument_list|(
name|plugin_name
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
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
DECL|function|uri_backend_get_load_help (void)
name|uri_backend_get_load_help
parameter_list|(
name|void
parameter_list|)
block|{
return|return
literal|"Loads a file using the GIO Virtual File System"
return|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|uri_backend_get_save_help (void)
name|uri_backend_get_save_help
parameter_list|(
name|void
parameter_list|)
block|{
return|return
literal|"Saves a file using the GIO Virtual File System"
return|;
block|}
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
if|if
condition|(
operator|!
name|supported_protocols
condition|)
name|supported_protocols
operator|=
name|get_protocols
argument_list|()
expr_stmt|;
return|return
name|supported_protocols
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
if|if
condition|(
operator|!
name|supported_protocols
condition|)
name|supported_protocols
operator|=
name|get_protocols
argument_list|()
expr_stmt|;
return|return
name|supported_protocols
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
name|gchar
modifier|*
name|dest_uri
init|=
name|g_filename_to_uri
argument_list|(
name|tmpname
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
decl_stmt|;
if|if
condition|(
name|dest_uri
condition|)
block|{
name|gboolean
name|success
init|=
name|copy_uri
argument_list|(
name|uri
argument_list|,
name|dest_uri
argument_list|,
name|DOWNLOAD
argument_list|,
name|run_mode
argument_list|,
name|error
argument_list|)
decl_stmt|;
name|g_free
argument_list|(
name|dest_uri
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
return|return
name|FALSE
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
name|gchar
modifier|*
name|src_uri
init|=
name|g_filename_to_uri
argument_list|(
name|tmpname
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
decl_stmt|;
if|if
condition|(
name|src_uri
condition|)
block|{
name|gboolean
name|success
init|=
name|copy_uri
argument_list|(
name|src_uri
argument_list|,
name|uri
argument_list|,
name|UPLOAD
argument_list|,
name|run_mode
argument_list|,
name|error
argument_list|)
decl_stmt|;
name|g_free
argument_list|(
name|src_uri
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|get_protocols (void)
name|get_protocols
parameter_list|(
name|void
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
specifier|const
modifier|*
name|schemes
decl_stmt|;
name|GString
modifier|*
name|string
init|=
name|g_string_new
argument_list|(
name|NULL
argument_list|)
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|schemes
operator|=
name|g_vfs_get_supported_uri_schemes
argument_list|(
name|g_vfs_get_default
argument_list|()
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|schemes
operator|&&
name|schemes
index|[
name|i
index|]
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|string
operator|->
name|len
operator|>
literal|0
condition|)
name|g_string_append_c
argument_list|(
name|string
argument_list|,
literal|','
argument_list|)
expr_stmt|;
name|g_string_append
argument_list|(
name|string
argument_list|,
name|schemes
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|g_string_append_c
argument_list|(
name|string
argument_list|,
literal|':'
argument_list|)
expr_stmt|;
block|}
return|return
name|g_string_free
argument_list|(
name|string
argument_list|,
name|FALSE
argument_list|)
return|;
block|}
end_function

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c59ead00208
block|{
DECL|member|mode
name|Mode
name|mode
decl_stmt|;
DECL|member|last_time
name|GTimeVal
name|last_time
decl_stmt|;
DECL|typedef|UriProgress
block|}
name|UriProgress
typedef|;
end_typedef

begin_function
specifier|static
name|void
DECL|function|uri_progress_callback (goffset current_num_bytes,goffset total_num_bytes,gpointer user_data)
name|uri_progress_callback
parameter_list|(
name|goffset
name|current_num_bytes
parameter_list|,
name|goffset
name|total_num_bytes
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|UriProgress
modifier|*
name|progress
init|=
name|user_data
decl_stmt|;
name|GTimeVal
name|now
decl_stmt|;
comment|/*  update the progress only up to 10 times a second  */
name|g_get_current_time
argument_list|(
operator|&
name|now
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
operator|->
name|last_time
operator|.
name|tv_sec
operator|&&
operator|(
operator|(
name|now
operator|.
name|tv_sec
operator|-
name|progress
operator|->
name|last_time
operator|.
name|tv_sec
operator|)
operator|*
literal|1000
operator|+
operator|(
name|now
operator|.
name|tv_usec
operator|-
name|progress
operator|->
name|last_time
operator|.
name|tv_usec
operator|)
operator|/
literal|1000
operator|)
operator|<
literal|100
condition|)
return|return;
name|progress
operator|->
name|last_time
operator|=
name|now
expr_stmt|;
if|if
condition|(
name|total_num_bytes
operator|>
literal|0
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|format
decl_stmt|;
name|gchar
modifier|*
name|done
init|=
name|g_format_size_for_display
argument_list|(
name|current_num_bytes
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|total
init|=
name|g_format_size_for_display
argument_list|(
name|total_num_bytes
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|progress
operator|->
name|mode
condition|)
block|{
case|case
name|DOWNLOAD
case|:
name|format
operator|=
name|_
argument_list|(
literal|"Downloading image (%s of %s)"
argument_list|)
expr_stmt|;
break|break;
case|case
name|UPLOAD
case|:
name|format
operator|=
name|_
argument_list|(
literal|"Uploading image (%s of %s)"
argument_list|)
expr_stmt|;
break|break;
default|default:
name|g_assert_not_reached
argument_list|()
expr_stmt|;
block|}
name|gimp_progress_set_text_printf
argument_list|(
name|format
argument_list|,
name|done
argument_list|,
name|total
argument_list|)
expr_stmt|;
name|gimp_progress_update
argument_list|(
operator|(
name|gdouble
operator|)
name|current_num_bytes
operator|/
operator|(
name|gdouble
operator|)
name|total_num_bytes
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|total
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|done
argument_list|)
expr_stmt|;
block|}
else|else
block|{
specifier|const
name|gchar
modifier|*
name|format
decl_stmt|;
name|gchar
modifier|*
name|done
init|=
name|g_format_size_for_display
argument_list|(
name|current_num_bytes
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|progress
operator|->
name|mode
condition|)
block|{
case|case
name|DOWNLOAD
case|:
name|format
operator|=
name|_
argument_list|(
literal|"Downloaded %s of image data"
argument_list|)
expr_stmt|;
break|break;
case|case
name|UPLOAD
case|:
name|format
operator|=
name|_
argument_list|(
literal|"Uploaded %s of image data"
argument_list|)
expr_stmt|;
break|break;
default|default:
name|g_assert_not_reached
argument_list|()
expr_stmt|;
block|}
name|gimp_progress_set_text_printf
argument_list|(
name|format
argument_list|,
name|done
argument_list|)
expr_stmt|;
name|gimp_progress_pulse
argument_list|()
expr_stmt|;
name|g_free
argument_list|(
name|done
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|mount_volume_ready (GFile * file,GAsyncResult * res,GError ** error)
name|mount_volume_ready
parameter_list|(
name|GFile
modifier|*
name|file
parameter_list|,
name|GAsyncResult
modifier|*
name|res
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|g_file_mount_enclosing_volume_finish
argument_list|(
name|file
argument_list|,
name|res
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|gtk_main_quit
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|mount_enclosing_volume (GFile * file,GError ** error)
name|mount_enclosing_volume
parameter_list|(
name|GFile
modifier|*
name|file
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GMountOperation
modifier|*
name|operation
init|=
name|gtk_mount_operation_new
argument_list|(
name|NULL
argument_list|)
decl_stmt|;
name|g_file_mount_enclosing_volume
argument_list|(
name|file
argument_list|,
name|G_MOUNT_MOUNT_NONE
argument_list|,
name|operation
argument_list|,
name|NULL
argument_list|,
operator|(
name|GAsyncReadyCallback
operator|)
name|mount_volume_ready
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|gtk_main
argument_list|()
expr_stmt|;
name|g_object_unref
argument_list|(
name|operation
argument_list|)
expr_stmt|;
return|return
operator|(
operator|*
name|error
operator|==
name|NULL
operator|)
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|copy_uri (const gchar * src_uri,const gchar * dest_uri,Mode mode,GimpRunMode run_mode,GError ** error)
name|copy_uri
parameter_list|(
specifier|const
name|gchar
modifier|*
name|src_uri
parameter_list|,
specifier|const
name|gchar
modifier|*
name|dest_uri
parameter_list|,
name|Mode
name|mode
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
name|GVfs
modifier|*
name|vfs
decl_stmt|;
name|GFile
modifier|*
name|src_file
decl_stmt|;
name|GFile
modifier|*
name|dest_file
decl_stmt|;
name|UriProgress
name|progress
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|gboolean
name|success
decl_stmt|;
name|vfs
operator|=
name|g_vfs_get_default
argument_list|()
expr_stmt|;
if|if
condition|(
operator|!
name|g_vfs_is_active
argument_list|(
name|vfs
argument_list|)
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|G_FILE_ERROR
argument_list|,
name|G_FILE_ERROR_FAILED
argument_list|,
literal|"Initialization of GVfs failed"
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|src_file
operator|=
name|g_vfs_get_file_for_uri
argument_list|(
name|vfs
argument_list|,
name|src_uri
argument_list|)
expr_stmt|;
name|dest_file
operator|=
name|g_vfs_get_file_for_uri
argument_list|(
name|vfs
argument_list|,
name|dest_uri
argument_list|)
expr_stmt|;
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Connecting to server"
argument_list|)
argument_list|)
expr_stmt|;
name|progress
operator|.
name|mode
operator|=
name|mode
expr_stmt|;
name|success
operator|=
name|g_file_copy
argument_list|(
name|src_file
argument_list|,
name|dest_file
argument_list|,
name|G_FILE_COPY_OVERWRITE
argument_list|,
name|NULL
argument_list|,
name|uri_progress_callback
argument_list|,
operator|&
name|progress
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|success
operator|&&
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
operator|&&
operator|(
operator|*
name|error
operator|)
operator|->
name|domain
operator|==
name|G_IO_ERROR
operator|&&
operator|(
operator|*
name|error
operator|)
operator|->
name|code
operator|==
name|G_IO_ERROR_NOT_MOUNTED
condition|)
block|{
name|g_clear_error
argument_list|(
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|mount_enclosing_volume
argument_list|(
name|mode
operator|==
name|DOWNLOAD
condition|?
name|src_file
else|:
name|dest_file
argument_list|,
name|error
argument_list|)
condition|)
block|{
name|success
operator|=
name|g_file_copy
argument_list|(
name|src_file
argument_list|,
name|dest_file
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|uri_progress_callback
argument_list|,
operator|&
name|progress
argument_list|,
name|error
argument_list|)
expr_stmt|;
block|}
block|}
name|g_object_unref
argument_list|(
name|src_file
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|dest_file
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

end_unit

