begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__LUT_FUNCS_H__
end_ifndef

begin_define
DECL|macro|__LUT_FUNCS_H__
define|#
directive|define
name|__LUT_FUNCS_H__
end_define

begin_include
include|#
directive|include
file|"gimplutF.h"
end_include

begin_include
include|#
directive|include
file|"gimphistogram.h"
end_include

begin_comment
comment|/* brightness contrast */
end_comment

begin_function_decl
name|void
name|brightness_contrast_lut_setup
parameter_list|(
name|GimpLut
modifier|*
name|lut
parameter_list|,
name|double
name|brightness
parameter_list|,
name|double
name|contrast
parameter_list|,
name|int
name|nchannels
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLut
modifier|*
name|brightness_contrast_lut_new
parameter_list|(
name|double
name|brightness
parameter_list|,
name|double
name|contrast
parameter_list|,
name|int
name|nchannels
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* invert */
end_comment

begin_function_decl
name|void
name|invert_lut_setup
parameter_list|(
name|GimpLut
modifier|*
name|lut
parameter_list|,
name|int
name|nchannels
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLut
modifier|*
name|invert_lut_new
parameter_list|(
name|int
name|nchannels
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* add (or subtract) */
end_comment

begin_function_decl
name|void
name|add_lut_setup
parameter_list|(
name|GimpLut
modifier|*
name|lut
parameter_list|,
name|double
name|ammount
parameter_list|,
name|int
name|nchannels
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLut
modifier|*
name|add_lut_new
parameter_list|(
name|double
name|ammount
parameter_list|,
name|int
name|nchannels
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* intersect (MINIMUM(pixel, value)) */
end_comment

begin_function_decl
name|void
name|intersect_lut_setup
parameter_list|(
name|GimpLut
modifier|*
name|lut
parameter_list|,
name|double
name|value
parameter_list|,
name|int
name|nchannels
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLut
modifier|*
name|intersect_lut_new
parameter_list|(
name|double
name|value
parameter_list|,
name|int
name|nchannels
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* threshold */
end_comment

begin_function_decl
name|void
name|threshold_lut_setup
parameter_list|(
name|GimpLut
modifier|*
name|lut
parameter_list|,
name|double
name|value
parameter_list|,
name|int
name|nchannels
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLut
modifier|*
name|threshold_lut_new
parameter_list|(
name|double
name|value
parameter_list|,
name|int
name|nchannels
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* levels */
end_comment

begin_function_decl
name|void
name|levels_lut_setup
parameter_list|(
name|GimpLut
modifier|*
name|lut
parameter_list|,
name|double
modifier|*
name|gamma
parameter_list|,
name|int
modifier|*
name|low_input
parameter_list|,
name|int
modifier|*
name|high_input
parameter_list|,
name|int
modifier|*
name|low_output
parameter_list|,
name|int
modifier|*
name|high_output
parameter_list|,
name|int
name|nchannels
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLut
modifier|*
name|levels_lut_new
parameter_list|(
name|double
modifier|*
name|gamma
parameter_list|,
name|int
modifier|*
name|low_input
parameter_list|,
name|int
modifier|*
name|high_input
parameter_list|,
name|int
modifier|*
name|low_output
parameter_list|,
name|int
modifier|*
name|high_output
parameter_list|,
name|int
name|nchannels
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* posterize */
end_comment

begin_function_decl
name|void
name|posterize_lut_setup
parameter_list|(
name|GimpLut
modifier|*
name|lut
parameter_list|,
name|int
name|levels
parameter_list|,
name|int
name|nchannels
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLut
modifier|*
name|posterize_lut_new
parameter_list|(
name|int
name|levels
parameter_list|,
name|int
name|nchannels
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* equalize histogram */
end_comment

begin_function_decl
name|void
name|eq_histogram_lut_setup
parameter_list|(
name|GimpLut
modifier|*
name|lut
parameter_list|,
name|GimpHistogram
modifier|*
name|hist
parameter_list|,
name|int
name|bytes
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLut
modifier|*
name|eq_histogram_lut_new
parameter_list|(
name|GimpHistogram
modifier|*
name|h
parameter_list|,
name|int
name|nchannels
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __LUT_FUNCS_H__ */
end_comment

end_unit

