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
file|<glib.h>
end_include

begin_comment
comment|/* For NATIVE_WIN32 */
end_comment

begin_ifdef
ifdef|#
directive|ifdef
name|NATIVE_WIN32
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

begin_ifdef
ifdef|#
directive|ifdef
name|__EMX__
end_ifdef

begin_include
include|#
directive|include
file|<fcntl.h>
end_include

begin_include
include|#
directive|include
file|<process.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"libgimp/gimp.h"
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
name|char
modifier|*
name|name
parameter_list|,
name|int
name|nparams
parameter_list|,
name|GParam
modifier|*
name|param
parameter_list|,
name|int
modifier|*
name|nreturn_vals
parameter_list|,
name|GParam
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
name|char
modifier|*
name|filename
parameter_list|,
name|gint32
name|run_mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|save_image
parameter_list|(
name|char
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
name|int
name|valid_file
parameter_list|(
name|char
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|char
modifier|*
name|find_extension
parameter_list|(
name|char
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|PLUG_IN_INFO
name|GPlugInInfo
name|PLUG_IN_INFO
init|=
block|{
name|NULL
block|,
comment|/* init_proc */
name|NULL
block|,
comment|/* quit_proc */
name|query
block|,
comment|/* query_proc */
name|run
block|,
comment|/* run_proc */
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
parameter_list|()
block|{
specifier|static
name|GParamDef
name|load_args
index|[]
init|=
block|{
block|{
name|PARAM_INT32
block|,
literal|"run_mode"
block|,
literal|"Interactive, non-interactive"
block|}
block|,
block|{
name|PARAM_STRING
block|,
literal|"filename"
block|,
literal|"The name of the file to load"
block|}
block|,
block|{
name|PARAM_STRING
block|,
literal|"raw_filename"
block|,
literal|"The name entered"
block|}
block|,   }
decl_stmt|;
specifier|static
name|GParamDef
name|load_return_vals
index|[]
init|=
block|{
block|{
name|PARAM_IMAGE
block|,
literal|"image"
block|,
literal|"Output image"
block|}
block|,   }
decl_stmt|;
specifier|static
name|int
name|nload_args
init|=
sizeof|sizeof
argument_list|(
name|load_args
argument_list|)
operator|/
sizeof|sizeof
argument_list|(
name|load_args
index|[
literal|0
index|]
argument_list|)
decl_stmt|;
specifier|static
name|int
name|nload_return_vals
init|=
sizeof|sizeof
argument_list|(
name|load_return_vals
argument_list|)
operator|/
sizeof|sizeof
argument_list|(
name|load_return_vals
index|[
literal|0
index|]
argument_list|)
decl_stmt|;
specifier|static
name|GParamDef
name|save_args
index|[]
init|=
block|{
block|{
name|PARAM_INT32
block|,
literal|"run_mode"
block|,
literal|"Interactive, non-interactive"
block|}
block|,
block|{
name|PARAM_IMAGE
block|,
literal|"image"
block|,
literal|"Input image"
block|}
block|,
block|{
name|PARAM_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"Drawable to save"
block|}
block|,
block|{
name|PARAM_STRING
block|,
literal|"filename"
block|,
literal|"The name of the file to save the image in"
block|}
block|,
block|{
name|PARAM_STRING
block|,
literal|"raw_filename"
block|,
literal|"The name of the file to save the image in"
block|}
block|}
decl_stmt|;
specifier|static
name|int
name|nsave_args
init|=
sizeof|sizeof
argument_list|(
name|save_args
argument_list|)
operator|/
sizeof|sizeof
argument_list|(
name|save_args
index|[
literal|0
index|]
argument_list|)
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
name|PROC_PLUG_IN
argument_list|,
name|nload_args
argument_list|,
name|nload_return_vals
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
literal|"You need to have gzip installed"
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
name|PROC_PLUG_IN
argument_list|,
name|nsave_args
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
DECL|function|run (char * name,int nparams,GParam * param,int * nreturn_vals,GParam ** return_vals)
name|run
parameter_list|(
name|char
modifier|*
name|name
parameter_list|,
name|int
name|nparams
parameter_list|,
name|GParam
modifier|*
name|param
parameter_list|,
name|int
modifier|*
name|nreturn_vals
parameter_list|,
name|GParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
block|{
specifier|static
name|GParam
name|values
index|[
literal|2
index|]
decl_stmt|;
name|GRunModeType
name|run_mode
decl_stmt|;
name|GStatusType
name|status
init|=
name|STATUS_SUCCESS
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
name|PARAM_STATUS
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
name|STATUS_CALLING_ERROR
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
name|nreturn_vals
operator|=
literal|2
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
name|STATUS_SUCCESS
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|.
name|type
operator|=
name|PARAM_IMAGE
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
else|else
block|{
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|STATUS_EXECUTION_ERROR
expr_stmt|;
name|g_assert
argument_list|(
name|FALSE
argument_list|)
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
name|RUN_INTERACTIVE
case|:
break|break;
case|case
name|RUN_NONINTERACTIVE
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
name|STATUS_CALLING_ERROR
expr_stmt|;
case|case
name|RUN_WITH_LAST_VALS
case|:
break|break;
default|default:
break|break;
block|}
operator|*
name|nreturn_vals
operator|=
literal|1
expr_stmt|;
if|if
condition|(
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
condition|)
block|{
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|STATUS_SUCCESS
expr_stmt|;
block|}
else|else
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|STATUS_EXECUTION_ERROR
expr_stmt|;
block|}
else|else
name|g_assert
argument_list|(
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_ifdef
ifdef|#
directive|ifdef
name|__EMX__
end_ifdef

begin_function
DECL|function|spawn_gzip (char * filename,char * tmpname,char * parms,int * pid)
specifier|static
name|int
name|spawn_gzip
parameter_list|(
name|char
modifier|*
name|filename
parameter_list|,
name|char
modifier|*
name|tmpname
parameter_list|,
name|char
modifier|*
name|parms
parameter_list|,
name|int
modifier|*
name|pid
parameter_list|)
block|{
name|FILE
modifier|*
name|f
decl_stmt|;
name|int
name|tfd
decl_stmt|;
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
literal|"gz: fopen failed: %s\n"
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
comment|/* save fileno(stdout) */
name|tfd
operator|=
name|dup
argument_list|(
name|fileno
argument_list|(
name|stdout
argument_list|)
argument_list|)
expr_stmt|;
comment|/* make stdout for this process be the output file */
if|if
condition|(
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
operator|==
operator|-
literal|1
condition|)
block|{
name|g_message
argument_list|(
literal|"gz: dup2 failed: %s\n"
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
name|close
argument_list|(
name|tfd
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
name|fcntl
argument_list|(
name|tfd
argument_list|,
name|F_SETFD
argument_list|,
name|FD_CLOEXEC
argument_list|)
expr_stmt|;
operator|*
name|pid
operator|=
name|spawnlp
argument_list|(
name|P_NOWAIT
argument_list|,
literal|"gzip"
argument_list|,
literal|"gzip"
argument_list|,
name|parms
argument_list|,
name|tmpname
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|f
argument_list|)
expr_stmt|;
comment|/* restore fileno(stdout) */
name|dup2
argument_list|(
name|tfd
argument_list|,
name|fileno
argument_list|(
name|stdout
argument_list|)
argument_list|)
expr_stmt|;
name|close
argument_list|(
name|tfd
argument_list|)
expr_stmt|;
if|if
condition|(
operator|*
name|pid
operator|==
operator|-
literal|1
condition|)
block|{
name|g_message
argument_list|(
literal|"gz: spawn failed: %s\n"
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
return|return
literal|0
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_function
specifier|static
name|gint
DECL|function|save_image (char * filename,gint32 image_ID,gint32 drawable_ID,gint32 run_mode)
name|save_image
parameter_list|(
name|char
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
name|GParam
modifier|*
name|params
decl_stmt|;
name|gint
name|retvals
decl_stmt|;
name|char
modifier|*
name|ext
decl_stmt|;
name|char
modifier|*
name|tmpname
decl_stmt|;
ifndef|#
directive|ifndef
name|NATIVE_WIN32
name|FILE
modifier|*
name|f
decl_stmt|;
name|int
name|pid
decl_stmt|;
name|int
name|status
decl_stmt|;
else|#
directive|else
name|SECURITY_ATTRIBUTES
name|secattr
decl_stmt|;
name|HANDLE
name|f
decl_stmt|;
name|STARTUPINFO
name|startupinfo
decl_stmt|;
name|PROCESS_INFORMATION
name|processinfo
decl_stmt|;
name|gchar
modifier|*
name|cmdline
decl_stmt|;
endif|#
directive|endif
name|ext
operator|=
name|find_extension
argument_list|(
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
literal|0
operator|==
operator|*
name|ext
condition|)
block|{
name|g_message
argument_list|(
literal|"gz: no sensible extension, saving as gzip'd xcf\n"
argument_list|)
expr_stmt|;
name|ext
operator|=
literal|".xcf"
expr_stmt|;
block|}
comment|/* get a temp name with the right extension and save into it. */
name|params
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_temp_name"
argument_list|,
operator|&
name|retvals
argument_list|,
name|PARAM_STRING
argument_list|,
name|ext
operator|+
literal|1
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|tmpname
operator|=
name|params
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
expr_stmt|;
name|params
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_file_save"
argument_list|,
operator|&
name|retvals
argument_list|,
name|PARAM_INT32
argument_list|,
name|run_mode
argument_list|,
name|PARAM_IMAGE
argument_list|,
name|image_ID
argument_list|,
name|PARAM_DRAWABLE
argument_list|,
name|drawable_ID
argument_list|,
name|PARAM_STRING
argument_list|,
name|tmpname
argument_list|,
name|PARAM_STRING
argument_list|,
name|tmpname
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
if|if
condition|(
name|params
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|FALSE
operator|||
operator|!
name|valid_file
argument_list|(
name|tmpname
argument_list|)
condition|)
block|{
name|unlink
argument_list|(
name|tmpname
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
comment|/*   if (! file_save(image_ID, tmpname, tmpname)) { */
comment|/*     unlink (tmpname); */
comment|/*     return -1; */
comment|/*   } */
ifndef|#
directive|ifndef
name|NATIVE_WIN32
ifndef|#
directive|ifndef
name|__EMX__
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
literal|"gz: fork failed: %s\n"
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
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
literal|"gz: fopen failed: %s\n"
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
literal|"gz: dup2 failed: %s\n"
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
literal|"-cf"
argument_list|,
name|tmpname
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_message
argument_list|(
literal|"gz: exec failed: gzip: %s\n"
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
elseif|else
else|#
directive|else
comment|/* __EMX__ */
if|if
condition|(
name|spawn_gzip
argument_list|(
name|filename
argument_list|,
name|tmpname
argument_list|,
literal|"-cf"
argument_list|,
operator|&
name|pid
argument_list|)
operator|==
operator|-
literal|1
condition|)
return|return
operator|-
literal|1
return|;
endif|#
directive|endif
block|{
name|waitpid
argument_list|(
name|pid
argument_list|,
operator|&
name|status
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|WIFEXITED
argument_list|(
name|status
argument_list|)
operator|||
name|WEXITSTATUS
argument_list|(
name|status
argument_list|)
operator|!=
literal|0
condition|)
block|{
name|g_message
argument_list|(
literal|"gz: gzip exited abnormally on file %s\n"
argument_list|,
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
comment|/* NATIVE_WIN32 */
name|secattr
operator|.
name|nLength
operator|=
sizeof|sizeof
argument_list|(
name|SECURITY_ATTRIBUTES
argument_list|)
expr_stmt|;
name|secattr
operator|.
name|lpSecurityDescriptor
operator|=
name|NULL
expr_stmt|;
name|secattr
operator|.
name|bInheritHandle
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
operator|(
name|f
operator|=
name|CreateFile
argument_list|(
name|filename
argument_list|,
name|GENERIC_WRITE
argument_list|,
name|FILE_SHARE_READ
argument_list|,
operator|&
name|secattr
argument_list|,
name|CREATE_ALWAYS
argument_list|,
name|FILE_ATTRIBUTE_NORMAL
argument_list|,
name|NULL
argument_list|)
operator|)
operator|==
name|INVALID_HANDLE_VALUE
condition|)
block|{
name|g_message
argument_list|(
literal|"gz: CreateFile failed\n"
argument_list|)
expr_stmt|;
name|_exit
argument_list|(
literal|127
argument_list|)
expr_stmt|;
block|}
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
name|GetStdHandle
argument_list|(
name|STD_INPUT_HANDLE
argument_list|)
expr_stmt|;
name|startupinfo
operator|.
name|hStdOutput
operator|=
name|f
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
name|cmdline
operator|=
name|g_strdup_printf
argument_list|(
literal|"gzip -cf %s"
argument_list|,
name|tmpname
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|CreateProcess
argument_list|(
name|NULL
argument_list|,
name|cmdline
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
literal|"gz: CreateProcess failed\n"
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
name|f
argument_list|)
expr_stmt|;
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
comment|/* NATIVE_WIN32 */
name|unlink
argument_list|(
name|tmpname
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gint32
DECL|function|load_image (char * filename,gint32 run_mode)
name|load_image
parameter_list|(
name|char
modifier|*
name|filename
parameter_list|,
name|gint32
name|run_mode
parameter_list|)
block|{
name|GParam
modifier|*
name|params
decl_stmt|;
name|gint
name|retvals
decl_stmt|;
name|char
modifier|*
name|ext
decl_stmt|;
name|char
modifier|*
name|tmpname
decl_stmt|;
ifndef|#
directive|ifndef
name|NATIVE_WIN32
name|int
name|pid
decl_stmt|;
name|int
name|status
decl_stmt|;
else|#
directive|else
name|SECURITY_ATTRIBUTES
name|secattr
decl_stmt|;
name|HANDLE
name|f
decl_stmt|;
name|STARTUPINFO
name|startupinfo
decl_stmt|;
name|PROCESS_INFORMATION
name|processinfo
decl_stmt|;
name|gchar
modifier|*
name|cmdline
decl_stmt|;
endif|#
directive|endif
name|ext
operator|=
name|find_extension
argument_list|(
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
literal|0
operator|==
operator|*
name|ext
condition|)
block|{
name|g_message
argument_list|(
literal|"gz: no sensible extension, attempting to load with file magic\n"
argument_list|)
expr_stmt|;
block|}
comment|/* find a temp name */
name|params
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_temp_name"
argument_list|,
operator|&
name|retvals
argument_list|,
name|PARAM_STRING
argument_list|,
name|ext
operator|+
literal|1
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|tmpname
operator|=
name|params
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
expr_stmt|;
ifndef|#
directive|ifndef
name|NATIVE_WIN32
ifndef|#
directive|ifndef
name|__EMX__
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
literal|"gz: fork failed: %s\n"
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
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
literal|"gz: fopen failed: %s\n"
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
name|g_message
argument_list|(
literal|"gz: dup2 failed: %s\n"
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
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
literal|"gz: exec failed: gunzip: %s\n"
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
elseif|else
comment|/* parent process */
else|#
directive|else
comment|/* __EMX__ */
if|if
condition|(
name|spawn_gzip
argument_list|(
name|filename
argument_list|,
name|tmpname
argument_list|,
literal|"-cfd"
argument_list|,
operator|&
name|pid
argument_list|)
operator|==
operator|-
literal|1
condition|)
return|return
operator|-
literal|1
return|;
endif|#
directive|endif
block|{
name|waitpid
argument_list|(
name|pid
argument_list|,
operator|&
name|status
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|WIFEXITED
argument_list|(
name|status
argument_list|)
operator|||
name|WEXITSTATUS
argument_list|(
name|status
argument_list|)
operator|!=
literal|0
condition|)
block|{
name|g_message
argument_list|(
literal|"gz: gzip exited abnormally on file %s\n"
argument_list|,
name|filename
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
block|}
else|#
directive|else
name|secattr
operator|.
name|nLength
operator|=
sizeof|sizeof
argument_list|(
name|SECURITY_ATTRIBUTES
argument_list|)
expr_stmt|;
name|secattr
operator|.
name|lpSecurityDescriptor
operator|=
name|NULL
expr_stmt|;
name|secattr
operator|.
name|bInheritHandle
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
operator|(
name|f
operator|=
name|CreateFile
argument_list|(
name|tmpname
argument_list|,
name|GENERIC_WRITE
argument_list|,
name|FILE_SHARE_READ
argument_list|,
operator|&
name|secattr
argument_list|,
name|CREATE_ALWAYS
argument_list|,
name|FILE_ATTRIBUTE_NORMAL
argument_list|,
name|NULL
argument_list|)
operator|)
operator|==
name|INVALID_HANDLE_VALUE
condition|)
block|{
name|g_message
argument_list|(
literal|"gz: CreateFile failed\n"
argument_list|)
expr_stmt|;
name|_exit
argument_list|(
literal|127
argument_list|)
expr_stmt|;
block|}
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
name|GetStdHandle
argument_list|(
name|STD_INPUT_HANDLE
argument_list|)
expr_stmt|;
name|startupinfo
operator|.
name|hStdOutput
operator|=
name|f
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
name|cmdline
operator|=
name|g_strdup_printf
argument_list|(
literal|"gzip -cfd %s"
argument_list|,
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|CreateProcess
argument_list|(
name|NULL
argument_list|,
name|cmdline
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
literal|"gz: CreateProcess failed: %d\n"
argument_list|,
name|GetLastError
argument_list|()
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
name|f
argument_list|)
expr_stmt|;
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
comment|/* NATIVE_WIN32 */
comment|/* now that we un-gziped it, load the temp file */
name|params
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_file_load"
argument_list|,
operator|&
name|retvals
argument_list|,
name|PARAM_INT32
argument_list|,
name|run_mode
argument_list|,
name|PARAM_STRING
argument_list|,
name|tmpname
argument_list|,
name|PARAM_STRING
argument_list|,
name|tmpname
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|unlink
argument_list|(
name|tmpname
argument_list|)
expr_stmt|;
if|if
condition|(
name|params
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|FALSE
condition|)
return|return
operator|-
literal|1
return|;
else|else
block|{
name|gimp_image_set_filename
argument_list|(
name|params
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
argument_list|,
name|filename
argument_list|)
expr_stmt|;
return|return
name|params
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
return|;
block|}
block|}
end_function

begin_function
DECL|function|valid_file (char * filename)
specifier|static
name|int
name|valid_file
parameter_list|(
name|char
modifier|*
name|filename
parameter_list|)
block|{
name|int
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
literal|1
return|;
else|else
return|return
literal|0
return|;
block|}
end_function

begin_function
DECL|function|find_extension (char * filename)
specifier|static
name|char
modifier|*
name|find_extension
parameter_list|(
name|char
modifier|*
name|filename
parameter_list|)
block|{
name|char
modifier|*
name|filename_copy
decl_stmt|;
name|char
modifier|*
name|ext
decl_stmt|;
comment|/* we never free this copy - aren't we evil! */
name|filename_copy
operator|=
name|malloc
argument_list|(
name|strlen
argument_list|(
name|filename
argument_list|)
operator|+
literal|1
argument_list|)
expr_stmt|;
name|strcpy
argument_list|(
name|filename_copy
argument_list|,
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
literal|1
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
literal|0
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
literal|""
return|;
block|}
if|if
condition|(
literal|0
operator|==
name|strcmp
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
name|strcmp
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
literal|0
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

