begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<libgnomevfs/gnome-vfs.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_GNOMEUI
end_ifdef

begin_include
include|#
directive|include
file|<libgnomeui/gnome-authentication-manager.h>
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
file|"libgimp/stdplugins-intl.h"
end_include

begin_define
DECL|macro|BUFSIZE
define|#
directive|define
name|BUFSIZE
value|4096
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

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
specifier|const
name|gchar
modifier|*
name|copying_format_str
parameter_list|,
specifier|const
name|gchar
modifier|*
name|copied_format_str
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  private variables  */
end_comment

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

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|gboolean
DECL|function|uri_backend_init (GError ** error)
name|uri_backend_init
parameter_list|(
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
if|if
condition|(
operator|!
name|gnome_vfs_init
argument_list|()
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
literal|"Could not initialize GnomeVFS"
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
ifdef|#
directive|ifdef
name|HAVE_GNOMEUI
name|gnome_authentication_manager_init
argument_list|()
expr_stmt|;
endif|#
directive|endif
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
block|{
name|gnome_vfs_shutdown
argument_list|()
expr_stmt|;
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
decl_stmt|;
name|gboolean
name|success
decl_stmt|;
name|dest_uri
operator|=
name|g_filename_to_uri
argument_list|(
name|tmpname
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|success
operator|=
name|copy_uri
argument_list|(
name|uri
argument_list|,
name|dest_uri
argument_list|,
name|_
argument_list|(
literal|"Downloading %s of image data..."
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Downloaded %s of image data"
argument_list|)
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|dest_uri
argument_list|)
expr_stmt|;
return|return
name|success
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
decl_stmt|;
name|gboolean
name|success
decl_stmt|;
name|src_uri
operator|=
name|g_filename_to_uri
argument_list|(
name|tmpname
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|success
operator|=
name|copy_uri
argument_list|(
name|src_uri
argument_list|,
name|uri
argument_list|,
name|_
argument_list|(
literal|"Uploading %s of image data..."
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Uploaded %s of image data"
argument_list|)
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|src_uri
argument_list|)
expr_stmt|;
return|return
name|success
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
specifier|static
specifier|const
name|gchar
modifier|*
name|protocols
index|[]
init|=
block|{
literal|"http:"
block|,
literal|"https:"
block|,
literal|"ftp:"
block|,
literal|"sftp:"
block|,
literal|"ssh:"
block|,
literal|"smb:"
block|,
literal|"dav:"
block|,
literal|"davs:"
block|}
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
name|protocols
argument_list|)
condition|;
name|i
operator|++
control|)
block|{
name|gchar
modifier|*
name|uri
decl_stmt|;
name|GnomeVFSURI
modifier|*
name|vfs_uri
decl_stmt|;
name|uri
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s//foo/bar.xcf"
argument_list|,
name|protocols
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|vfs_uri
operator|=
name|gnome_vfs_uri_new
argument_list|(
name|uri
argument_list|)
expr_stmt|;
if|if
condition|(
name|vfs_uri
condition|)
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
name|protocols
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|gnome_vfs_uri_unref
argument_list|(
name|vfs_uri
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|uri
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

begin_function
specifier|static
name|gboolean
DECL|function|copy_uri (const gchar * src_uri,const gchar * dest_uri,const gchar * copying_format_str,const gchar * copied_format_str,GError ** error)
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
specifier|const
name|gchar
modifier|*
name|copying_format_str
parameter_list|,
specifier|const
name|gchar
modifier|*
name|copied_format_str
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GnomeVFSHandle
modifier|*
name|read_handle
decl_stmt|;
name|GnomeVFSHandle
modifier|*
name|write_handle
decl_stmt|;
name|GnomeVFSFileInfo
modifier|*
name|src_info
decl_stmt|;
name|GnomeVFSFileSize
name|file_size
init|=
literal|0
decl_stmt|;
name|GnomeVFSFileSize
name|bytes_read
init|=
literal|0
decl_stmt|;
name|guchar
name|buffer
index|[
name|BUFSIZE
index|]
decl_stmt|;
name|GnomeVFSResult
name|result
decl_stmt|;
name|gchar
modifier|*
name|memsize
decl_stmt|;
name|gchar
modifier|*
name|message
decl_stmt|;
name|GTimeVal
name|last_time
init|=
block|{
literal|0
block|,
literal|0
block|}
decl_stmt|;
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Connecting to server..."
argument_list|)
argument_list|)
expr_stmt|;
name|src_info
operator|=
name|gnome_vfs_file_info_new
argument_list|()
expr_stmt|;
name|result
operator|=
name|gnome_vfs_get_file_info
argument_list|(
name|src_uri
argument_list|,
name|src_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/*  ignore errors here, they will be noticed below  */
if|if
condition|(
name|result
operator|==
name|GNOME_VFS_OK
operator|&&
operator|(
name|src_info
operator|->
name|valid_fields
operator|&
name|GNOME_VFS_FILE_INFO_FIELDS_SIZE
operator|)
condition|)
block|{
name|file_size
operator|=
name|src_info
operator|->
name|size
expr_stmt|;
block|}
name|gnome_vfs_file_info_unref
argument_list|(
name|src_info
argument_list|)
expr_stmt|;
name|result
operator|=
name|gnome_vfs_open
argument_list|(
operator|&
name|read_handle
argument_list|,
name|src_uri
argument_list|,
name|GNOME_VFS_OPEN_READ
argument_list|)
expr_stmt|;
if|if
condition|(
name|result
operator|!=
name|GNOME_VFS_OK
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
literal|"Could not open '%s' for reading: %s"
argument_list|)
argument_list|,
name|src_uri
argument_list|,
name|gnome_vfs_result_to_string
argument_list|(
name|result
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|result
operator|=
name|gnome_vfs_create
argument_list|(
operator|&
name|write_handle
argument_list|,
name|dest_uri
argument_list|,
name|GNOME_VFS_OPEN_WRITE
argument_list|,
name|FALSE
argument_list|,
literal|0644
argument_list|)
expr_stmt|;
if|if
condition|(
name|result
operator|!=
name|GNOME_VFS_OK
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
literal|"Could not open '%s' for writing: %s"
argument_list|)
argument_list|,
name|dest_uri
argument_list|,
name|gnome_vfs_result_to_string
argument_list|(
name|result
argument_list|)
argument_list|)
expr_stmt|;
name|gnome_vfs_close
argument_list|(
name|read_handle
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|memsize
operator|=
name|gimp_memsize_to_string
argument_list|(
name|file_size
argument_list|)
expr_stmt|;
name|gimp_progress_init_printf
argument_list|(
name|file_size
operator|>
literal|0
condition|?
name|copying_format_str
else|:
name|copied_format_str
argument_list|,
name|memsize
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|memsize
argument_list|)
expr_stmt|;
while|while
condition|(
name|TRUE
condition|)
block|{
name|GnomeVFSFileSize
name|chunk_read
decl_stmt|;
name|GnomeVFSFileSize
name|chunk_written
decl_stmt|;
name|GTimeVal
name|now
decl_stmt|;
name|result
operator|=
name|gnome_vfs_read
argument_list|(
name|read_handle
argument_list|,
name|buffer
argument_list|,
sizeof|sizeof
argument_list|(
name|buffer
argument_list|)
argument_list|,
operator|&
name|chunk_read
argument_list|)
expr_stmt|;
if|if
condition|(
name|chunk_read
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|result
operator|!=
name|GNOME_VFS_ERROR_EOF
condition|)
block|{
name|memsize
operator|=
name|gimp_memsize_to_string
argument_list|(
sizeof|sizeof
argument_list|(
name|buffer
argument_list|)
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
name|_
argument_list|(
literal|"Failed to read %s from '%s': %s"
argument_list|)
argument_list|,
name|memsize
argument_list|,
name|src_uri
argument_list|,
name|gnome_vfs_result_to_string
argument_list|(
name|result
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|memsize
argument_list|)
expr_stmt|;
name|gnome_vfs_close
argument_list|(
name|read_handle
argument_list|)
expr_stmt|;
name|gnome_vfs_close
argument_list|(
name|write_handle
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
else|else
block|{
name|gimp_progress_update
argument_list|(
literal|1.0
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
name|bytes_read
operator|+=
name|chunk_read
expr_stmt|;
comment|/*  update the progress only up to 10 times a second  */
name|g_get_current_time
argument_list|(
operator|&
name|now
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
operator|(
name|now
operator|.
name|tv_sec
operator|-
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
name|last_time
operator|.
name|tv_usec
operator|)
operator|/
literal|1000
operator|)
operator|>
literal|100
condition|)
block|{
if|if
condition|(
name|file_size
operator|>
literal|0
condition|)
block|{
name|gimp_progress_update
argument_list|(
operator|(
name|gdouble
operator|)
name|bytes_read
operator|/
operator|(
name|gdouble
operator|)
name|file_size
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|memsize
operator|=
name|gimp_memsize_to_string
argument_list|(
name|bytes_read
argument_list|)
expr_stmt|;
name|message
operator|=
name|g_strdup_printf
argument_list|(
name|copied_format_str
argument_list|,
name|memsize
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|memsize
argument_list|)
expr_stmt|;
name|gimp_progress_set_text
argument_list|(
name|message
argument_list|)
expr_stmt|;
name|gimp_progress_pulse
argument_list|()
expr_stmt|;
name|g_free
argument_list|(
name|message
argument_list|)
expr_stmt|;
block|}
name|last_time
operator|=
name|now
expr_stmt|;
block|}
name|result
operator|=
name|gnome_vfs_write
argument_list|(
name|write_handle
argument_list|,
name|buffer
argument_list|,
name|chunk_read
argument_list|,
operator|&
name|chunk_written
argument_list|)
expr_stmt|;
if|if
condition|(
name|chunk_written
operator|<
name|chunk_read
condition|)
block|{
name|memsize
operator|=
name|gimp_memsize_to_string
argument_list|(
name|chunk_read
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
name|_
argument_list|(
literal|"Failed to write %s to '%s': %s"
argument_list|)
argument_list|,
name|memsize
argument_list|,
name|dest_uri
argument_list|,
name|gnome_vfs_result_to_string
argument_list|(
name|result
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|memsize
argument_list|)
expr_stmt|;
name|gnome_vfs_close
argument_list|(
name|read_handle
argument_list|)
expr_stmt|;
name|gnome_vfs_close
argument_list|(
name|write_handle
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
block|}
name|gnome_vfs_close
argument_list|(
name|read_handle
argument_list|)
expr_stmt|;
name|gnome_vfs_close
argument_list|(
name|write_handle
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

end_unit

