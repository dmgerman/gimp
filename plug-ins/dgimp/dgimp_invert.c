begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|"libgimp/gimp.h"
end_include

begin_include
include|#
directive|include
file|"dgimp_procs.h"
end_include

begin_function
name|void
DECL|function|dgimp_invert_proc (char * name,int nparams,GParam * params,int * nreturn_vals,GParam ** return_vals)
name|dgimp_invert_proc
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
name|params
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
name|GParam
modifier|*
name|lgp_params
decl_stmt|;
name|gint
name|drawable_id
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
comment|/*  Get drawable and LGP parameters  */
name|drawable_id
operator|=
name|params
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_drawable
expr_stmt|;
comment|/*lgp_params = dgimp_convert_params (nparams, params);*/
comment|/*  Get work area  */
name|gimp_drawable_mask_bounds
argument_list|(
name|drawable_id
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|)
expr_stmt|;
comment|/*  Distribute work  */
comment|/*  dgimp_auto_dist ("lgp_invert", nparams + 4, lgp_params, x1, y1, x2, y2);*/
comment|/*  Merge shadow and update  */
name|gimp_drawable_merge_shadow
argument_list|(
name|drawable_id
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|drawable_id
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|,
operator|(
name|y2
operator|-
name|y1
operator|)
argument_list|)
expr_stmt|;
comment|/*gimp_destory_params (lgp_params, nparams + 4);*/
operator|*
name|nreturn_vals
operator|=
literal|1
expr_stmt|;
operator|*
name|return_vals
operator|=
name|success_value
expr_stmt|;
block|}
end_function

end_unit

