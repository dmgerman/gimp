begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Web Browser Plug-in  * Copyright (C) 2003  Henrik Brix Andersen<brix@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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

begin_comment
comment|/* strlen, strstr */
end_comment

begin_include
include|#
directive|include
file|<glib.h>
end_include

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

begin_define
DECL|macro|PLUG_IN_NAME
define|#
directive|define
name|PLUG_IN_NAME
value|"plug_in_web_browser"
end_define

begin_function_decl
specifier|static
name|void
name|query
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|run
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
specifier|const
name|GimpParam
modifier|*
name|param
parameter_list|,
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
name|GimpParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|browser_open_url
parameter_list|(
specifier|const
name|gchar
modifier|*
name|url
parameter_list|)
function_decl|;
end_function_decl

begin_ifndef
ifndef|#
directive|ifndef
name|G_OS_WIN32
end_ifndef

begin_function_decl
specifier|static
name|gchar
modifier|*
name|strreplace
parameter_list|(
specifier|const
name|gchar
modifier|*
name|string
parameter_list|,
specifier|const
name|gchar
modifier|*
name|delimiter
parameter_list|,
specifier|const
name|gchar
modifier|*
name|replacement
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_decl_stmt
DECL|variable|PLUG_IN_INFO
name|GimpPlugInInfo
name|PLUG_IN_INFO
init|=
block|{
name|NULL
block|,
comment|/* init_proc  */
name|NULL
block|,
comment|/* quit_proc  */
name|query
block|,
comment|/* query_proc */
name|run
comment|/* run_proc   */
block|}
decl_stmt|;
end_decl_stmt

begin_macro
DECL|function|MAIN ()
name|MAIN
argument_list|()
end_macro

begin_function
specifier|static
name|void
name|query
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GimpParamDef
name|args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"url"
block|,
literal|"URL to open"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
name|PLUG_IN_NAME
argument_list|,
literal|"Open an URL in the user specified web browser"
argument_list|,
literal|"Opens the given URL in the user specified web browser."
argument_list|,
literal|"Henrik Brix Andersen<brix@gimp.org>"
argument_list|,
literal|"2003"
argument_list|,
literal|"2003/09/16"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|args
argument_list|)
argument_list|,
literal|0
argument_list|,
name|args
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|run (const gchar * name,gint nparams,const GimpParam * param,gint * nreturn_vals,GimpParam ** return_vals)
name|run
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
specifier|const
name|GimpParam
modifier|*
name|param
parameter_list|,
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
name|GimpParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
block|{
specifier|static
name|GimpParam
name|values
index|[
literal|1
index|]
decl_stmt|;
name|GimpRunMode
name|run_mode
decl_stmt|;
name|GimpPDBStatusType
name|status
decl_stmt|;
name|run_mode
operator|=
name|param
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|status
operator|=
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|INIT_I18N
argument_list|()
expr_stmt|;
if|if
condition|(
name|nparams
operator|==
literal|1
operator|&&
name|param
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_string
operator|!=
name|NULL
operator|&&
name|strlen
argument_list|(
name|param
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
condition|)
block|{
if|if
condition|(
operator|!
name|browser_open_url
argument_list|(
name|param
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
condition|)
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
block|}
else|else
block|{
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
block|}
operator|*
name|nreturn_vals
operator|=
literal|1
expr_stmt|;
operator|*
name|return_vals
operator|=
name|values
expr_stmt|;
name|values
index|[
literal|0
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_STATUS
expr_stmt|;
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|status
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|browser_open_url (const gchar * url)
name|browser_open_url
parameter_list|(
specifier|const
name|gchar
modifier|*
name|url
parameter_list|)
block|{
ifdef|#
directive|ifdef
name|G_OS_WIN32
return|return
operator|(
operator|(
name|gint
operator|)
name|ShellExecute
argument_list|(
name|HWND_DESKTOP
argument_list|,
literal|"open"
argument_list|,
name|url
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|SW_SHOWNORMAL
argument_list|)
operator|>
literal|32
operator|)
return|;
else|#
directive|else
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|browser
decl_stmt|;
name|gchar
modifier|*
name|cmd
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|argv
decl_stmt|;
name|gboolean
name|retval
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|url
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|browser
operator|=
name|gimp_gimprc_query
argument_list|(
literal|"web-browser"
argument_list|)
expr_stmt|;
if|if
condition|(
name|browser
operator|==
name|NULL
operator|||
operator|!
name|strlen
argument_list|(
name|browser
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Web browser not specified.\n"
literal|"Please specify a web browser using the Preferences Dialog."
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|browser
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
comment|/* replace %s with URL */
if|if
condition|(
name|strstr
argument_list|(
name|browser
argument_list|,
literal|"%s"
argument_list|)
condition|)
name|cmd
operator|=
name|strreplace
argument_list|(
name|browser
argument_list|,
literal|"%s"
argument_list|,
name|url
argument_list|)
expr_stmt|;
else|else
name|cmd
operator|=
name|g_strconcat
argument_list|(
name|browser
argument_list|,
literal|" "
argument_list|,
name|url
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* parse the cmd line */
if|if
condition|(
operator|!
name|g_shell_parse_argv
argument_list|(
name|cmd
argument_list|,
name|NULL
argument_list|,
operator|&
name|argv
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Could not parse specified web browser command:\n%s"
argument_list|)
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
return|return
name|FALSE
return|;
block|}
name|retval
operator|=
name|g_spawn_async
argument_list|(
name|NULL
argument_list|,
name|argv
argument_list|,
name|NULL
argument_list|,
name|G_SPAWN_SEARCH_PATH
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|retval
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Could not execute specified web browser:\n%s"
argument_list|)
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
name|g_free
argument_list|(
name|browser
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|cmd
argument_list|)
expr_stmt|;
name|g_strfreev
argument_list|(
name|argv
argument_list|)
expr_stmt|;
return|return
name|retval
return|;
endif|#
directive|endif
block|}
end_function

begin_ifndef
ifndef|#
directive|ifndef
name|G_OS_WIN32
end_ifndef

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|strreplace (const gchar * string,const gchar * delimiter,const gchar * replacement)
name|strreplace
parameter_list|(
specifier|const
name|gchar
modifier|*
name|string
parameter_list|,
specifier|const
name|gchar
modifier|*
name|delimiter
parameter_list|,
specifier|const
name|gchar
modifier|*
name|replacement
parameter_list|)
block|{
name|gchar
modifier|*
name|ret
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|tmp
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
name|g_return_val_if_fail
argument_list|(
name|delimiter
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|replacement
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|tmp
operator|=
name|g_strsplit
argument_list|(
name|string
argument_list|,
name|delimiter
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|ret
operator|=
name|g_strjoinv
argument_list|(
name|replacement
argument_list|,
name|tmp
argument_list|)
expr_stmt|;
name|g_strfreev
argument_list|(
name|tmp
argument_list|)
expr_stmt|;
return|return
name|ret
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* !G_OS_WIN32 */
end_comment

end_unit

