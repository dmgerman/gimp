begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/***************************************************  * file: gtclConst.c  *  * Copyright (c) 1996 Eric L. Hernes (erich@rrnet.com)  * All rights reserved.  *  * Redistribution and use in source and binary forms, with or without  * modification, are permitted provided that the following conditions  * are met:  * 1. Redistributions of source code must retain the above copyright  *    notice, this list of conditions and the following disclaimer.  * 2. The name of the author may not be used to endorse or promote products  *    derived from this software withough specific prior written permission  *  * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR  * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES  * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT  * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,  * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY  * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF  * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  *  * $Id$  */
end_comment

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<tcl.h>
end_include

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
file|"gtcl.h"
end_include

begin_include
include|#
directive|include
file|"gtclEnums.h"
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_decl_stmt
DECL|variable|GtclConst
name|char
modifier|*
name|GtclConst
init|=
literal|"GtclConst"
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|Gtcl_CAdd (c)
define|#
directive|define
name|Gtcl_CAdd
parameter_list|(
name|c
parameter_list|)
value|sprintf(t, "%d", c);                                  \                       sprintf(t1, "%s", # c);                               \                       Tcl_SetVar2(interp, GtclConst, t1, t,                 \                                   TCL_GLOBAL_ONLY);                         \                       cvtfrom(t1);                                          \                       Tcl_SetVar2(interp, GtclConst, t1, t,                 \                                   TCL_GLOBAL_ONLY);
end_define

begin_define
DECL|macro|Gtcl_CAddf (c)
define|#
directive|define
name|Gtcl_CAddf
parameter_list|(
name|c
parameter_list|)
value|sprintf(t, "%g", c);                                 \                        sprintf(t1, "%s", # c);                              \                        Tcl_SetVar2(interp, GtclConst, t1, t,                \                                    TCL_GLOBAL_ONLY);                        \                        cvtfrom(t1);                                         \                        Tcl_SetVar2(interp, GtclConst, t1, t,                \                                    TCL_GLOBAL_ONLY);
end_define

begin_function
name|int
DECL|function|Gtcl_ConstInit (Tcl_Interp * interp)
name|Gtcl_ConstInit
parameter_list|(
name|Tcl_Interp
modifier|*
name|interp
parameter_list|)
block|{
name|char
name|t
index|[
literal|30
index|]
decl_stmt|,
name|t1
index|[
literal|30
index|]
decl_stmt|;
name|Tcl_PkgProvide
argument_list|(
name|interp
argument_list|,
literal|"GtclConstant"
argument_list|,
literal|"1.0"
argument_list|)
expr_stmt|;
comment|/* the auto-generated ones from<gimpenums.h> */
include|#
directive|include
file|"gtclenums.h"
comment|/* and a few manifest constants from<glib.h> */
name|Gtcl_CAddf
argument_list|(
name|G_MINFLOAT
argument_list|)
expr_stmt|;
name|Gtcl_CAddf
argument_list|(
name|G_MAXFLOAT
argument_list|)
expr_stmt|;
name|Gtcl_CAddf
argument_list|(
name|G_MINDOUBLE
argument_list|)
expr_stmt|;
name|Gtcl_CAddf
argument_list|(
name|G_MAXDOUBLE
argument_list|)
expr_stmt|;
name|Gtcl_CAdd
argument_list|(
name|G_MINSHORT
argument_list|)
expr_stmt|;
name|Gtcl_CAdd
argument_list|(
name|G_MAXSHORT
argument_list|)
expr_stmt|;
name|Gtcl_CAdd
argument_list|(
name|G_MININT
argument_list|)
expr_stmt|;
name|Gtcl_CAdd
argument_list|(
name|G_MAXINT
argument_list|)
expr_stmt|;
name|Gtcl_CAdd
argument_list|(
name|G_MINLONG
argument_list|)
expr_stmt|;
name|Gtcl_CAdd
argument_list|(
name|G_MAXLONG
argument_list|)
expr_stmt|;
comment|/* and a few others */
name|Gtcl_CAdd
argument_list|(
name|TRUE
argument_list|)
expr_stmt|;
name|Gtcl_CAdd
argument_list|(
name|FALSE
argument_list|)
expr_stmt|;
comment|/* for gimp-text */
DECL|macro|NEW_LAYER
define|#
directive|define
name|NEW_LAYER
value|-1
DECL|macro|PIXELS
define|#
directive|define
name|PIXELS
value|0
DECL|macro|POINTS
define|#
directive|define
name|POINTS
value|1
name|Gtcl_CAdd
argument_list|(
name|NEW_LAYER
argument_list|)
expr_stmt|;
name|Gtcl_CAdd
argument_list|(
name|PIXELS
argument_list|)
expr_stmt|;
name|Gtcl_CAdd
argument_list|(
name|POINTS
argument_list|)
expr_stmt|;
return|return
name|TCL_OK
return|;
block|}
end_function

end_unit

