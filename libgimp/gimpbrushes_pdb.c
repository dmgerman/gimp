begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2000 Peter Mattis and Spencer Kimball  *  * gimpbrushes_pdb.c  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_function
name|gchar
modifier|*
DECL|function|gimp_brushes_get_brush_data (gchar * brush_name,gdouble * opacity,gint * spacing,GimpLayerModeEffects * paint_mode,gint * width,gint * height,gint * mask_data_size,guint8 ** mask_data)
name|gimp_brushes_get_brush_data
parameter_list|(
name|gchar
modifier|*
name|brush_name
parameter_list|,
name|gdouble
modifier|*
name|opacity
parameter_list|,
name|gint
modifier|*
name|spacing
parameter_list|,
name|GimpLayerModeEffects
modifier|*
name|paint_mode
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|,
name|gint
modifier|*
name|mask_data_size
parameter_list|,
name|guint8
modifier|*
modifier|*
name|mask_data
parameter_list|)
block|{
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_brushes_get_brush_data"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_STRING
argument_list|,
name|brush_name
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|brush_name
operator|=
name|NULL
expr_stmt|;
operator|*
name|width
operator|=
literal|0
expr_stmt|;
operator|*
name|height
operator|=
literal|0
expr_stmt|;
operator|*
name|mask_data_size
operator|=
literal|0
expr_stmt|;
operator|*
name|mask_data
operator|=
name|NULL
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
block|{
name|brush_name
operator|=
name|g_strdup
argument_list|(
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
expr_stmt|;
operator|*
name|opacity
operator|=
name|return_vals
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
operator|*
name|spacing
operator|=
name|return_vals
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|*
name|paint_mode
operator|=
name|return_vals
index|[
literal|4
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|*
name|width
operator|=
name|return_vals
index|[
literal|5
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|*
name|height
operator|=
name|return_vals
index|[
literal|6
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|*
name|mask_data_size
operator|=
name|return_vals
index|[
literal|7
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|*
name|mask_data
operator|=
name|g_new
argument_list|(
name|guint8
argument_list|,
operator|*
name|mask_data_size
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
operator|*
name|mask_data
argument_list|,
name|return_vals
index|[
literal|8
index|]
operator|.
name|data
operator|.
name|d_int8array
argument_list|,
operator|*
name|mask_data_size
operator|*
sizeof|sizeof
argument_list|(
name|guint8
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|brush_name
return|;
block|}
end_function

end_unit

