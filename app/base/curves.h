begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__CURVES_H__
end_ifndef

begin_define
DECL|macro|__CURVES_H__
define|#
directive|define
name|__CURVES_H__
end_define

begin_define
DECL|macro|CURVES_NUM_POINTS
define|#
directive|define
name|CURVES_NUM_POINTS
value|17
end_define

begin_struct
DECL|struct|_Curves
struct|struct
name|_Curves
block|{
DECL|member|curve_type
name|GimpCurveType
name|curve_type
index|[
literal|5
index|]
decl_stmt|;
DECL|member|points
name|gint
name|points
index|[
literal|5
index|]
index|[
name|CURVES_NUM_POINTS
index|]
index|[
literal|2
index|]
decl_stmt|;
DECL|member|curve
name|guchar
name|curve
index|[
literal|5
index|]
index|[
literal|256
index|]
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|curves_init
parameter_list|(
name|Curves
modifier|*
name|curves
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|curves_channel_reset
parameter_list|(
name|Curves
modifier|*
name|curves
parameter_list|,
name|GimpHistogramChannel
name|channel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|curves_calculate_curve
parameter_list|(
name|Curves
modifier|*
name|curves
parameter_list|,
name|GimpHistogramChannel
name|channel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gfloat
name|curves_lut_func
parameter_list|(
name|Curves
modifier|*
name|curves
parameter_list|,
name|gint
name|nchannels
parameter_list|,
name|gint
name|channel
parameter_list|,
name|gfloat
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __CURVES_H__  */
end_comment

end_unit

