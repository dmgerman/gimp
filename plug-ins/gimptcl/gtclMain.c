begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/***************************************************  * file: gtclMain.c  *  * Copyright (c) 1996 Eric L. Hernes (erich@rrnet.com)  * All rights reserved.  *  * Redistribution and use in source and binary forms, with or without  * modification, are permitted provided that the following conditions  * are met:  * 1. Redistributions of source code must retain the above copyright  *    notice, this list of conditions and the following disclaimer.  * 2. The name of the author may not be used to endorse or promote products  *    derived from this software withough specific prior written permission  *  * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR  * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES  * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT  * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,  * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY  * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF  * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  *  * $Id$  */
end_comment

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|<tcl.h>
end_include

begin_include
include|#
directive|include
file|<tk.h>
end_include

begin_include
include|#
directive|include
file|"gtcl.h"
end_include

begin_decl_stmt
DECL|variable|debuglevel
name|int
name|debuglevel
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_function_decl
name|int
name|Gtcl_Init
parameter_list|(
name|Tcl_Interp
modifier|*
name|interp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gtcl_init
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gtcl_quit
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gtcl_query
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gtcl_run
parameter_list|(
name|char
modifier|*
name|name
parameter_list|,
name|int
name|nparm
parameter_list|,
name|GParam
modifier|*
name|p
parameter_list|,
name|int
modifier|*
name|nrv
parameter_list|,
name|GParam
modifier|*
modifier|*
name|rv
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|Gimptcl_Init
parameter_list|(
name|Tcl_Interp
modifier|*
name|interp
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|theInterp
name|Tcl_Interp
modifier|*
name|theInterp
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|PLUG_IN_INFO
name|GPlugInInfo
name|PLUG_IN_INFO
init|=
block|{
name|gtcl_init
block|,
name|gtcl_quit
block|,
name|gtcl_query
block|,
name|gtcl_run
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|int
DECL|function|main (int ac,char * av[])
name|main
parameter_list|(
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
name|tcllib_p
decl_stmt|,
modifier|*
name|tcllib
decl_stmt|;
name|char
modifier|*
name|tklib_p
decl_stmt|,
modifier|*
name|tklib
decl_stmt|;
comment|/*  fprintf(stderr, "gimptcl: %d %s\n", ac, av[1]);*/
if|if
condition|(
name|ac
operator|<
literal|2
condition|)
block|{
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"usage: %s<script>\n"
argument_list|,
name|av
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
name|exit
argument_list|(
literal|1
argument_list|)
expr_stmt|;
block|}
name|theInterp
operator|=
name|Tcl_CreateInterp
argument_list|()
expr_stmt|;
name|Tcl_SetVar
argument_list|(
name|theInterp
argument_list|,
literal|"tcl_interactive"
argument_list|,
literal|"1"
argument_list|,
name|TCL_GLOBAL_ONLY
argument_list|)
expr_stmt|;
name|tcllib_p
operator|=
name|Tcl_GetVar
argument_list|(
name|theInterp
argument_list|,
literal|"tcl_library"
argument_list|,
name|TCL_GLOBAL_ONLY
argument_list|)
expr_stmt|;
name|tcllib
operator|=
name|malloc
argument_list|(
name|strlen
argument_list|(
name|tcllib_p
argument_list|)
operator|+
literal|10
argument_list|)
expr_stmt|;
name|sprintf
argument_list|(
name|tcllib
argument_list|,
literal|"%s/init.tcl"
argument_list|,
name|tcllib_p
argument_list|)
expr_stmt|;
name|Tcl_EvalFile
argument_list|(
name|theInterp
argument_list|,
name|tcllib
argument_list|)
expr_stmt|;
name|free
argument_list|(
name|tcllib
argument_list|)
expr_stmt|;
name|free
argument_list|(
name|tcllib_p
argument_list|)
expr_stmt|;
if|if
condition|(
name|Tk_Init
argument_list|(
name|theInterp
argument_list|)
operator|==
name|TCL_OK
condition|)
block|{
name|tklib_p
operator|=
name|Tcl_GetVar
argument_list|(
name|theInterp
argument_list|,
literal|"tk_library"
argument_list|,
name|TCL_GLOBAL_ONLY
argument_list|)
expr_stmt|;
name|tklib
operator|=
name|malloc
argument_list|(
name|strlen
argument_list|(
name|tklib_p
argument_list|)
operator|+
literal|10
argument_list|)
expr_stmt|;
name|sprintf
argument_list|(
name|tklib
argument_list|,
literal|"%s/init.tcl"
argument_list|,
name|tklib_p
argument_list|)
expr_stmt|;
name|Tcl_EvalFile
argument_list|(
name|theInterp
argument_list|,
name|tklib
argument_list|)
expr_stmt|;
name|free
argument_list|(
name|tklib_p
argument_list|)
expr_stmt|;
name|free
argument_list|(
name|tklib
argument_list|)
expr_stmt|;
block|}
name|Gimptcl_Init
argument_list|(
name|theInterp
argument_list|)
expr_stmt|;
name|Tcl_EvalFile
argument_list|(
name|theInterp
argument_list|,
name|av
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
return|return
name|gimp_main
argument_list|(
name|ac
operator|-
literal|1
argument_list|,
name|av
operator|+
literal|1
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  * add Gimp package to a Tcl Interp  */
end_comment

begin_function
name|int
DECL|function|Gimptcl_Init (Tcl_Interp * interp)
name|Gimptcl_Init
parameter_list|(
name|Tcl_Interp
modifier|*
name|interp
parameter_list|)
block|{
name|Tcl_CreateCommand
argument_list|(
name|interp
argument_list|,
literal|"gimp-run-procedure"
argument_list|,
name|Gtcl_GimpRunProc
argument_list|,
operator|(
name|ClientData
operator|)
name|NULL
argument_list|,
operator|(
name|Tcl_CmdDeleteProc
operator|*
operator|)
name|NULL
argument_list|)
expr_stmt|;
name|Tcl_CreateCommand
argument_list|(
name|interp
argument_list|,
literal|"gimp-query-dbproc"
argument_list|,
name|Gtcl_QueryDBProc
argument_list|,
operator|(
name|ClientData
operator|)
name|NULL
argument_list|,
operator|(
name|Tcl_CmdDeleteProc
operator|*
operator|)
name|NULL
argument_list|)
expr_stmt|;
name|Tcl_CreateCommand
argument_list|(
name|interp
argument_list|,
literal|"gimp-query-db"
argument_list|,
name|Gtcl_QueryDB
argument_list|,
operator|(
name|ClientData
operator|)
name|NULL
argument_list|,
operator|(
name|Tcl_CmdDeleteProc
operator|*
operator|)
name|NULL
argument_list|)
expr_stmt|;
name|Tcl_CreateCommand
argument_list|(
name|interp
argument_list|,
literal|"gimp-install-procedure"
argument_list|,
name|Gtcl_InstallProc
argument_list|,
operator|(
name|ClientData
operator|)
name|NULL
argument_list|,
operator|(
name|Tcl_CmdDeleteProc
operator|*
operator|)
name|NULL
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|SHLIB_METHOD
name|Tcl_CreateCommand
argument_list|(
name|interp
argument_list|,
literal|"gimp-main"
argument_list|,
name|Gtcl_GimpMain
argument_list|,
operator|(
name|ClientData
operator|)
name|NULL
argument_list|,
operator|(
name|Tcl_CmdDeleteProc
operator|*
operator|)
name|NULL
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|Tcl_LinkVar
argument_list|(
name|interp
argument_list|,
literal|"DebugLevel"
argument_list|,
operator|(
name|char
operator|*
operator|)
operator|&
name|debuglevel
argument_list|,
name|TCL_LINK_INT
argument_list|)
expr_stmt|;
comment|/*    * we have to belay adding PDB and Const to the interp    * until gtcl_run is called, because we need    * gimp_main to setup the IPC to the PDB.    */
name|theInterp
operator|=
name|interp
expr_stmt|;
return|return
name|TCL_OK
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gtcl_init (void)
name|gtcl_init
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
name|theInterp
operator|==
name|NULL
condition|)
block|{
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"gtcl_init, theInterp not initialized\n"
argument_list|)
expr_stmt|;
return|return;
block|}
name|Tcl_Eval
argument_list|(
name|theInterp
argument_list|,
literal|"info procs gimptcl_init"
argument_list|)
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|theInterp
operator|->
name|result
argument_list|,
literal|"gimptcl_init"
argument_list|)
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|Tcl_Eval
argument_list|(
name|theInterp
argument_list|,
literal|"gimptcl_init"
argument_list|)
operator|==
name|TCL_ERROR
condition|)
block|{
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"Error in gtcl_init:\n\t%s\n"
argument_list|,
name|theInterp
operator|->
name|result
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/*      printf("%s\n", theInterp->result);*/
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gtcl_quit (void)
name|gtcl_quit
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
name|theInterp
operator|==
name|NULL
condition|)
block|{
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"gtcl_quit, theInterp not initialized\n"
argument_list|)
expr_stmt|;
return|return;
block|}
name|Tcl_Eval
argument_list|(
name|theInterp
argument_list|,
literal|"info procs gimptcl_quit"
argument_list|)
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|theInterp
operator|->
name|result
argument_list|,
literal|"gimptcl_quit"
argument_list|)
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|Tcl_Eval
argument_list|(
name|theInterp
argument_list|,
literal|"gimptcl_quit"
argument_list|)
operator|==
name|TCL_ERROR
condition|)
block|{
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"Error in gtcl_quit:\n\t%s\n"
argument_list|,
name|theInterp
operator|->
name|result
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/*      printf("%s\n", theInterp->result);*/
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gtcl_query (void)
name|gtcl_query
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
name|theInterp
operator|==
name|NULL
condition|)
block|{
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"gtcl_quit, theInterp not initialized\n"
argument_list|)
expr_stmt|;
return|return;
block|}
name|Tcl_Eval
argument_list|(
name|theInterp
argument_list|,
literal|"info procs gimptcl_query"
argument_list|)
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|theInterp
operator|->
name|result
argument_list|,
literal|"gimptcl_query"
argument_list|)
operator|!=
literal|0
condition|)
block|{
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"Whoa there, no query\n"
argument_list|)
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|Tcl_Eval
argument_list|(
name|theInterp
argument_list|,
literal|"gimptcl_query"
argument_list|)
operator|==
name|TCL_ERROR
condition|)
block|{
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"Error in gtcl_query:%s\n"
argument_list|,
name|theInterp
operator|->
name|result
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/*      printf("%s\n", theInterp->result);*/
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gtcl_run (char * name,int nparm,GParam * p,int * nrv,GParam ** rv)
name|gtcl_run
parameter_list|(
name|char
modifier|*
name|name
parameter_list|,
name|int
name|nparm
parameter_list|,
name|GParam
modifier|*
name|p
parameter_list|,
name|int
modifier|*
name|nrv
parameter_list|,
name|GParam
modifier|*
modifier|*
name|rv
parameter_list|)
block|{
name|char
modifier|*
modifier|*
name|pars
decl_stmt|,
modifier|*
modifier|*
name|rvs
decl_stmt|,
modifier|*
name|t
decl_stmt|,
name|cmd
index|[
literal|80
index|]
decl_stmt|;
name|int
name|rstat
decl_stmt|;
if|if
condition|(
name|theInterp
operator|==
name|NULL
condition|)
block|{
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"gtcl_run, theInterp not initialized\n"
argument_list|)
expr_stmt|;
name|rstat
operator|=
name|STATUS_EXECUTION_ERROR
expr_stmt|;
goto|goto
name|error_done
goto|;
block|}
comment|/* ok, add in our constants and the full PDB */
name|Gtcl_PDBInit
argument_list|(
name|theInterp
argument_list|)
expr_stmt|;
name|Gtcl_ConstInit
argument_list|(
name|theInterp
argument_list|)
expr_stmt|;
name|Tcl_Eval
argument_list|(
name|theInterp
argument_list|,
literal|"info procs gimptcl_run"
argument_list|)
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|theInterp
operator|->
name|result
argument_list|,
literal|"gimptcl_run"
argument_list|)
operator|!=
literal|0
condition|)
block|{
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"gimptcl_run: nothing to do"
argument_list|)
expr_stmt|;
name|rstat
operator|=
name|STATUS_EXECUTION_ERROR
expr_stmt|;
goto|goto
name|error_done
goto|;
block|}
name|pars
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
name|nparm
argument_list|)
expr_stmt|;
comment|/*  fprintf(stderr, "gimptcl_run, need %d args\n", nparm);*/
if|if
condition|(
name|GParam_to_Argv
argument_list|(
name|theInterp
argument_list|,
literal|"gimptcl_run"
argument_list|,
name|nparm
argument_list|,
name|p
argument_list|,
name|pars
argument_list|)
operator|==
name|TCL_ERROR
condition|)
block|{
name|rstat
operator|=
name|STATUS_CALLING_ERROR
expr_stmt|;
goto|goto
name|error_done
goto|;
block|}
name|t
operator|=
name|Tcl_Merge
argument_list|(
name|nparm
argument_list|,
name|pars
argument_list|)
expr_stmt|;
name|free
argument_list|(
name|pars
argument_list|)
expr_stmt|;
name|sprintf
argument_list|(
name|cmd
argument_list|,
literal|"gimptcl_run %s"
argument_list|,
name|t
argument_list|)
expr_stmt|;
name|Tcl_Free
argument_list|(
name|t
argument_list|)
expr_stmt|;
if|if
condition|(
name|Tcl_Eval
argument_list|(
name|theInterp
argument_list|,
name|cmd
argument_list|)
operator|==
name|TCL_ERROR
condition|)
block|{
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"Error in gtcl_run:%s\n"
argument_list|,
name|theInterp
operator|->
name|result
argument_list|)
expr_stmt|;
name|rstat
operator|=
name|STATUS_CALLING_ERROR
expr_stmt|;
goto|goto
name|error_done
goto|;
block|}
if|if
condition|(
name|p
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_int32
operator|==
name|RUN_INTERACTIVE
condition|)
block|{
name|Tk_MainLoop
argument_list|()
expr_stmt|;
name|rstat
operator|=
name|STATUS_SUCCESS
expr_stmt|;
goto|goto
name|error_done
goto|;
comment|/* XXX a bit kludgey */
block|}
comment|/*  fprintf(stderr, "gimptcl_run returned `%s'\n", theInterp->result);*/
name|Tcl_SplitList
argument_list|(
name|theInterp
argument_list|,
name|theInterp
operator|->
name|result
argument_list|,
name|nrv
argument_list|,
operator|&
name|rvs
argument_list|)
expr_stmt|;
comment|/*  fprintf(stderr, "split into %d rets\n", *nrv);*/
operator|*
name|rv
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
operator|(
operator|(
operator|*
name|nrv
operator|)
operator|+
literal|1
operator|)
argument_list|)
expr_stmt|;
name|rv
index|[
literal|0
index|]
operator|->
name|type
operator|=
name|PARAM_STATUS
expr_stmt|;
block|{
name|char
modifier|*
name|b
decl_stmt|,
modifier|*
name|h
decl_stmt|,
modifier|*
name|a
decl_stmt|,
modifier|*
name|c
decl_stmt|,
modifier|*
name|d
decl_stmt|;
name|int
name|type
decl_stmt|,
name|nparams
decl_stmt|,
name|nrvs
decl_stmt|,
name|i
decl_stmt|;
name|GParamDef
modifier|*
name|p_params
decl_stmt|,
modifier|*
name|p_rvals
decl_stmt|;
if|if
condition|(
name|gimp_query_procedure
argument_list|(
name|name
argument_list|,
operator|&
name|b
argument_list|,
operator|&
name|h
argument_list|,
operator|&
name|a
argument_list|,
operator|&
name|c
argument_list|,
operator|&
name|d
argument_list|,
operator|&
name|type
argument_list|,
operator|&
name|nparams
argument_list|,
operator|&
name|nrvs
argument_list|,
operator|&
name|p_params
argument_list|,
operator|&
name|p_rvals
argument_list|)
operator|!=
name|TRUE
condition|)
block|{
name|rstat
operator|=
name|STATUS_EXECUTION_ERROR
expr_stmt|;
goto|goto
name|error_done
goto|;
block|}
comment|/*    fprintf(stderr, "%s returns %d rets\n", name, nrvs);*/
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
operator|*
name|nrv
condition|;
name|i
operator|++
control|)
block|{
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"setting rv[%d] to %d"
argument_list|,
name|i
operator|+
literal|1
argument_list|,
name|p_rvals
index|[
name|i
index|]
operator|.
name|type
argument_list|)
expr_stmt|;
operator|(
operator|*
name|rv
operator|)
index|[
name|i
operator|+
literal|1
index|]
operator|.
name|type
operator|=
name|p_rvals
index|[
name|i
index|]
operator|.
name|type
expr_stmt|;
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"\n"
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|b
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|h
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|a
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|d
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|Argv_to_GParam
argument_list|(
name|theInterp
argument_list|,
literal|"gtcl_run"
argument_list|,
operator|*
name|nrv
argument_list|,
name|rvs
argument_list|,
operator|&
operator|(
operator|(
operator|*
name|rv
operator|)
index|[
literal|1
index|]
operator|)
argument_list|)
operator|==
name|TCL_ERROR
condition|)
block|{
name|rv
index|[
literal|0
index|]
operator|->
name|data
operator|.
name|d_status
operator|=
name|STATUS_EXECUTION_ERROR
expr_stmt|;
block|}
else|else
block|{
name|rv
index|[
literal|0
index|]
operator|->
name|data
operator|.
name|d_status
operator|=
name|STATUS_SUCCESS
expr_stmt|;
block|}
return|return;
name|error_done
label|:
operator|*
name|nrv
operator|=
literal|0
expr_stmt|;
operator|*
name|rv
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
argument_list|)
expr_stmt|;
name|rv
index|[
literal|0
index|]
operator|->
name|type
operator|=
name|PARAM_STATUS
expr_stmt|;
name|rv
index|[
literal|0
index|]
operator|->
name|data
operator|.
name|d_status
operator|=
name|rstat
expr_stmt|;
block|}
end_function

end_unit

