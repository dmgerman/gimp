begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimplut.h: Copyright (C) 1999 Jay Cox<jaycox@earthlink.net>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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

begin_include
include|#
directive|include
file|"pixel_region.h"
end_include

begin_comment
comment|/* TODO: the GimpLutFunc should really be passed the ColorModel of the region,    not just the number of channels */
end_comment

begin_comment
comment|/* GimpLutFuncs should assume that the input and output gamma are 1.0    and do no correction as this will be handled by gimp_lut_setup */
end_comment

begin_typedef
DECL|typedef|GimpLutFunc
typedef|typedef
name|float
function_decl|(
modifier|*
name|GimpLutFunc
function_decl|)
parameter_list|(
name|void
modifier|*
name|user_data
parameter_list|,
name|int
name|nchannels
parameter_list|,
name|int
name|channel
parameter_list|,
name|float
name|value
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|GimpLut
modifier|*
name|gimp_lut_new
parameter_list|()
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
parameter_list|,
name|GimpLutFunc
parameter_list|,
name|void
modifier|*
name|user_data
parameter_list|,
name|int
name|nchannels
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* gimp_lut_setup_exact is currently identical to gimp_lut_setup.  It    however is guaranteed to never perform any interpolation or gamma    correction on the lut */
end_comment

begin_function_decl
name|void
name|gimp_lut_setup_exact
parameter_list|(
name|GimpLut
modifier|*
parameter_list|,
name|GimpLutFunc
parameter_list|,
name|void
modifier|*
name|user_data
parameter_list|,
name|int
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
comment|/* gimp_lut_process_inline is like gimp_lut_process except it uses a    single PixelRegion as both the source and destination */
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

begin_comment
comment|/* gimp_lut_process_2 is the same as gimp_lut_process but the lut    perameter is last instead of first.  this is necesary because    pixel_region_process_paralell sends the user_data as the 1st    parameter, and the image_map functions send user_data as the last    parameter */
end_comment

begin_function_decl
name|void
name|gimp_lut_process_2
parameter_list|(
name|PixelRegion
modifier|*
name|srcPR
parameter_list|,
name|PixelRegion
modifier|*
name|destPR
parameter_list|,
name|GimpLut
modifier|*
name|lut
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

