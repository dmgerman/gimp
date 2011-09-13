begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * libcurl backend for the URI plug-in  * Copyright (C) 2006 Mukund Sivaraman<muks@mukund.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<curl/curl.h>
end_include

begin_include
include|#
directive|include
file|<curl/easy.h>
end_include

begin_include
include|#
directive|include
file|<glib/gstdio.h>
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

begin_decl_stmt
DECL|variable|user_agent
specifier|static
name|gchar
modifier|*
name|user_agent
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

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
name|GString
modifier|*
name|protocols
decl_stmt|;
name|curl_version_info_data
modifier|*
name|vinfo
decl_stmt|;
if|if
condition|(
name|curl_global_init
argument_list|(
name|CURL_GLOBAL_ALL
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
literal|"%s"
argument_list|,
name|_
argument_list|(
literal|"Could not initialize libcurl"
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|vinfo
operator|=
name|curl_version_info
argument_list|(
name|CURLVERSION_NOW
argument_list|)
expr_stmt|;
name|protocols
operator|=
name|g_string_new
argument_list|(
literal|"http:,ftp:,gopher:"
argument_list|)
expr_stmt|;
if|if
condition|(
name|vinfo
operator|->
name|features
operator|&
name|CURL_VERSION_SSL
condition|)
block|{
name|g_string_append
argument_list|(
name|protocols
argument_list|,
literal|",https:,ftps:"
argument_list|)
expr_stmt|;
block|}
name|supported_protocols
operator|=
name|g_string_free
argument_list|(
name|protocols
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|user_agent
operator|=
name|g_strconcat
argument_list|(
literal|"GIMP/"
argument_list|,
name|GIMP_VERSION
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
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
name|g_free
argument_list|(
name|user_agent
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|supported_protocols
argument_list|)
expr_stmt|;
name|curl_global_cleanup
argument_list|()
expr_stmt|;
block|}
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
literal|"Loads a file using the libcurl file transfer library"
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
name|NULL
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
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|int
DECL|function|progress_callback (void * clientp,double dltotal,double dlnow,double ultotal,double ulnow)
name|progress_callback
parameter_list|(
name|void
modifier|*
name|clientp
parameter_list|,
name|double
name|dltotal
parameter_list|,
name|double
name|dlnow
parameter_list|,
name|double
name|ultotal
parameter_list|,
name|double
name|ulnow
parameter_list|)
block|{
name|gchar
modifier|*
name|memsize
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|dltotal
operator|>
literal|0.0
condition|)
block|{
name|memsize
operator|=
name|g_format_size
argument_list|(
name|dltotal
argument_list|)
expr_stmt|;
name|gimp_progress_set_text_printf
argument_list|(
name|_
argument_list|(
literal|"Downloading %s of image data"
argument_list|)
argument_list|,
name|memsize
argument_list|)
expr_stmt|;
name|gimp_progress_update
argument_list|(
name|dlnow
operator|/
name|dltotal
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|memsize
operator|=
name|g_format_size
argument_list|(
name|dlnow
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
block|}
name|g_free
argument_list|(
name|memsize
argument_list|)
expr_stmt|;
return|return
literal|0
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
name|FILE
modifier|*
name|out_file
decl_stmt|;
name|CURL
modifier|*
name|curl_handle
decl_stmt|;
name|CURLcode
name|result
decl_stmt|;
name|glong
name|response_code
decl_stmt|;
name|gchar
modifier|*
name|eff_url
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|proto
init|=
name|NULL
decl_stmt|;
name|gboolean
name|is_http
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|is_ftp
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|is_gopher
init|=
name|FALSE
decl_stmt|;
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Connecting to server"
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|out_file
operator|=
name|g_fopen
argument_list|(
name|tmpname
argument_list|,
literal|"wb"
argument_list|)
operator|)
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
name|tmpname
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
name|curl_handle
operator|=
name|curl_easy_init
argument_list|()
expr_stmt|;
name|curl_easy_setopt
argument_list|(
name|curl_handle
argument_list|,
name|CURLOPT_URL
argument_list|,
name|uri
argument_list|)
expr_stmt|;
name|curl_easy_setopt
argument_list|(
name|curl_handle
argument_list|,
name|CURLOPT_WRITEDATA
argument_list|,
name|out_file
argument_list|)
expr_stmt|;
name|curl_easy_setopt
argument_list|(
name|curl_handle
argument_list|,
name|CURLOPT_PROGRESSFUNCTION
argument_list|,
name|progress_callback
argument_list|)
expr_stmt|;
name|curl_easy_setopt
argument_list|(
name|curl_handle
argument_list|,
name|CURLOPT_NOPROGRESS
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|curl_easy_setopt
argument_list|(
name|curl_handle
argument_list|,
name|CURLOPT_USERAGENT
argument_list|,
name|user_agent
argument_list|)
expr_stmt|;
name|curl_easy_setopt
argument_list|(
name|curl_handle
argument_list|,
name|CURLOPT_FOLLOWLOCATION
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|curl_easy_setopt
argument_list|(
name|curl_handle
argument_list|,
name|CURLOPT_MAXREDIRS
argument_list|,
literal|10
argument_list|)
expr_stmt|;
name|curl_easy_setopt
argument_list|(
name|curl_handle
argument_list|,
name|CURLOPT_SSL_VERIFYPEER
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/* the following empty string causes libcurl to send a list of    * all supported encodings which turns on compression    * if libcurl has support for compression    */
name|curl_easy_setopt
argument_list|(
name|curl_handle
argument_list|,
name|CURLOPT_ENCODING
argument_list|,
literal|""
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|result
operator|=
name|curl_easy_perform
argument_list|(
name|curl_handle
argument_list|)
operator|)
operator|!=
literal|0
condition|)
block|{
name|fclose
argument_list|(
name|out_file
argument_list|)
expr_stmt|;
name|g_set_error
argument_list|(
name|error
argument_list|,
name|G_FILE_ERROR
argument_list|,
name|G_FILE_ERROR_FAILED
argument_list|,
name|_
argument_list|(
literal|"Could not open '%s' for reading: %s"
argument_list|)
argument_list|,
name|uri
argument_list|,
name|curl_easy_strerror
argument_list|(
name|result
argument_list|)
argument_list|)
expr_stmt|;
name|curl_easy_cleanup
argument_list|(
name|curl_handle
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|curl_easy_getinfo
argument_list|(
name|curl_handle
argument_list|,
name|CURLINFO_RESPONSE_CODE
argument_list|,
operator|&
name|response_code
argument_list|)
expr_stmt|;
comment|/* protocol could be not specified in provided uri      get complete url guessed by curl */
name|curl_easy_getinfo
argument_list|(
name|curl_handle
argument_list|,
name|CURLINFO_EFFECTIVE_URL
argument_list|,
operator|&
name|eff_url
argument_list|)
expr_stmt|;
comment|/* detect uri protocol */
if|if
condition|(
operator|!
name|g_ascii_strncasecmp
argument_list|(
name|eff_url
argument_list|,
literal|"http://"
argument_list|,
literal|7
argument_list|)
condition|)
block|{
name|is_http
operator|=
name|TRUE
expr_stmt|;
name|proto
operator|=
literal|"HTTP"
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|g_ascii_strncasecmp
argument_list|(
name|eff_url
argument_list|,
literal|"https://"
argument_list|,
literal|8
argument_list|)
condition|)
block|{
name|is_http
operator|=
name|TRUE
expr_stmt|;
name|proto
operator|=
literal|"HTTPS"
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|g_ascii_strncasecmp
argument_list|(
name|eff_url
argument_list|,
literal|"ftp://"
argument_list|,
literal|6
argument_list|)
condition|)
block|{
name|is_ftp
operator|=
name|TRUE
expr_stmt|;
name|proto
operator|=
literal|"FTP"
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|g_ascii_strncasecmp
argument_list|(
name|eff_url
argument_list|,
literal|"ftps://"
argument_list|,
literal|7
argument_list|)
condition|)
block|{
name|is_ftp
operator|=
name|TRUE
expr_stmt|;
name|proto
operator|=
literal|"FTPS"
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|g_ascii_strncasecmp
argument_list|(
name|eff_url
argument_list|,
literal|"gopher://"
argument_list|,
literal|9
argument_list|)
condition|)
block|{
name|is_gopher
operator|=
name|TRUE
expr_stmt|;
name|proto
operator|=
literal|"GOPHER"
expr_stmt|;
block|}
else|else
block|{
name|proto
operator|=
literal|"UNKNOWN"
expr_stmt|;
block|}
if|if
condition|(
operator|!
operator|(
operator|(
name|is_http
operator|&&
name|response_code
operator|==
literal|200
operator|)
operator|||
operator|(
name|is_ftp
operator|&&
name|response_code
operator|==
literal|226
operator|)
operator|||
operator|(
name|is_gopher
operator|)
operator|)
condition|)
block|{
name|fclose
argument_list|(
name|out_file
argument_list|)
expr_stmt|;
name|g_set_error
argument_list|(
name|error
argument_list|,
name|G_FILE_ERROR
argument_list|,
name|G_FILE_ERROR_FAILED
argument_list|,
name|_
argument_list|(
literal|"Opening '%s' for reading resulted in %s "
literal|"response code: %ld"
argument_list|)
argument_list|,
name|uri
argument_list|,
name|proto
argument_list|,
name|response_code
argument_list|)
expr_stmt|;
name|curl_easy_cleanup
argument_list|(
name|curl_handle
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|fclose
argument_list|(
name|out_file
argument_list|)
expr_stmt|;
name|gimp_progress_update
argument_list|(
literal|1.0
argument_list|)
expr_stmt|;
name|curl_easy_cleanup
argument_list|(
name|curl_handle
argument_list|)
expr_stmt|;
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
name|G_FILE_ERROR
argument_list|,
name|G_FILE_ERROR_FAILED
argument_list|,
literal|"not implemented"
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|uri_backend_map_image (const gchar * uri,GimpRunMode run_mode)
name|uri_backend_map_image
parameter_list|(
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
name|GimpRunMode
name|run_mode
parameter_list|)
block|{
return|return
name|NULL
return|;
block|}
end_function

end_unit

