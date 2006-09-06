begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
DECL|macro|EPSILON
define|#
directive|define
name|EPSILON
value|(0.0001)
end_define

begin_define
DECL|macro|LANCZOS_SPP
define|#
directive|define
name|LANCZOS_SPP
value|(1000)
end_define

begin_define
DECL|macro|LANCZOS_WIDTH
define|#
directive|define
name|LANCZOS_WIDTH
value|(4)
end_define

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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __SCALE_FUNCS_H__  */
end_comment

end_unit

