begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimplut.h: Copyright (C) 1999 Jay Cox<jaycox@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_LUT_H__
end_ifndef

begin_define
DECL|macro|__GIMP_LUT_H__
define|#
directive|define
name|__GIMP_LUT_H__
end_define

begin_struct
DECL|struct|_GimpLut
struct|struct
name|_GimpLut
block|{
DECL|member|luts
name|guchar
modifier|*
modifier|*
name|luts
decl_stmt|;
DECL|member|nchannels
name|gint
name|nchannels
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/* TODO: the GimpLutFunc should really be passed the ColorModel of the  * region, not just the number of channels  */
end_comment

begin_comment
comment|/* GimpLutFuncs should assume that the input and output gamma are 1.0  * and do no correction as this will be handled by gimp_lut_setup  */
end_comment

begin_typedef
DECL|typedef|GimpLutFunc
typedef|typedef
name|gfloat
function_decl|(
modifier|*
name|GimpLutFunc
function_decl|)
parameter_list|(
name|gpointer
name|user_data
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
end_typedef

begin_function_decl
name|GimpLut
modifier|*
name|gimp_lut_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_lut_free
parameter_list|(
name|GimpLut
modifier|*
name|lut
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_lut_setup
parameter_list|(
name|GimpLut
modifier|*
name|lut
parameter_list|,
name|GimpLutFunc
name|func
parameter_list|,
name|gpointer
name|user_data
parameter_list|,
name|gint
name|nchannels
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* gimp_lut_setup_exact is currently identical to gimp_lut_setup.  It  * however is guaranteed to never perform any interpolation or gamma  * correction on the lut  */
end_comment

begin_function_decl
name|void
name|gimp_lut_setup_exact
parameter_list|(
name|GimpLut
modifier|*
name|lut
parameter_list|,
name|GimpLutFunc
name|func
parameter_list|,
name|gpointer
name|user_data
parameter_list|,
name|gint
name|nchannels
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_lut_process
parameter_list|(
name|GimpLut
modifier|*
name|lut
parameter_list|,
name|PixelRegion
modifier|*
name|srcPR
parameter_list|,
name|PixelRegion
modifier|*
name|destPR
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* gimp_lut_process_inline is like gimp_lut_process except it uses a  * single PixelRegion as both the source and destination  */
end_comment

begin_function_decl
name|void
name|gimp_lut_process_inline
parameter_list|(
name|GimpLut
modifier|*
name|lut
parameter_list|,
name|PixelRegion
modifier|*
name|src_destPR
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_LUT_H__ */
end_comment

end_unit

