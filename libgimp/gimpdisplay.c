begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library                                                     * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball                  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Library General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.               *                                                                                * This library is distributed in the hope that it will be useful,                * but WITHOUT ANY WARRANTY; without even the implied warranty of                 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU              * Library General Public License for more details.  *  * You should have received a copy of the GNU Library General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_function
name|gint32
DECL|function|gimp_display_new (gint32 image_ID)
name|gimp_display_new
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|gint32
name|display_ID
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_display_new"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_IMAGE
argument_list|,
name|image_ID
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|display_ID
operator|=
operator|-
literal|1
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|STATUS_SUCCESS
condition|)
name|display_ID
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_display
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|display_ID
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_delete (gint32 display_ID)
name|gimp_display_delete
parameter_list|(
name|gint32
name|display_ID
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_display_delete"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_DISPLAY
argument_list|,
name|display_ID
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_displays_flush ()
name|gimp_displays_flush
parameter_list|()
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_displays_flush"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

