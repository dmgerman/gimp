begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__SCALE_FUNCS_H__
end_ifndef

begin_define
DECL|macro|__SCALE_FUNCS_H__
define|#
directive|define
name|__SCALE_FUNCS_H__
end_define

begin_define
DECL|macro|LANCZOS_SPP
define|#
directive|define
name|LANCZOS_SPP
value|(4000)
end_define

begin_comment
DECL|macro|LANCZOS_SPP
comment|/* number of data pts per unit x in lookup table */
end_comment

begin_define
DECL|macro|LANCZOS_MIN
define|#
directive|define
name|LANCZOS_MIN
value|(1.0/LANCZOS_SPP)
end_define

begin_define
DECL|macro|LANCZOS_WIDTH
define|#
directive|define
name|LANCZOS_WIDTH
value|(3)
end_define

begin_comment
DECL|macro|LANCZOS_WIDTH
comment|/* 3 for Lanczos3 code, for L4 prefer DUAL_LANCZOS below */
end_comment

begin_define
DECL|macro|LANCZOS_WIDTH2
define|#
directive|define
name|LANCZOS_WIDTH2
value|(1 + (LANCZOS_WIDTH * 2))
end_define

begin_define
DECL|macro|LANCZOS_SAMPLES
define|#
directive|define
name|LANCZOS_SAMPLES
value|(LANCZOS_SPP * (LANCZOS_WIDTH + 1))
end_define

begin_function_decl
name|void
name|scale_region
parameter_list|(
name|PixelRegion
modifier|*
name|srcPR
parameter_list|,
name|PixelRegion
modifier|*
name|destPR
parameter_list|,
name|GimpInterpolationType
name|interpolation
parameter_list|,
name|GimpProgressFunc
name|progress_callback
parameter_list|,
name|gpointer
name|progress_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|subsample_region
parameter_list|(
name|PixelRegion
modifier|*
name|srcPR
parameter_list|,
name|PixelRegion
modifier|*
name|destPR
parameter_list|,
name|gint
name|subsample
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gfloat
modifier|*
name|create_lanczos_lookup
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __SCALE_FUNCS_H__  */
end_comment

begin_comment
comment|/* determining LANCZOS_SPP value   1000 points per unit will produce typically 1 bit of error per channel on a Lanczos3 window   4000 should not produce a detectable error caused by lookup table size.on 8b colours ie 24bit RGB   this req 80kB of memory comparable to a small 250x150 px image. Filling the array is a small part of   the time required for the transform.   This will need reviewing when GIMP handles images with more bytes per pixel. */
end_comment

end_unit

