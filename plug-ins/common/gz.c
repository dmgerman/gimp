begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  * Copyright (C) 1997 Daniel Risacher, magnus@alum.mit.edu  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* Minor changes to support file magic */
end_comment

begin_comment
comment|/* 4 Oct 1997 -- Risacher */
end_comment

begin_comment
comment|/* gzip plug-in for the gimp */
end_comment

begin_comment
comment|/* loosley based on url.c by */
end_comment

begin_comment
comment|/* Josh MacDonald, jmacd@cs.berkeley.edu */
end_comment

begin_comment
comment|/* and, very loosely on hrz.c by */
end_comment

begin_comment
comment|/* Albert Cahalan<acahalan at cs.uml.edu> */
end_comment

begin_comment
comment|/* This is reads and writes gziped image files for the Gimp  *  * You need to have gzip installed for it to work.  *  * It should work with file names of the form  * filename.foo.gz where foo is some already-recognized extension  *  * and it also works for names of the form  * filename.xcfgz - which is equivalent to  * filename.xcf.gz  *  * I added the xcfgz bit because having a default extension of xcf.gz  * can confuse the file selection dialog box somewhat, forcing the  * user to type sometimes when he/she otherwise wouldn't need to.  *  * I later decided I didn't like it because I don't like to bloat  * the file-extension namespace.  But I left in the recognition  * feature/bug so if people want to use files named foo.xcfgz by  * default, they can just hack their pluginrc file.  *  * to do this hack, change :  *                      "xcf.gz,gz,xcfgz"  * to  *                      "xcfgz,gz,xcf.gz"  *  *  * -Dan Risacher, 0430 CDT, 26 May 1997  */
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
file|<sys/types.h>
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

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_SYS_WAIT_H
end_ifdef

begin_include
include|#
directive|include
file|<sys/wait.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<sys/stat.h>
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
file|<errno.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_define
DECL|macro|STRICT
define|#
directive|define
name|STRICT
end_define

begin_define
DECL|macro|WinMain
define|#
directive|define
name|WinMain
value|WinMain_foo
end_define

begin_include
include|#
directive|include
file|<windows.h>
end_include

begin_include
include|#
directive|include
file|<io.h>
end_include

begin_comment
comment|/* _get_osfhandle */
end_comment

begin_undef
undef|#
directive|undef
name|WinMain
end_undef

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_comment
comment|/* Author 1: Josh MacDonald (url.c) */
end_comment

begin_comment
comment|/* Author 2: Daniel Risacher (gz.c) */
end_comment

begin_comment
comment|/* According to USAF Lt Steve Werhle, US DoD software development  * contracts average about $25 USD per source line of code (SLOC).  By  * that metric, I figure this plug-in is worth about $10,000 USD */
end_comment

begin_comment
comment|/* But you got it free.   Magic of Gnu. */
end_comment

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
name|gint32
name|load_image
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gint32
name|run_mode
parameter_list|,
name|GimpPDBStatusType
modifier|*
name|status
comment|/* return value */
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpPDBStatusType
name|save_image
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|,
name|gint32
name|run_mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|valid_file
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
specifier|const
name|gchar
modifier|*
name|find_extension
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

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
block|,
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
name|load_args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"run_mode"
block|,
literal|"Interactive, non-interactive"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"filename"
block|,
literal|"The name of the file to load"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"raw_filename"
block|,
literal|"The name entered"
block|}
block|}
decl_stmt|;
specifier|static
name|GimpParamDef
name|load_return_vals
index|[]
init|=
block|{
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"Output image"
block|}
block|,   }
decl_stmt|;
specifier|static
name|GimpParamDef
name|save_args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"run_mode"
block|,
literal|"Interactive, non-interactive"
block|}
block|,
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"Input image"
block|}
block|,
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"Drawable to save"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"filename"
block|,
literal|"The name of the file to save the image in"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"raw_filename"
block|,
literal|"The name of the file to save the image in"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"file_gz_load"
argument_list|,
literal|"loads files compressed with gzip"
argument_list|,
literal|"You need to have gzip installed."
argument_list|,
literal|"Daniel Risacher"
argument_list|,
literal|"Daniel Risacher, Spencer Kimball and Peter Mattis"
argument_list|,
literal|"1995-1997"
argument_list|,
literal|"<Load>/gzip"
argument_list|,
name|NULL
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|load_args
argument_list|)
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|load_return_vals
argument_list|)
argument_list|,
name|load_args
argument_list|,
name|load_return_vals
argument_list|)
expr_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"file_gz_save"
argument_list|,
literal|"saves files compressed with gzip"
argument_list|,
literal|"You need to have gzip installed."
argument_list|,
literal|"Daniel Risacher"
argument_list|,
literal|"Daniel Risacher, Spencer Kimball and Peter Mattis"
argument_list|,
literal|"1995-1997"
argument_list|,
literal|"<Save>/gzip"
argument_list|,
literal|"RGB*, GRAY*, INDEXED*"
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|save_args
argument_list|)
argument_list|,
literal|0
argument_list|,
name|save_args
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_register_magic_load_handler
argument_list|(
literal|"file_gz_load"
argument_list|,
literal|"xcf.gz,gz,xcfgz"
argument_list|,
literal|""
argument_list|,
literal|"0,string,\037\213"
argument_list|)
expr_stmt|;
name|gimp_register_save_handler
argument_list|(
literal|"file_gz_save"
argument_list|,
literal|"xcf.gz,gz,xcfgz"
argument_list|,
literal|""
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
name|GimpRunMode
name|run_mode
decl_stmt|;
name|GimpPDBStatusType
name|status
init|=
name|GIMP_PDB_SUCCESS
decl_stmt|;
name|gint32
name|image_ID
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
name|INIT_I18N
argument_list|()
expr_stmt|;
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
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"file_gz_load"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|image_ID
operator|=
name|load_image
argument_list|(
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|,
name|param
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_int32
argument_list|,
operator|&
name|status
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_ID
operator|!=
operator|-
literal|1
operator|&&
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
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
name|GIMP_PDB_IMAGE
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_image
operator|=
name|image_ID
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"file_gz_save"
argument_list|)
operator|==
literal|0
condition|)
block|{
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|GIMP_RUN_INTERACTIVE
case|:
break|break;
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
comment|/*  Make sure all the arguments are there!  */
if|if
condition|(
name|nparams
operator|!=
literal|4
condition|)
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
break|break;
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
break|break;
default|default:
break|break;
block|}
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
name|status
operator|=
name|save_image
argument_list|(
name|param
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|,
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
argument_list|,
name|param
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_int32
argument_list|,
name|param
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_int32
argument_list|)
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
name|GimpPDBStatusType
DECL|function|save_image (const gchar * filename,gint32 image_ID,gint32 drawable_ID,gint32 run_mode)
name|save_image
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|,
name|gint32
name|run_mode
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|ext
decl_stmt|;
name|gchar
modifier|*
name|tmpname
decl_stmt|;
ifndef|#
directive|ifndef
name|G_OS_WIN32
name|FILE
modifier|*
name|f
decl_stmt|;
name|gint
name|pid
decl_stmt|;
name|gint
name|wpid
decl_stmt|;
name|gint
name|process_status
decl_stmt|;
else|#
directive|else
name|FILE
modifier|*
name|in
decl_stmt|;
name|FILE
modifier|*
name|out
decl_stmt|;
name|STARTUPINFO
name|startupinfo
decl_stmt|;
name|PROCESS_INFORMATION
name|processinfo
decl_stmt|;
endif|#
directive|endif
if|if
condition|(
name|NULL
operator|==
operator|(
name|ext
operator|=
name|find_extension
argument_list|(
name|filename
argument_list|)
operator|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"No sensible extension, saving as compressed XCF."
argument_list|)
argument_list|)
expr_stmt|;
name|ext
operator|=
literal|".xcf"
expr_stmt|;
block|}
comment|/* get a temp name with the right extension and save into it. */
name|tmpname
operator|=
name|gimp_temp_name
argument_list|(
name|ext
operator|+
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|gimp_file_save
argument_list|(
name|run_mode
argument_list|,
name|image_ID
argument_list|,
name|drawable_ID
argument_list|,
name|tmpname
argument_list|,
name|tmpname
argument_list|)
operator|&&
name|valid_file
argument_list|(
name|tmpname
argument_list|)
operator|)
condition|)
block|{
name|unlink
argument_list|(
name|tmpname
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tmpname
argument_list|)
expr_stmt|;
return|return
name|GIMP_PDB_EXECUTION_ERROR
return|;
block|}
ifndef|#
directive|ifndef
name|G_OS_WIN32
comment|/* fork off a gzip process */
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
name|g_message
argument_list|(
literal|"fork() failed: %s"
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
name|GIMP_PDB_EXECUTION_ERROR
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
operator|!
operator|(
name|f
operator|=
name|fopen
argument_list|(
name|filename
argument_list|,
literal|"w"
argument_list|)
operator|)
condition|)
block|{
name|g_message
argument_list|(
literal|"fopen() failed: %s"
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
name|_exit
argument_list|(
literal|127
argument_list|)
expr_stmt|;
block|}
comment|/* make stdout for this process be the output file */
if|if
condition|(
operator|-
literal|1
operator|==
name|dup2
argument_list|(
name|fileno
argument_list|(
name|f
argument_list|)
argument_list|,
name|fileno
argument_list|(
name|stdout
argument_list|)
argument_list|)
condition|)
name|g_message
argument_list|(
literal|"dup2() failed: %s"
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
comment|/* and gzip into it */
name|execlp
argument_list|(
literal|"gzip"
argument_list|,
literal|"gzip"
argument_list|,
literal|"-cfn"
argument_list|,
name|tmpname
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_message
argument_list|(
literal|"execlp(\"gzip -cfn\") failed: %s"
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
name|_exit
argument_list|(
literal|127
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|wpid
operator|=
name|waitpid
argument_list|(
name|pid
argument_list|,
operator|&
name|process_status
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|wpid
operator|<
literal|0
operator|)
operator|||
operator|!
name|WIFEXITED
argument_list|(
name|process_status
argument_list|)
operator|||
operator|(
name|WEXITSTATUS
argument_list|(
name|process_status
argument_list|)
operator|!=
literal|0
operator|)
condition|)
block|{
name|g_message
argument_list|(
literal|"gzip exited abnormally on file '%s'"
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|tmpname
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tmpname
argument_list|)
expr_stmt|;
return|return
literal|0
return|;
block|}
block|}
else|#
directive|else
comment|/* G_OS_WIN32 */
name|in
operator|=
name|fopen
argument_list|(
name|tmpname
argument_list|,
literal|"rb"
argument_list|)
expr_stmt|;
name|out
operator|=
name|fopen
argument_list|(
name|filename
argument_list|,
literal|"wb"
argument_list|)
expr_stmt|;
name|startupinfo
operator|.
name|cb
operator|=
sizeof|sizeof
argument_list|(
name|STARTUPINFO
argument_list|)
expr_stmt|;
name|startupinfo
operator|.
name|lpReserved
operator|=
name|NULL
expr_stmt|;
name|startupinfo
operator|.
name|lpDesktop
operator|=
name|NULL
expr_stmt|;
name|startupinfo
operator|.
name|lpTitle
operator|=
name|NULL
expr_stmt|;
name|startupinfo
operator|.
name|dwFlags
operator|=
name|STARTF_FORCEOFFFEEDBACK
operator||
name|STARTF_USESHOWWINDOW
operator||
name|STARTF_USESTDHANDLES
expr_stmt|;
name|startupinfo
operator|.
name|wShowWindow
operator|=
name|SW_SHOWMINNOACTIVE
expr_stmt|;
name|startupinfo
operator|.
name|cbReserved2
operator|=
literal|0
expr_stmt|;
name|startupinfo
operator|.
name|lpReserved2
operator|=
name|NULL
expr_stmt|;
name|startupinfo
operator|.
name|hStdInput
operator|=
operator|(
name|HANDLE
operator|)
name|_get_osfhandle
argument_list|(
name|fileno
argument_list|(
name|in
argument_list|)
argument_list|)
expr_stmt|;
name|startupinfo
operator|.
name|hStdOutput
operator|=
operator|(
name|HANDLE
operator|)
name|_get_osfhandle
argument_list|(
name|fileno
argument_list|(
name|out
argument_list|)
argument_list|)
expr_stmt|;
name|startupinfo
operator|.
name|hStdError
operator|=
name|GetStdHandle
argument_list|(
name|STD_ERROR_HANDLE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|CreateProcess
argument_list|(
name|NULL
argument_list|,
literal|"minigzip"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|NORMAL_PRIORITY_CLASS
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|startupinfo
argument_list|,
operator|&
name|processinfo
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
literal|"CreateProcess failed. Minigzip.exe not in the path?"
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tmpname
argument_list|)
expr_stmt|;
name|_exit
argument_list|(
literal|127
argument_list|)
expr_stmt|;
block|}
name|CloseHandle
argument_list|(
name|processinfo
operator|.
name|hThread
argument_list|)
expr_stmt|;
name|WaitForSingleObject
argument_list|(
name|processinfo
operator|.
name|hProcess
argument_list|,
name|INFINITE
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* G_OS_WIN32 */
name|unlink
argument_list|(
name|tmpname
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tmpname
argument_list|)
expr_stmt|;
return|return
name|GIMP_PDB_SUCCESS
return|;
block|}
end_function

begin_function
specifier|static
name|gint32
DECL|function|load_image (const gchar * filename,gint32 run_mode,GimpPDBStatusType * status)
name|load_image
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gint32
name|run_mode
parameter_list|,
name|GimpPDBStatusType
modifier|*
name|status
comment|/* return value */
parameter_list|)
block|{
name|gint32
name|image_ID
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|ext
decl_stmt|;
name|gchar
modifier|*
name|tmpname
decl_stmt|;
ifndef|#
directive|ifndef
name|G_OS_WIN32
name|gint
name|pid
decl_stmt|;
name|gint
name|wpid
decl_stmt|;
name|gint
name|process_status
decl_stmt|;
else|#
directive|else
name|FILE
modifier|*
name|in
decl_stmt|,
modifier|*
name|out
decl_stmt|;
name|SECURITY_ATTRIBUTES
name|secattr
decl_stmt|;
name|STARTUPINFO
name|startupinfo
decl_stmt|;
name|PROCESS_INFORMATION
name|processinfo
decl_stmt|;
endif|#
directive|endif
if|if
condition|(
name|NULL
operator|==
operator|(
name|ext
operator|=
name|find_extension
argument_list|(
name|filename
argument_list|)
operator|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"No sensible extension, attempting to load "
literal|"with file magic."
argument_list|)
argument_list|)
expr_stmt|;
name|ext
operator|=
literal|".foo"
expr_stmt|;
block|}
comment|/* find a temp name */
name|tmpname
operator|=
name|gimp_temp_name
argument_list|(
name|ext
operator|+
literal|1
argument_list|)
expr_stmt|;
ifndef|#
directive|ifndef
name|G_OS_WIN32
comment|/* fork off a g(un)zip and wait for it */
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
name|g_message
argument_list|(
literal|"fork() failed: %s"
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
operator|*
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
elseif|else
if|if
condition|(
name|pid
operator|==
literal|0
condition|)
comment|/* child process */
block|{
name|FILE
modifier|*
name|f
decl_stmt|;
if|if
condition|(
operator|!
operator|(
name|f
operator|=
name|fopen
argument_list|(
name|tmpname
argument_list|,
literal|"w"
argument_list|)
operator|)
condition|)
block|{
name|g_message
argument_list|(
literal|"fopen() failed: %s"
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
name|_exit
argument_list|(
literal|127
argument_list|)
expr_stmt|;
block|}
comment|/* make stdout for this child process be the temp file */
if|if
condition|(
operator|-
literal|1
operator|==
name|dup2
argument_list|(
name|fileno
argument_list|(
name|f
argument_list|)
argument_list|,
name|fileno
argument_list|(
name|stdout
argument_list|)
argument_list|)
condition|)
block|{
name|g_free
argument_list|(
name|tmpname
argument_list|)
expr_stmt|;
name|g_message
argument_list|(
literal|"dup2() failed: %s"
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
block|}
comment|/* and unzip into it */
name|execlp
argument_list|(
literal|"gzip"
argument_list|,
literal|"gzip"
argument_list|,
literal|"-cfd"
argument_list|,
name|filename
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_message
argument_list|(
literal|"execlp(\"gzip -cfd\") failed: %s"
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
name|_exit
argument_list|(
literal|127
argument_list|)
expr_stmt|;
block|}
else|else
comment|/* parent process */
block|{
name|wpid
operator|=
name|waitpid
argument_list|(
name|pid
argument_list|,
operator|&
name|process_status
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|wpid
operator|<
literal|0
operator|)
operator|||
operator|!
name|WIFEXITED
argument_list|(
name|process_status
argument_list|)
operator|||
operator|(
name|WEXITSTATUS
argument_list|(
name|process_status
argument_list|)
operator|!=
literal|0
operator|)
condition|)
block|{
name|g_message
argument_list|(
literal|"gzip exited abnormally on file '%s'"
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tmpname
argument_list|)
expr_stmt|;
operator|*
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
block|}
else|#
directive|else
name|in
operator|=
name|fopen
argument_list|(
name|filename
argument_list|,
literal|"rb"
argument_list|)
expr_stmt|;
name|out
operator|=
name|fopen
argument_list|(
name|tmpname
argument_list|,
literal|"wb"
argument_list|)
expr_stmt|;
name|startupinfo
operator|.
name|cb
operator|=
sizeof|sizeof
argument_list|(
name|STARTUPINFO
argument_list|)
expr_stmt|;
name|startupinfo
operator|.
name|lpReserved
operator|=
name|NULL
expr_stmt|;
name|startupinfo
operator|.
name|lpDesktop
operator|=
name|NULL
expr_stmt|;
name|startupinfo
operator|.
name|lpTitle
operator|=
name|NULL
expr_stmt|;
name|startupinfo
operator|.
name|dwFlags
operator|=
name|STARTF_FORCEOFFFEEDBACK
operator||
name|STARTF_USESHOWWINDOW
operator||
name|STARTF_USESTDHANDLES
expr_stmt|;
name|startupinfo
operator|.
name|wShowWindow
operator|=
name|SW_SHOWMINNOACTIVE
expr_stmt|;
name|startupinfo
operator|.
name|cbReserved2
operator|=
literal|0
expr_stmt|;
name|startupinfo
operator|.
name|lpReserved2
operator|=
name|NULL
expr_stmt|;
name|startupinfo
operator|.
name|hStdInput
operator|=
operator|(
name|HANDLE
operator|)
name|_get_osfhandle
argument_list|(
name|fileno
argument_list|(
name|in
argument_list|)
argument_list|)
expr_stmt|;
name|startupinfo
operator|.
name|hStdOutput
operator|=
operator|(
name|HANDLE
operator|)
name|_get_osfhandle
argument_list|(
name|fileno
argument_list|(
name|out
argument_list|)
argument_list|)
expr_stmt|;
name|startupinfo
operator|.
name|hStdError
operator|=
name|GetStdHandle
argument_list|(
name|STD_ERROR_HANDLE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|CreateProcess
argument_list|(
name|NULL
argument_list|,
literal|"minigzip -d"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|NORMAL_PRIORITY_CLASS
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|startupinfo
argument_list|,
operator|&
name|processinfo
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
literal|"CreateProcess failed: %d"
argument_list|,
name|GetLastError
argument_list|()
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tmpname
argument_list|)
expr_stmt|;
name|_exit
argument_list|(
literal|127
argument_list|)
expr_stmt|;
block|}
name|CloseHandle
argument_list|(
name|processinfo
operator|.
name|hThread
argument_list|)
expr_stmt|;
name|WaitForSingleObject
argument_list|(
name|processinfo
operator|.
name|hProcess
argument_list|,
name|INFINITE
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|in
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|out
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* G_OS_WIN32 */
comment|/* now that we un-gziped it, load the temp file */
name|image_ID
operator|=
name|gimp_file_load
argument_list|(
name|run_mode
argument_list|,
name|tmpname
argument_list|,
name|tmpname
argument_list|)
expr_stmt|;
name|unlink
argument_list|(
name|tmpname
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tmpname
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_ID
operator|!=
operator|-
literal|1
condition|)
block|{
operator|*
name|status
operator|=
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_image_set_filename
argument_list|(
name|image_ID
argument_list|,
name|filename
argument_list|)
expr_stmt|;
block|}
else|else
operator|*
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
return|return
name|image_ID
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|valid_file (const gchar * filename)
name|valid_file
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
name|gint
name|stat_res
decl_stmt|;
name|struct
name|stat
name|buf
decl_stmt|;
name|stat_res
operator|=
name|stat
argument_list|(
name|filename
argument_list|,
operator|&
name|buf
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
literal|0
operator|==
name|stat_res
operator|)
operator|&&
operator|(
name|buf
operator|.
name|st_size
operator|>
literal|0
operator|)
condition|)
return|return
name|TRUE
return|;
else|else
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
specifier|const
name|gchar
modifier|*
DECL|function|find_extension (const gchar * filename)
name|find_extension
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
name|gchar
modifier|*
name|filename_copy
decl_stmt|;
name|gchar
modifier|*
name|ext
decl_stmt|;
comment|/* we never free this copy - aren't we evil! */
name|filename_copy
operator|=
name|g_strdup
argument_list|(
name|filename
argument_list|)
expr_stmt|;
comment|/* find the extension, boy! */
name|ext
operator|=
name|strrchr
argument_list|(
name|filename_copy
argument_list|,
literal|'.'
argument_list|)
expr_stmt|;
while|while
condition|(
name|TRUE
condition|)
block|{
if|if
condition|(
operator|!
name|ext
operator|||
name|ext
index|[
literal|1
index|]
operator|==
literal|'\0'
operator|||
name|strchr
argument_list|(
name|ext
argument_list|,
literal|'/'
argument_list|)
condition|)
block|{
return|return
name|NULL
return|;
block|}
if|if
condition|(
literal|0
operator|==
name|g_ascii_strcasecmp
argument_list|(
name|ext
argument_list|,
literal|".xcfgz"
argument_list|)
condition|)
block|{
return|return
literal|".xcf"
return|;
comment|/* we've found it */
block|}
if|if
condition|(
literal|0
operator|!=
name|g_ascii_strcasecmp
argument_list|(
name|ext
argument_list|,
literal|".gz"
argument_list|)
condition|)
block|{
return|return
name|ext
return|;
block|}
else|else
block|{
comment|/* we found ".gz" so strip it, loop back, and look again */
operator|*
name|ext
operator|=
literal|'\0'
expr_stmt|;
name|ext
operator|=
name|strrchr
argument_list|(
name|filename_copy
argument_list|,
literal|'.'
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

end_unit

