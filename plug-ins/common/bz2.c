begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  * Copyright (C) 1997 Daniel Risacher  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* bzip2 plug-in for the gimp */
end_comment

begin_comment
comment|/* this is almost exactly the same as the gz(ip) plugin by */
end_comment

begin_comment
comment|/* Dan Risacher& Josh, so feel free to go look there. */
end_comment

begin_comment
comment|/* GZ plugin adapted to BZ2 by Adam. I've left all other */
end_comment

begin_comment
comment|/* Error checking added by srn. */
end_comment

begin_comment
comment|/* credits intact since it was only a super-wussy mod. */
end_comment

begin_comment
comment|/* This is reads and writes bzip2ed image files for the Gimp  *  * You need to have bzip2 installed for it to work.  *  * It should work with file names of the form  * filename.foo.bz2 where foo is some already-recognized extension  */
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

begin_include
include|#
directive|include
file|<sys/param.h>
end_include

begin_include
include|#
directive|include
file|<sys/wait.h>
end_include

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

begin_include
include|#
directive|include
file|<unistd.h>
end_include

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
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

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
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
name|GParam
modifier|*
name|param
parameter_list|,
name|gint
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
name|gchar
modifier|*
name|filename
parameter_list|,
name|gint32
name|run_mode
parameter_list|,
name|GStatusType
modifier|*
name|status
comment|/* return value */
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GStatusType
name|save_image
parameter_list|(
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
name|gchar
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gchar
modifier|*
name|find_extension
parameter_list|(
name|gchar
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
name|gint
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
name|gint
name|nload_return_vals
init|=
operator|(
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
operator|)
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
name|gint
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
literal|"file_bz2_load"
argument_list|,
literal|"loads files compressed with bzip2"
argument_list|,
literal|"You need to have bzip2 installed."
argument_list|,
literal|"Daniel Risacher"
argument_list|,
literal|"Daniel Risacher, Spencer Kimball and Peter Mattis"
argument_list|,
literal|"1995-1997"
argument_list|,
literal|"<Load>/bzip2"
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
literal|"file_bz2_save"
argument_list|,
literal|"saves files compressed with bzip2"
argument_list|,
literal|"You need to have bzip2 installed"
argument_list|,
literal|"Daniel Risacher"
argument_list|,
literal|"Daniel Risacher, Spencer Kimball and Peter Mattis"
argument_list|,
literal|"1995-1997"
argument_list|,
literal|"<Save>/bzip2"
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
name|gimp_register_load_handler
argument_list|(
literal|"file_bz2_load"
argument_list|,
literal|"xcf.bz2,bz2,xcfbz2"
argument_list|,
literal|""
argument_list|)
expr_stmt|;
name|gimp_register_save_handler
argument_list|(
literal|"file_bz2_save"
argument_list|,
literal|"xcf.bz2,bz2,xcfbz2"
argument_list|,
literal|""
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|run (gchar * name,gint nparams,GParam * param,gint * nreturn_vals,GParam ** return_vals)
name|run
parameter_list|(
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
name|GParam
modifier|*
name|param
parameter_list|,
name|gint
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
name|STATUS_EXECUTION_ERROR
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"file_bz2_load"
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
name|STATUS_SUCCESS
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
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"file_bz2_save"
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
break|break;
case|case
name|RUN_WITH_LAST_VALS
case|:
break|break;
default|default:
break|break;
block|}
if|if
condition|(
name|status
operator|==
name|STATUS_SUCCESS
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
name|STATUS_CALLING_ERROR
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

begin_ifdef
ifdef|#
directive|ifdef
name|__EMX__
end_ifdef

begin_function
specifier|static
name|gint
DECL|function|spawn_bz (gchar * filename,gchar * tmpname,gchar * parms,gint * pid)
name|spawn_bz
parameter_list|(
name|gchar
modifier|*
name|filename
parameter_list|,
name|gchar
modifier|*
name|tmpname
parameter_list|,
name|gchar
modifier|*
name|parms
parameter_list|,
name|gint
modifier|*
name|pid
parameter_list|)
block|{
name|FILE
modifier|*
name|f
decl_stmt|;
name|gint
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
literal|"wb"
argument_list|)
operator|)
condition|)
block|{
name|g_message
argument_list|(
literal|"bz: fopen failed: %s\n"
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
literal|"bz: dup2 failed: %s\n"
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
literal|"bzip2"
argument_list|,
literal|"bzip2"
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
literal|"bz: spawn failed: %s\n"
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
name|GStatusType
DECL|function|save_image (gchar * filename,gint32 image_ID,gint32 drawable_ID,gint32 run_mode)
name|save_image
parameter_list|(
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
name|FILE
modifier|*
name|f
decl_stmt|;
name|GParam
modifier|*
name|params
decl_stmt|;
name|gint
name|retvals
decl_stmt|;
name|gchar
modifier|*
name|ext
decl_stmt|;
name|gchar
modifier|*
name|tmpname
decl_stmt|;
name|gint
name|pid
decl_stmt|;
name|gint
name|status
decl_stmt|;
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
literal|"bz2: can't open bzip2ed file without a "
literal|"sensible extension\n"
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|STATUS_CALLING_ERROR
return|;
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
name|g_strdup
argument_list|(
name|params
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|params
argument_list|,
name|retvals
argument_list|)
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
operator|!
name|valid_file
argument_list|(
name|tmpname
argument_list|)
operator|||
name|params
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|!=
name|STATUS_SUCCESS
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
name|params
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
return|;
block|}
comment|/*   if (! file_save(image_ID, tmpname, tmpname)) { */
comment|/*     unlink (tmpname); */
comment|/*     return -1; */
comment|/*   } */
ifndef|#
directive|ifndef
name|__EMX__
comment|/* fork off a bzip2 process */
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
literal|"bz2: fork failed: %s\n"
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
name|STATUS_EXECUTION_ERROR
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
literal|"bz2: fopen failed: %s\n"
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
literal|"bz2: dup2 failed: %s\n"
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
comment|/* and bzip2 into it */
name|execlp
argument_list|(
literal|"bzip2"
argument_list|,
literal|"bzip2"
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
literal|"bz2: exec failed: bzip2: %s\n"
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
elseif|else
else|#
directive|else
comment|/* __EMX__ */
if|if
condition|(
name|spawn_bz
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
block|{
name|g_free
argument_list|(
name|tmpname
argument_list|)
expr_stmt|;
return|return
name|STATUS_EXECUTION_ERROR
return|;
block|}
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
literal|"bz2: bzip2 exited abnormally on file %s\n"
argument_list|,
name|tmpname
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tmpname
argument_list|)
expr_stmt|;
return|return
name|STATUS_EXECUTION_ERROR
return|;
block|}
block|}
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
name|STATUS_SUCCESS
return|;
block|}
end_function

begin_function
specifier|static
name|gint32
DECL|function|load_image (gchar * filename,gint32 run_mode,GStatusType * status)
name|load_image
parameter_list|(
name|gchar
modifier|*
name|filename
parameter_list|,
name|gint32
name|run_mode
parameter_list|,
name|GStatusType
modifier|*
name|status
comment|/* return value */
parameter_list|)
block|{
name|GParam
modifier|*
name|params
decl_stmt|;
name|gint
name|retvals
decl_stmt|;
name|gchar
modifier|*
name|ext
decl_stmt|;
name|gchar
modifier|*
name|tmpname
decl_stmt|;
name|gint
name|pid
decl_stmt|;
name|gint
name|process_status
decl_stmt|;
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
literal|"bz2: can't open bzip2ed file without a "
literal|"sensible extension\n"
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|status
operator|=
name|STATUS_CALLING_ERROR
expr_stmt|;
return|return
operator|-
literal|1
return|;
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
name|g_strdup
argument_list|(
name|params
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|params
argument_list|,
name|retvals
argument_list|)
expr_stmt|;
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
literal|"bz2: fork failed: %s\n"
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
name|STATUS_EXECUTION_ERROR
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
literal|"bz2: fopen failed: %s\n"
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
name|g_message
argument_list|(
literal|"bz2: dup2 failed: %s\n"
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
literal|"bzip2"
argument_list|,
literal|"bzip2"
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
literal|"bz2: exec failed: bunzip2: %s\n"
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
elseif|else
comment|/* parent process */
else|#
directive|else
comment|/* __EMX__ */
if|if
condition|(
name|spawn_bz
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
block|{
name|g_free
argument_list|(
name|tmpname
argument_list|)
expr_stmt|;
operator|*
name|status
operator|=
name|STATUS_EXECUTION_ERROR
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
endif|#
directive|endif
block|{
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
operator|!
name|WIFEXITED
argument_list|(
name|process_status
argument_list|)
operator|||
name|WEXITSTATUS
argument_list|(
name|process_status
argument_list|)
operator|!=
literal|0
condition|)
block|{
name|g_message
argument_list|(
literal|"bz2: bzip2 exited abnormally on file %s\n"
argument_list|,
name|filename
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
name|STATUS_EXECUTION_ERROR
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
block|}
comment|/* now that we un-bzip2ed it, load the temp file */
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
name|g_free
argument_list|(
name|tmpname
argument_list|)
expr_stmt|;
operator|*
name|status
operator|=
name|params
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
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
operator|!=
name|STATUS_SUCCESS
condition|)
block|{
return|return
operator|-
literal|1
return|;
block|}
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
specifier|static
name|gboolean
DECL|function|valid_file (gchar * filename)
name|valid_file
parameter_list|(
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
name|gchar
modifier|*
DECL|function|find_extension (gchar * filename)
name|find_extension
parameter_list|(
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
name|g_malloc
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
name|NULL
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
literal|".xcfbz2"
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
literal|".bz2"
argument_list|)
condition|)
block|{
return|return
name|ext
return|;
block|}
else|else
block|{
comment|/* we found ".bz2" so strip it, loop back, and look again */
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

