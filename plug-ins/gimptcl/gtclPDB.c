begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/***************************************************  * file: gtclPDB.c  *  * Copyright (c) 1996 Eric L. Hernes (erich@rrnet.com)  * All rights reserved.  *  * Redistribution and use in source and binary forms, with or without  * modification, are permitted provided that the following conditions  * are met:  * 1. Redistributions of source code must retain the above copyright  *    notice, this list of conditions and the following disclaimer.  * 2. The name of the author may not be used to endorse or promote products  *    derived from this software withough specific prior written permission  *  * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR  * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES  * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT  * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,  * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY  * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF  * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  *  * $Id$  */
end_comment

begin_include
include|#
directive|include
file|<ctype.h>
end_include

begin_include
include|#
directive|include
file|<tcl.h>
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

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|"gtcl.h"
end_include

begin_decl_stmt
DECL|variable|proc_types
specifier|static
name|char
modifier|*
name|proc_types
index|[]
init|=
block|{
literal|"undefined"
block|,
literal|"plug-in"
block|,
literal|"Extension"
block|, }
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|param_types
specifier|static
name|char
modifier|*
name|param_types
index|[]
init|=
block|{
literal|"int32"
block|,
literal|"int16"
block|,
literal|"int8"
block|,
literal|"float"
block|,
literal|"string"
block|,
literal|"int32array"
block|,
literal|"int16array"
block|,
literal|"int8array"
block|,
literal|"floatarray"
block|,
literal|"stringarray"
block|,
literal|"color"
block|,
literal|"region"
block|,
literal|"display"
block|,
literal|"image"
block|,
literal|"layer"
block|,
literal|"channel"
block|,
literal|"drawable"
block|,
literal|"selection"
block|,
literal|"boundary"
block|,
literal|"path"
block|,
literal|"status"
block|,
literal|"end"
block|}
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|static
name|int
name|str_to_typeenum
parameter_list|(
name|char
modifier|*
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|int
name|list_to_pdef
parameter_list|(
name|Tcl_Interp
modifier|*
name|interp
parameter_list|,
name|char
modifier|*
name|list
parameter_list|,
name|GParamDef
modifier|*
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  * add the procedural-database to a Tcl Interpreter  */
end_comment

begin_function
name|int
DECL|function|Gtcl_PDBInit (Tcl_Interp * interp)
name|Gtcl_PDBInit
parameter_list|(
name|Tcl_Interp
modifier|*
name|interp
parameter_list|)
block|{
name|char
modifier|*
modifier|*
name|proc_list
decl_stmt|;
name|char
modifier|*
name|proc_name
decl_stmt|;
name|char
modifier|*
name|proc_blurb
decl_stmt|;
name|char
modifier|*
name|proc_help
decl_stmt|;
name|char
modifier|*
name|proc_author
decl_stmt|;
name|char
modifier|*
name|proc_copyright
decl_stmt|;
name|char
modifier|*
name|proc_date
decl_stmt|;
name|int
name|proc_type
decl_stmt|;
name|int
name|nparams
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|GParamDef
modifier|*
name|params
decl_stmt|,
modifier|*
name|return_vals
decl_stmt|;
name|int
name|num_procs
decl_stmt|,
name|i
decl_stmt|,
name|j
decl_stmt|;
name|char
name|whole_proc
index|[
literal|2048
index|]
decl_stmt|;
name|char
name|arglist
index|[
literal|400
index|]
decl_stmt|;
name|char
name|carglist
index|[
literal|400
index|]
decl_stmt|;
name|gimp_query_database
argument_list|(
literal|".*"
argument_list|,
literal|".*"
argument_list|,
literal|".*"
argument_list|,
literal|".*"
argument_list|,
literal|".*"
argument_list|,
literal|".*"
argument_list|,
literal|".*"
argument_list|,
operator|&
name|num_procs
argument_list|,
operator|&
name|proc_list
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
name|num_procs
condition|;
name|i
operator|++
control|)
block|{
name|memset
argument_list|(
name|whole_proc
argument_list|,
literal|0
argument_list|,
literal|2048
argument_list|)
expr_stmt|;
name|memset
argument_list|(
name|arglist
argument_list|,
literal|0
argument_list|,
literal|400
argument_list|)
expr_stmt|;
name|memset
argument_list|(
name|carglist
argument_list|,
literal|0
argument_list|,
literal|400
argument_list|)
expr_stmt|;
name|proc_name
operator|=
name|strdup
argument_list|(
name|proc_list
index|[
name|i
index|]
argument_list|)
expr_stmt|;
comment|/*  fprintf(stderr, "(proc %d/%d %s)\n", i, num_procs, proc_name);*/
comment|/*  lookup the procedure  */
if|if
condition|(
name|gimp_query_procedure
argument_list|(
name|proc_name
argument_list|,
operator|&
name|proc_blurb
argument_list|,
operator|&
name|proc_help
argument_list|,
operator|&
name|proc_author
argument_list|,
operator|&
name|proc_copyright
argument_list|,
operator|&
name|proc_date
argument_list|,
operator|&
name|proc_type
argument_list|,
operator|&
name|nparams
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
operator|&
name|params
argument_list|,
operator|&
name|return_vals
argument_list|)
operator|==
name|TRUE
condition|)
block|{
name|cvtfrom
argument_list|(
name|proc_name
argument_list|)
expr_stmt|;
name|sprintf
argument_list|(
name|carglist
argument_list|,
literal|"gimp-run-procedure %s "
argument_list|,
name|proc_name
argument_list|)
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|nparams
condition|;
name|j
operator|++
control|)
block|{
if|if
condition|(
name|strcmp
argument_list|(
name|params
index|[
name|j
index|]
operator|.
name|name
argument_list|,
literal|"run_mode"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|strcat
argument_list|(
name|carglist
argument_list|,
literal|"1 "
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|strcat
argument_list|(
name|arglist
argument_list|,
name|params
index|[
name|j
index|]
operator|.
name|name
argument_list|)
expr_stmt|;
name|strcat
argument_list|(
name|arglist
argument_list|,
literal|" "
argument_list|)
expr_stmt|;
name|strcat
argument_list|(
name|carglist
argument_list|,
literal|"$"
argument_list|)
expr_stmt|;
name|strcat
argument_list|(
name|carglist
argument_list|,
name|params
index|[
name|j
index|]
operator|.
name|name
argument_list|)
expr_stmt|;
name|strcat
argument_list|(
name|carglist
argument_list|,
literal|" "
argument_list|)
expr_stmt|;
block|}
block|}
name|sprintf
argument_list|(
name|whole_proc
argument_list|,
literal|"proc %s {%s} {\n global GimpPDBCmd\n  set GimpPDBCmd %s\n   update\n   return [%s]\n}\n\n"
argument_list|,
name|proc_name
argument_list|,
name|arglist
argument_list|,
name|proc_name
argument_list|,
name|carglist
argument_list|)
expr_stmt|;
if|#
directive|if
literal|0
block|fprintf(stderr, "%s", whole_proc);
endif|#
directive|endif
name|Tcl_GlobalEval
argument_list|(
name|interp
argument_list|,
name|whole_proc
argument_list|)
expr_stmt|;
name|free
argument_list|(
name|proc_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|proc_blurb
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|proc_help
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|proc_author
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|proc_copyright
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|proc_date
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|params
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|TCL_OK
return|;
block|}
end_function

begin_comment
comment|/*  * run a procedure from the PDB, really the heart of  * this thing... Virtually everything goes through here.  */
end_comment

begin_function
name|int
DECL|function|Gtcl_GimpRunProc (ClientData data,Tcl_Interp * interp,int ac,char * av[])
name|Gtcl_GimpRunProc
parameter_list|(
name|ClientData
name|data
parameter_list|,
name|Tcl_Interp
modifier|*
name|interp
parameter_list|,
name|int
name|ac
parameter_list|,
name|char
modifier|*
name|av
index|[]
parameter_list|)
block|{
name|GParam
modifier|*
name|par
decl_stmt|,
modifier|*
name|vals
decl_stmt|;
name|char
modifier|*
name|p_blurb
decl_stmt|,
modifier|*
name|p_help
decl_stmt|,
modifier|*
name|p_author
decl_stmt|,
modifier|*
name|p_copy
decl_stmt|,
modifier|*
name|p_date
decl_stmt|,
modifier|*
modifier|*
name|rv_a
decl_stmt|;
name|int
name|p_type
decl_stmt|,
name|p_npar
decl_stmt|,
name|p_nrv
decl_stmt|;
name|GParamDef
modifier|*
name|p_par
decl_stmt|,
modifier|*
name|p_rv
decl_stmt|;
name|char
modifier|*
name|p_name
decl_stmt|;
name|int
name|i
decl_stmt|;
name|rv_a
operator|=
operator|(
name|char
operator|*
operator|*
operator|)
name|NULL
expr_stmt|;
name|p_name
operator|=
name|strdup
argument_list|(
name|av
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
comment|/* first try the name as given */
if|if
condition|(
name|gimp_query_procedure
argument_list|(
name|p_name
argument_list|,
operator|&
name|p_blurb
argument_list|,
operator|&
name|p_help
argument_list|,
operator|&
name|p_author
argument_list|,
operator|&
name|p_copy
argument_list|,
operator|&
name|p_date
argument_list|,
operator|&
name|p_type
argument_list|,
operator|&
name|p_npar
argument_list|,
operator|&
name|p_nrv
argument_list|,
operator|&
name|p_par
argument_list|,
operator|&
name|p_rv
argument_list|)
operator|==
name|FALSE
condition|)
block|{
comment|/* nope?, try `tr - _` */
name|cvtto
argument_list|(
name|p_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_query_procedure
argument_list|(
name|p_name
argument_list|,
operator|&
name|p_blurb
argument_list|,
operator|&
name|p_help
argument_list|,
operator|&
name|p_author
argument_list|,
operator|&
name|p_copy
argument_list|,
operator|&
name|p_date
argument_list|,
operator|&
name|p_type
argument_list|,
operator|&
name|p_npar
argument_list|,
operator|&
name|p_nrv
argument_list|,
operator|&
name|p_par
argument_list|,
operator|&
name|p_rv
argument_list|)
operator|==
name|FALSE
condition|)
block|{
name|Tcl_SetResult
argument_list|(
name|interp
argument_list|,
literal|"gimp-run-procedure invalid command: "
argument_list|,
name|TCL_STATIC
argument_list|)
expr_stmt|;
name|Tcl_AppendResult
argument_list|(
name|interp
argument_list|,
name|p_name
argument_list|,
operator|(
name|char
operator|*
operator|)
name|NULL
argument_list|)
expr_stmt|;
return|return
name|TCL_ERROR
return|;
block|}
block|}
name|ac
operator|-=
literal|2
expr_stmt|;
comment|/* subtract off own name and the proc name */
if|if
condition|(
name|ac
operator|!=
name|p_npar
condition|)
block|{
name|Tcl_SetResult
argument_list|(
name|interp
argument_list|,
literal|"gimp-run-procedure: "
argument_list|,
name|TCL_STATIC
argument_list|)
expr_stmt|;
name|Tcl_AppendResult
argument_list|(
name|interp
argument_list|,
name|p_name
argument_list|,
literal|" : Wrong # args\n"
argument_list|,
literal|"usage: "
argument_list|,
name|p_name
argument_list|,
operator|(
name|char
operator|*
operator|)
name|NULL
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
name|p_npar
condition|;
name|i
operator|++
control|)
block|{
name|Tcl_AppendResult
argument_list|(
name|interp
argument_list|,
literal|" "
argument_list|,
name|p_par
index|[
name|i
index|]
operator|.
name|name
argument_list|,
operator|(
name|char
operator|*
operator|)
name|NULL
argument_list|)
expr_stmt|;
block|}
return|return
name|TCL_ERROR
return|;
block|}
name|par
operator|=
operator|(
name|GParam
operator|*
operator|)
name|malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|GParam
argument_list|)
operator|*
name|ac
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
name|p_npar
condition|;
name|i
operator|++
control|)
block|{
name|par
index|[
name|i
index|]
operator|.
name|type
operator|=
name|p_par
index|[
name|i
index|]
operator|.
name|type
expr_stmt|;
block|}
if|if
condition|(
name|Argv_to_GParam
argument_list|(
name|interp
argument_list|,
name|p_name
argument_list|,
name|p_npar
argument_list|,
name|av
operator|+
literal|2
argument_list|,
name|par
argument_list|)
operator|==
name|TCL_ERROR
condition|)
block|{
name|free
argument_list|(
name|par
argument_list|)
expr_stmt|;
return|return
name|TCL_ERROR
return|;
block|}
name|DPRINTF
argument_list|(
literal|1
argument_list|,
operator|(
name|stderr
operator|,
literal|"\nGimp PDB Running: (%s:"
operator|,
name|p_name
operator|)
argument_list|)
expr_stmt|;
name|vals
operator|=
name|gimp_run_procedure2
argument_list|(
name|p_name
argument_list|,
operator|&
name|p_nrv
argument_list|,
name|p_npar
argument_list|,
name|par
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|vals
condition|)
block|{
name|Tcl_SetResult
argument_list|(
name|interp
argument_list|,
literal|"pdb: no status returned from"
argument_list|,
name|TCL_STATIC
argument_list|)
expr_stmt|;
name|Tcl_AppendResult
argument_list|(
name|interp
argument_list|,
name|p_name
argument_list|,
operator|(
name|char
operator|*
operator|)
name|NULL
argument_list|)
expr_stmt|;
name|free
argument_list|(
name|par
argument_list|)
expr_stmt|;
return|return
name|TCL_ERROR
return|;
block|}
name|DPRINTF
argument_list|(
literal|1
argument_list|,
operator|(
name|stderr
operator|,
literal|" returned %d)\n"
operator|,
name|vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|)
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
condition|)
block|{
case|case
name|STATUS_EXECUTION_ERROR
case|:
name|gimp_destroy_params
argument_list|(
name|vals
argument_list|,
name|p_nrv
argument_list|)
expr_stmt|;
name|free
argument_list|(
name|par
argument_list|)
expr_stmt|;
name|Tcl_SetResult
argument_list|(
name|interp
argument_list|,
literal|"pdb: exec failed for "
argument_list|,
name|TCL_STATIC
argument_list|)
expr_stmt|;
name|cvtfrom
argument_list|(
name|p_name
argument_list|)
expr_stmt|;
name|Tcl_AppendResult
argument_list|(
name|interp
argument_list|,
name|p_name
argument_list|,
operator|(
name|char
operator|*
operator|)
name|NULL
argument_list|)
expr_stmt|;
return|return
name|TCL_ERROR
return|;
break|break;
case|case
name|STATUS_CALLING_ERROR
case|:
name|gimp_destroy_params
argument_list|(
name|vals
argument_list|,
name|p_nrv
argument_list|)
expr_stmt|;
name|Tcl_SetResult
argument_list|(
name|interp
argument_list|,
literal|"pdb: invalid arguments for "
argument_list|,
name|TCL_STATIC
argument_list|)
expr_stmt|;
name|Tcl_AppendResult
argument_list|(
name|interp
argument_list|,
name|p_name
argument_list|,
operator|(
name|char
operator|*
operator|)
name|NULL
argument_list|)
expr_stmt|;
return|return
name|TCL_ERROR
return|;
break|break;
case|case
name|STATUS_SUCCESS
case|:
name|rv_a
operator|=
operator|(
name|char
operator|*
operator|*
operator|)
name|malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|char
operator|*
argument_list|)
operator|*
name|p_nrv
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|GParam_to_Argv
argument_list|(
name|interp
argument_list|,
name|p_name
argument_list|,
name|p_nrv
operator|-
literal|1
argument_list|,
operator|&
name|vals
index|[
literal|1
index|]
argument_list|,
name|rv_a
argument_list|)
operator|==
name|TCL_ERROR
condition|)
block|{
name|gimp_destroy_params
argument_list|(
name|vals
argument_list|,
name|p_nrv
argument_list|)
expr_stmt|;
return|return
name|TCL_ERROR
return|;
block|}
block|}
if|if
condition|(
name|p_nrv
operator|==
literal|2
condition|)
block|{
name|Tcl_SetResult
argument_list|(
name|interp
argument_list|,
name|rv_a
index|[
literal|0
index|]
argument_list|,
name|TCL_VOLATILE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|char
modifier|*
name|t
decl_stmt|;
name|t
operator|=
name|Tcl_Merge
argument_list|(
name|p_nrv
operator|-
literal|1
argument_list|,
name|rv_a
argument_list|)
expr_stmt|;
name|Tcl_SetResult
argument_list|(
name|interp
argument_list|,
name|t
argument_list|,
name|TCL_DYNAMIC
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|p_nrv
operator|-
literal|1
condition|;
name|i
operator|++
control|)
block|{
name|free
argument_list|(
name|rv_a
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
name|free
argument_list|(
operator|(
name|char
operator|*
operator|)
name|rv_a
argument_list|)
expr_stmt|;
name|free
argument_list|(
name|par
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|p_blurb
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|p_help
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|p_author
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|p_copy
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|p_date
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|p_par
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|p_rv
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|vals
argument_list|,
name|p_nrv
argument_list|)
expr_stmt|;
return|return
name|TCL_OK
return|;
block|}
end_function

begin_comment
comment|/*  * query the database for info on a procedure  */
end_comment

begin_function
name|int
DECL|function|Gtcl_QueryDBProc (ClientData data,Tcl_Interp * interp,int ac,char * av[])
name|Gtcl_QueryDBProc
parameter_list|(
name|ClientData
name|data
parameter_list|,
name|Tcl_Interp
modifier|*
name|interp
parameter_list|,
name|int
name|ac
parameter_list|,
name|char
modifier|*
name|av
index|[]
parameter_list|)
block|{
name|char
modifier|*
name|blurb
decl_stmt|,
modifier|*
name|help
decl_stmt|,
modifier|*
name|author
decl_stmt|,
modifier|*
name|copyright
decl_stmt|,
modifier|*
name|date
decl_stmt|,
modifier|*
modifier|*
name|tl0
decl_stmt|,
modifier|*
name|tl1
index|[
literal|3
index|]
decl_stmt|;
name|char
modifier|*
name|t
decl_stmt|,
modifier|*
name|p_name
decl_stmt|;
name|int
name|type
decl_stmt|,
name|npar
decl_stmt|,
name|nrv
decl_stmt|,
name|i
decl_stmt|;
name|GParamDef
modifier|*
name|par_d
decl_stmt|,
modifier|*
name|rv_d
decl_stmt|;
if|if
condition|(
name|ac
operator|!=
literal|2
condition|)
block|{
name|Tcl_SetResult
argument_list|(
name|interp
argument_list|,
literal|"gimp-query-dbproc: wrong # arguments"
argument_list|,
name|TCL_STATIC
argument_list|)
expr_stmt|;
return|return
name|TCL_ERROR
return|;
block|}
name|p_name
operator|=
name|strdup
argument_list|(
name|av
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
name|cvtto
argument_list|(
name|p_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_query_procedure
argument_list|(
name|av
index|[
literal|1
index|]
argument_list|,
operator|&
name|blurb
argument_list|,
operator|&
name|help
argument_list|,
operator|&
name|author
argument_list|,
operator|&
name|copyright
argument_list|,
operator|&
name|date
argument_list|,
operator|&
name|type
argument_list|,
operator|&
name|npar
argument_list|,
operator|&
name|nrv
argument_list|,
operator|&
name|par_d
argument_list|,
operator|&
name|rv_d
argument_list|)
operator|==
name|FALSE
condition|)
block|{
if|if
condition|(
name|gimp_query_procedure
argument_list|(
name|p_name
argument_list|,
operator|&
name|blurb
argument_list|,
operator|&
name|help
argument_list|,
operator|&
name|author
argument_list|,
operator|&
name|copyright
argument_list|,
operator|&
name|date
argument_list|,
operator|&
name|type
argument_list|,
operator|&
name|npar
argument_list|,
operator|&
name|nrv
argument_list|,
operator|&
name|par_d
argument_list|,
operator|&
name|rv_d
argument_list|)
operator|==
name|FALSE
condition|)
block|{
name|Tcl_SetResult
argument_list|(
name|interp
argument_list|,
literal|"gimp-query-dbproc: invalid command: "
argument_list|,
name|TCL_STATIC
argument_list|)
expr_stmt|;
name|Tcl_AppendResult
argument_list|(
name|interp
argument_list|,
name|av
index|[
literal|1
index|]
argument_list|,
operator|(
name|char
operator|*
operator|)
name|NULL
argument_list|)
expr_stmt|;
return|return
name|TCL_ERROR
return|;
block|}
block|}
name|free
argument_list|(
name|p_name
argument_list|)
expr_stmt|;
name|Tcl_AppendElement
argument_list|(
name|interp
argument_list|,
name|av
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
name|Tcl_AppendElement
argument_list|(
name|interp
argument_list|,
name|blurb
argument_list|)
expr_stmt|;
name|Tcl_AppendElement
argument_list|(
name|interp
argument_list|,
name|help
argument_list|)
expr_stmt|;
name|Tcl_AppendElement
argument_list|(
name|interp
argument_list|,
name|author
argument_list|)
expr_stmt|;
name|Tcl_AppendElement
argument_list|(
name|interp
argument_list|,
name|copyright
argument_list|)
expr_stmt|;
name|Tcl_AppendElement
argument_list|(
name|interp
argument_list|,
name|date
argument_list|)
expr_stmt|;
name|Tcl_AppendElement
argument_list|(
name|interp
argument_list|,
name|proc_types
index|[
name|type
index|]
argument_list|)
expr_stmt|;
name|tl0
operator|=
operator|(
name|char
operator|*
operator|*
operator|)
name|malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|char
operator|*
argument_list|)
operator|*
name|npar
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
name|npar
condition|;
name|i
operator|++
control|)
block|{
name|tl1
index|[
literal|0
index|]
operator|=
name|param_types
index|[
name|par_d
index|[
name|i
index|]
operator|.
name|type
index|]
expr_stmt|;
name|tl1
index|[
literal|1
index|]
operator|=
name|par_d
index|[
name|i
index|]
operator|.
name|name
expr_stmt|;
name|tl1
index|[
literal|2
index|]
operator|=
name|par_d
index|[
name|i
index|]
operator|.
name|description
expr_stmt|;
name|t
operator|=
name|Tcl_Merge
argument_list|(
literal|3
argument_list|,
name|tl1
argument_list|)
expr_stmt|;
name|tl0
index|[
name|i
index|]
operator|=
name|t
expr_stmt|;
block|}
name|t
operator|=
name|Tcl_Merge
argument_list|(
name|npar
argument_list|,
name|tl0
argument_list|)
expr_stmt|;
name|Tcl_AppendElement
argument_list|(
name|interp
argument_list|,
name|t
argument_list|)
expr_stmt|;
name|Tcl_Free
argument_list|(
name|t
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
name|npar
condition|;
name|i
operator|++
control|)
name|Tcl_Free
argument_list|(
name|tl0
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|free
argument_list|(
name|tl0
argument_list|)
expr_stmt|;
name|tl0
operator|=
operator|(
name|char
operator|*
operator|*
operator|)
name|malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|char
operator|*
argument_list|)
operator|*
name|nrv
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
name|nrv
condition|;
name|i
operator|++
control|)
block|{
name|tl1
index|[
literal|0
index|]
operator|=
name|param_types
index|[
name|rv_d
index|[
name|i
index|]
operator|.
name|type
index|]
expr_stmt|;
name|tl1
index|[
literal|1
index|]
operator|=
name|rv_d
index|[
name|i
index|]
operator|.
name|name
expr_stmt|;
name|tl1
index|[
literal|2
index|]
operator|=
name|rv_d
index|[
name|i
index|]
operator|.
name|description
expr_stmt|;
name|t
operator|=
name|Tcl_Merge
argument_list|(
literal|3
argument_list|,
name|tl1
argument_list|)
expr_stmt|;
name|tl0
index|[
name|i
index|]
operator|=
name|t
expr_stmt|;
block|}
name|t
operator|=
name|Tcl_Merge
argument_list|(
name|nrv
argument_list|,
name|tl0
argument_list|)
expr_stmt|;
name|Tcl_AppendElement
argument_list|(
name|interp
argument_list|,
name|t
argument_list|)
expr_stmt|;
name|Tcl_Free
argument_list|(
name|t
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
name|nrv
condition|;
name|i
operator|++
control|)
name|Tcl_Free
argument_list|(
name|tl0
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|free
argument_list|(
name|tl0
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|blurb
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|help
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|author
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|copyright
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|date
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|par_d
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|rv_d
argument_list|)
expr_stmt|;
return|return
name|TCL_OK
return|;
block|}
end_function

begin_comment
comment|/*  * query the database for any or all procedures  */
end_comment

begin_function
name|int
DECL|function|Gtcl_QueryDB (ClientData data,Tcl_Interp * interp,int ac,char * av[])
name|Gtcl_QueryDB
parameter_list|(
name|ClientData
name|data
parameter_list|,
name|Tcl_Interp
modifier|*
name|interp
parameter_list|,
name|int
name|ac
parameter_list|,
name|char
modifier|*
name|av
index|[]
parameter_list|)
block|{
name|char
modifier|*
modifier|*
name|procs
decl_stmt|,
modifier|*
name|r
decl_stmt|,
modifier|*
name|p_name
decl_stmt|;
name|int
name|nproc
decl_stmt|,
name|i
decl_stmt|;
if|if
condition|(
name|ac
operator|!=
literal|8
condition|)
block|{
name|Tcl_SetResult
argument_list|(
name|interp
argument_list|,
literal|"gimp-query-db: wrong # args"
argument_list|,
name|TCL_STATIC
argument_list|)
expr_stmt|;
return|return
name|TCL_ERROR
return|;
block|}
name|p_name
operator|=
name|strdup
argument_list|(
name|av
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
name|cvtto
argument_list|(
name|p_name
argument_list|)
expr_stmt|;
name|gimp_query_database
argument_list|(
name|p_name
argument_list|,
name|av
index|[
literal|2
index|]
argument_list|,
name|av
index|[
literal|3
index|]
argument_list|,
name|av
index|[
literal|4
index|]
argument_list|,
name|av
index|[
literal|5
index|]
argument_list|,
name|av
index|[
literal|6
index|]
argument_list|,
name|av
index|[
literal|7
index|]
argument_list|,
operator|&
name|nproc
argument_list|,
operator|&
name|procs
argument_list|)
expr_stmt|;
name|free
argument_list|(
name|p_name
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
name|nproc
condition|;
name|i
operator|++
control|)
block|{
name|cvtfrom
argument_list|(
name|procs
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
name|r
operator|=
name|Tcl_Merge
argument_list|(
name|nproc
argument_list|,
name|procs
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|nproc
condition|;
name|i
operator|++
control|)
block|{
name|free
argument_list|(
name|procs
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
name|free
argument_list|(
name|procs
argument_list|)
expr_stmt|;
name|Tcl_SetResult
argument_list|(
name|interp
argument_list|,
name|r
argument_list|,
name|TCL_DYNAMIC
argument_list|)
expr_stmt|;
return|return
name|TCL_OK
return|;
block|}
end_function

begin_comment
comment|/*  * install a procedure in the database  */
end_comment

begin_function
name|int
DECL|function|Gtcl_InstallProc (ClientData data,Tcl_Interp * interp,int ac,char * av[])
name|Gtcl_InstallProc
parameter_list|(
name|ClientData
name|data
parameter_list|,
name|Tcl_Interp
modifier|*
name|interp
parameter_list|,
name|int
name|ac
parameter_list|,
name|char
modifier|*
name|av
index|[]
parameter_list|)
block|{
name|GParamDef
modifier|*
name|args_p
decl_stmt|,
modifier|*
name|rets_p
decl_stmt|;
name|char
modifier|*
modifier|*
name|args
decl_stmt|,
modifier|*
modifier|*
name|rets
decl_stmt|;
name|int
name|narg
decl_stmt|,
name|nret
decl_stmt|,
name|i
decl_stmt|,
name|type
decl_stmt|;
if|if
condition|(
name|ac
operator|!=
literal|12
condition|)
block|{
name|Tcl_SetResult
argument_list|(
name|interp
argument_list|,
literal|"gimp-install-procedure: wrong # args:\n"
argument_list|,
name|TCL_STATIC
argument_list|)
expr_stmt|;
name|Tcl_AppendResult
argument_list|(
name|interp
argument_list|,
literal|"usage: "
argument_list|,
name|av
index|[
literal|0
index|]
argument_list|,
literal|"<name><blurb><help><author><copyright><date> "
literal|"<menu-path><image-types><type><args><retvals>"
argument_list|,
operator|(
name|char
operator|*
operator|)
name|NULL
argument_list|)
expr_stmt|;
return|return
operator|(
name|TCL_ERROR
operator|)
return|;
block|}
if|if
condition|(
name|strncasecmp
argument_list|(
literal|"plug"
argument_list|,
name|av
index|[
literal|9
index|]
argument_list|,
literal|4
argument_list|)
operator|==
literal|0
condition|)
block|{
name|type
operator|=
name|PROC_PLUG_IN
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strcasecmp
argument_list|(
literal|"extension"
argument_list|,
name|av
index|[
literal|9
index|]
argument_list|)
operator|==
literal|0
condition|)
block|{
name|type
operator|=
name|PROC_EXTENSION
expr_stmt|;
block|}
else|else
block|{
name|Tcl_SetResult
argument_list|(
name|interp
argument_list|,
literal|"unknown procedure type: `"
argument_list|,
name|TCL_STATIC
argument_list|)
expr_stmt|;
name|Tcl_AppendResult
argument_list|(
name|interp
argument_list|,
name|av
index|[
literal|9
index|]
argument_list|,
literal|"'"
argument_list|,
operator|(
name|char
operator|*
operator|)
name|NULL
argument_list|)
expr_stmt|;
return|return
name|TCL_ERROR
return|;
block|}
if|if
condition|(
name|Tcl_SplitList
argument_list|(
name|interp
argument_list|,
name|av
index|[
literal|10
index|]
argument_list|,
operator|&
name|narg
argument_list|,
operator|&
name|args
argument_list|)
operator|==
name|TCL_ERROR
condition|)
block|{
return|return
operator|(
name|TCL_ERROR
operator|)
return|;
block|}
if|if
condition|(
name|Tcl_SplitList
argument_list|(
name|interp
argument_list|,
name|av
index|[
literal|11
index|]
argument_list|,
operator|&
name|nret
argument_list|,
operator|&
name|rets
argument_list|)
operator|==
name|TCL_ERROR
condition|)
block|{
return|return
operator|(
name|TCL_ERROR
operator|)
return|;
block|}
name|args_p
operator|=
operator|(
name|GParamDef
operator|*
operator|)
name|malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|GParamDef
argument_list|)
operator|*
name|narg
argument_list|)
expr_stmt|;
name|rets_p
operator|=
operator|(
name|GParamDef
operator|*
operator|)
name|malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|GParamDef
argument_list|)
operator|*
name|nret
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
name|narg
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|list_to_pdef
argument_list|(
name|interp
argument_list|,
name|args
index|[
name|i
index|]
argument_list|,
operator|&
name|args_p
index|[
name|i
index|]
argument_list|)
operator|==
name|TCL_ERROR
condition|)
block|{
return|return
name|TCL_ERROR
return|;
block|}
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|nret
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|list_to_pdef
argument_list|(
name|interp
argument_list|,
name|rets
index|[
name|i
index|]
argument_list|,
operator|&
name|rets_p
index|[
name|i
index|]
argument_list|)
operator|==
name|TCL_ERROR
condition|)
block|{
return|return
name|TCL_ERROR
return|;
block|}
block|}
if|#
directive|if
literal|0
block|fprintf(stderr, "proc_inst: %s [arg: %d] [ret: %d]\n", av[1], narg, nret);    fprintf(stderr, "g_i_p(n=%s,\n      b=%s,\n      h=%s,\n      a=%s,\n", 	  av[1], av[2], av[3], av[4]);   fprintf(stderr, "      c=%s,\n      d=%s,\n      m=%s,\n      i=%s,\n", 	  av[5], av[6], av[7], av[8]);   fprintf(stderr, "      t=%d,\n     np=%d,\n     nr=%d)\n", 	  type, narg, nret);
endif|#
directive|endif
name|gimp_install_procedure
argument_list|(
name|av
index|[
literal|1
index|]
argument_list|,
name|av
index|[
literal|2
index|]
argument_list|,
name|av
index|[
literal|3
index|]
argument_list|,
name|av
index|[
literal|4
index|]
argument_list|,
name|av
index|[
literal|5
index|]
argument_list|,
name|av
index|[
literal|6
index|]
argument_list|,
name|av
index|[
literal|7
index|]
argument_list|,
name|av
index|[
literal|8
index|]
argument_list|,
name|type
argument_list|,
name|narg
argument_list|,
name|nret
argument_list|,
name|args_p
argument_list|,
name|rets_p
argument_list|)
expr_stmt|;
name|free
argument_list|(
name|args_p
argument_list|)
expr_stmt|;
name|free
argument_list|(
name|rets_p
argument_list|)
expr_stmt|;
return|return
name|TCL_OK
return|;
block|}
end_function

begin_comment
comment|/*  * the libgimp dispatcher -- needed for plugins  */
end_comment

begin_function
name|int
DECL|function|Gtcl_GimpMain (ClientData data,Tcl_Interp * interp,int argc,char * argv[])
name|Gtcl_GimpMain
parameter_list|(
name|ClientData
name|data
parameter_list|,
name|Tcl_Interp
modifier|*
name|interp
parameter_list|,
name|int
name|argc
parameter_list|,
name|char
modifier|*
name|argv
index|[]
parameter_list|)
block|{
name|char
modifier|*
modifier|*
name|av
decl_stmt|,
modifier|*
modifier|*
name|av0
decl_stmt|,
modifier|*
name|av1
decl_stmt|;
name|int
name|ac0
decl_stmt|,
name|i
decl_stmt|;
name|av1
operator|=
name|Tcl_GetVar
argument_list|(
name|interp
argument_list|,
literal|"argv"
argument_list|,
name|TCL_GLOBAL_ONLY
argument_list|)
expr_stmt|;
name|Tcl_SplitList
argument_list|(
name|interp
argument_list|,
name|av1
argument_list|,
operator|&
name|ac0
argument_list|,
operator|&
name|av0
argument_list|)
expr_stmt|;
name|av
operator|=
operator|(
name|char
operator|*
operator|*
operator|)
name|malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|char
operator|*
argument_list|)
operator|*
name|ac0
operator|+
literal|1
argument_list|)
expr_stmt|;
name|av
index|[
literal|0
index|]
operator|=
name|Tcl_GetVar
argument_list|(
name|interp
argument_list|,
literal|"argv0"
argument_list|,
name|TCL_GLOBAL_ONLY
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
name|ac0
condition|;
name|i
operator|++
control|)
block|{
name|av
index|[
name|i
operator|+
literal|1
index|]
operator|=
name|av0
index|[
name|i
index|]
expr_stmt|;
block|}
name|gimp_main
argument_list|(
name|ac0
operator|+
literal|1
argument_list|,
name|av
argument_list|)
expr_stmt|;
name|free
argument_list|(
operator|(
name|char
operator|*
operator|)
name|av
argument_list|)
expr_stmt|;
name|free
argument_list|(
operator|(
name|char
operator|*
operator|)
name|av0
argument_list|)
expr_stmt|;
return|return
name|TCL_OK
return|;
block|}
end_function

begin_comment
comment|/*  * static conveninence functions...  */
end_comment

begin_comment
comment|/*  * translate a 3 element list into a ParamDef structure  */
end_comment

begin_function
specifier|static
name|int
DECL|function|list_to_pdef (Tcl_Interp * interp,char * list,GParamDef * p)
name|list_to_pdef
parameter_list|(
name|Tcl_Interp
modifier|*
name|interp
parameter_list|,
name|char
modifier|*
name|list
parameter_list|,
name|GParamDef
modifier|*
name|p
parameter_list|)
block|{
name|char
modifier|*
modifier|*
name|l
decl_stmt|;
name|int
name|n
decl_stmt|,
name|t
decl_stmt|;
if|if
condition|(
name|Tcl_SplitList
argument_list|(
name|interp
argument_list|,
name|list
argument_list|,
operator|&
name|n
argument_list|,
operator|&
name|l
argument_list|)
operator|==
name|TCL_ERROR
condition|)
block|{
return|return
name|TCL_ERROR
return|;
block|}
if|if
condition|(
name|n
operator|!=
literal|3
condition|)
block|{
name|Tcl_SetResult
argument_list|(
name|interp
argument_list|,
literal|"ParamDef wasn't 3 elements"
argument_list|,
name|TCL_STATIC
argument_list|)
expr_stmt|;
return|return
name|TCL_ERROR
return|;
block|}
if|if
condition|(
operator|(
name|t
operator|=
name|str_to_typeenum
argument_list|(
name|l
index|[
literal|0
index|]
argument_list|)
operator|)
operator|==
operator|-
literal|1
condition|)
block|{
name|Tcl_SetResult
argument_list|(
name|interp
argument_list|,
literal|"ParamDef: unknown type `"
argument_list|,
name|TCL_STATIC
argument_list|)
expr_stmt|;
name|Tcl_AppendResult
argument_list|(
name|interp
argument_list|,
name|l
index|[
literal|0
index|]
argument_list|,
literal|"'"
argument_list|,
operator|(
name|char
operator|*
operator|)
name|NULL
argument_list|)
expr_stmt|;
return|return
operator|(
name|TCL_ERROR
operator|)
return|;
block|}
name|p
operator|->
name|type
operator|=
name|t
expr_stmt|;
name|p
operator|->
name|name
operator|=
name|strdup
argument_list|(
name|l
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
name|p
operator|->
name|description
operator|=
name|strdup
argument_list|(
name|l
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
name|Tcl_Free
argument_list|(
operator|(
name|char
operator|*
operator|)
name|l
argument_list|)
expr_stmt|;
return|return
name|TCL_OK
return|;
block|}
end_function

begin_function
specifier|static
name|int
DECL|function|str_to_typeenum (char * type)
name|str_to_typeenum
parameter_list|(
name|char
modifier|*
name|type
parameter_list|)
block|{
name|int
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
sizeof|sizeof
argument_list|(
name|param_types
argument_list|)
condition|;
name|i
operator|++
control|)
if|if
condition|(
name|strcasecmp
argument_list|(
name|type
argument_list|,
name|param_types
index|[
name|i
index|]
argument_list|)
operator|==
literal|0
condition|)
return|return
name|i
return|;
return|return
operator|-
literal|1
return|;
block|}
end_function

end_unit

