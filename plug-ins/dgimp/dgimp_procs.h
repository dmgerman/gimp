begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__DGIMP_PROCS_H__
end_ifndef

begin_comment
comment|/*  Structures  */
end_comment

begin_typedef
DECL|typedef|DGimpProc
typedef|typedef
name|struct
name|_DGimpProc
name|DGimpProc
typedef|;
end_typedef

begin_typedef
DECL|typedef|DGimpLGP
typedef|typedef
name|struct
name|_DGimpLGP
name|DGimpLGP
typedef|;
end_typedef

begin_struct
DECL|struct|_DGimpProc
struct|struct
name|_DGimpProc
block|{
DECL|member|name
name|char
modifier|*
name|name
decl_stmt|;
DECL|member|run_proc
name|GRunProc
name|run_proc
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_DGimpLGP
struct|struct
name|_DGimpLGP
block|{
DECL|member|filedes
name|gint
name|filedes
decl_stmt|;
DECL|member|available
name|gint
name|available
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  Function prototypes  */
end_comment

begin_define
DECL|macro|DGIMP_PROTO (func)
define|#
directive|define
name|DGIMP_PROTO
parameter_list|(
name|func
parameter_list|)
define|\
value|void  func (char    *name, \ 	    int      nparams, \ 	    GParam  *params, \ 	    int     *nreturn_vals, \ 	    GParam **return_vals)
end_define

begin_expr_stmt
name|DGIMP_PROTO
argument_list|(
name|dgimp_invert_proc
argument_list|)
expr_stmt|;
end_expr_stmt

begin_function_decl
name|GParam
modifier|*
name|dgimp_convert_params
parameter_list|(
name|int
name|nparams
parameter_list|,
name|GParam
modifier|*
name|params
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|dgimp_auto_dist
parameter_list|(
name|gchar
modifier|*
name|proc_name
parameter_list|,
name|int
name|nparams
parameter_list|,
name|GParam
modifier|*
name|params
parameter_list|,
name|int
name|x1
parameter_list|,
name|int
name|y1
parameter_list|,
name|int
name|x2
parameter_list|,
name|int
name|y2
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  External variables  */
end_comment

begin_decl_stmt
specifier|extern
name|GList
modifier|*
name|dgimp_lgp_list
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  Static variables  */
end_comment

begin_decl_stmt
DECL|variable|success_value
specifier|static
name|GParam
name|success_value
index|[
literal|1
index|]
init|=
block|{
block|{
name|PARAM_STATUS
block|,
name|STATUS_SUCCESS
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|failure_value
specifier|static
name|GParam
name|failure_value
index|[
literal|1
index|]
init|=
block|{
block|{
name|PARAM_STATUS
block|,
name|STATUS_EXECUTION_ERROR
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __DGIMP_PROCS_H__  */
end_comment

end_unit

