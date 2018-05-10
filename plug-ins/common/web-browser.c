begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Web Browser Plug-in  * Copyright (C) 2003  Henrik Brix Andersen<brix@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<gtk/gtk.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|PLATFORM_OSX
end_ifdef

begin_empty
empty|#import<Cocoa/Cocoa.h>
end_empty

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
DECL|macro|PLUG_IN_PROC
define|#
directive|define
name|PLUG_IN_PROC
value|"plug-in-web-browser"
end_define

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"web-browser"
end_define

begin_define
DECL|macro|PLUG_IN_ROLE
define|#
directive|define
name|PLUG_IN_ROLE
value|"gimp-web-browser"
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
name|GtkWindow
modifier|*
name|window
parameter_list|,
specifier|const
name|gchar
modifier|*
name|url
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|PLUG_IN_INFO
specifier|const
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
specifier|const
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
name|PLUG_IN_PROC
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
literal|2
index|]
decl_stmt|;
name|GimpPDBStatusType
name|status
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
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
name|NULL
argument_list|,
name|param
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
operator|*
name|nreturn_vals
operator|=
literal|2
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_STRING
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
operator|=
name|error
operator|->
name|message
expr_stmt|;
block|}
block|}
else|else
block|{
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
block|}
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
DECL|function|browser_open_url (GtkWindow * window,const gchar * url,GError ** error)
name|browser_open_url
parameter_list|(
name|GtkWindow
modifier|*
name|window
parameter_list|,
specifier|const
name|gchar
modifier|*
name|url
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
ifdef|#
directive|ifdef
name|G_OS_WIN32
name|HINSTANCE
name|hinst
init|=
name|ShellExecute
argument_list|(
name|GetDesktopWindow
argument_list|()
argument_list|,
literal|"open"
argument_list|,
name|url
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|SW_SHOW
argument_list|)
decl_stmt|;
if|if
condition|(
operator|(
name|gint
operator|)
name|hinst
operator|<=
literal|32
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|err
decl_stmt|;
switch|switch
condition|(
operator|(
name|gint
operator|)
name|hinst
condition|)
block|{
case|case
literal|0
case|:
name|err
operator|=
name|_
argument_list|(
literal|"The operating system is out of memory or resources."
argument_list|)
expr_stmt|;
break|break;
case|case
name|ERROR_FILE_NOT_FOUND
case|:
name|err
operator|=
name|_
argument_list|(
literal|"The specified file was not found."
argument_list|)
expr_stmt|;
break|break;
case|case
name|ERROR_PATH_NOT_FOUND
case|:
name|err
operator|=
name|_
argument_list|(
literal|"The specified path was not found."
argument_list|)
expr_stmt|;
break|break;
case|case
name|ERROR_BAD_FORMAT
case|:
name|err
operator|=
name|_
argument_list|(
literal|"The .exe file is invalid (non-Microsoft Win32 .exe or error in .exe image)."
argument_list|)
expr_stmt|;
break|break;
case|case
name|SE_ERR_ACCESSDENIED
case|:
name|err
operator|=
name|_
argument_list|(
literal|"The operating system denied access to the specified file."
argument_list|)
expr_stmt|;
break|break;
case|case
name|SE_ERR_ASSOCINCOMPLETE
case|:
name|err
operator|=
name|_
argument_list|(
literal|"The file name association is incomplete or invalid."
argument_list|)
expr_stmt|;
break|break;
case|case
name|SE_ERR_DDEBUSY
case|:
name|err
operator|=
name|_
argument_list|(
literal|"DDE transaction busy"
argument_list|)
expr_stmt|;
break|break;
case|case
name|SE_ERR_DDEFAIL
case|:
name|err
operator|=
name|_
argument_list|(
literal|"The DDE transaction failed."
argument_list|)
expr_stmt|;
break|break;
case|case
name|SE_ERR_DDETIMEOUT
case|:
name|err
operator|=
name|_
argument_list|(
literal|"The DDE transaction timed out."
argument_list|)
expr_stmt|;
break|break;
case|case
name|SE_ERR_DLLNOTFOUND
case|:
name|err
operator|=
name|_
argument_list|(
literal|"The specified DLL was not found."
argument_list|)
expr_stmt|;
break|break;
case|case
name|SE_ERR_NOASSOC
case|:
name|err
operator|=
name|_
argument_list|(
literal|"There is no application associated with the given file name extension."
argument_list|)
expr_stmt|;
break|break;
case|case
name|SE_ERR_OOM
case|:
name|err
operator|=
name|_
argument_list|(
literal|"There was not enough memory to complete the operation."
argument_list|)
expr_stmt|;
break|break;
case|case
name|SE_ERR_SHARE
case|:
name|err
operator|=
name|_
argument_list|(
literal|"A sharing violation occurred."
argument_list|)
expr_stmt|;
break|break;
default|default :
name|err
operator|=
name|_
argument_list|(
literal|"Unknown Microsoft Windows error."
argument_list|)
expr_stmt|;
block|}
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
literal|"Failed to open '%s': %s"
argument_list|)
argument_list|,
name|url
argument_list|,
name|err
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
return|return
name|TRUE
return|;
elif|#
directive|elif
name|defined
argument_list|(
name|PLATFORM_OSX
argument_list|)
name|NSURL
modifier|*
name|ns_url
decl_stmt|;
name|gboolean
name|retval
decl_stmt|;
block|@
name|autoreleasepool
block|{
name|ns_url
operator|=
index|[
name|NSURL
name|URLWithString
operator|:
index|[
name|NSString
name|stringWithUTF8String
operator|:
name|url
index|]
index|]
expr_stmt|;
name|retval
operator|=
index|[
index|[
name|NSWorkspace
name|sharedWorkspace
index|]
name|openURL
operator|:
name|ns_url
index|]
expr_stmt|;
block|}
return|return
name|retval
return|;
else|#
directive|else
name|gimp_ui_init
argument_list|(
name|PLUG_IN_BINARY
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|gtk_show_uri_on_window
argument_list|(
name|window
argument_list|,
name|url
argument_list|,
name|GDK_CURRENT_TIME
argument_list|,
name|error
argument_list|)
return|;
endif|#
directive|endif
block|}
end_function

end_unit

