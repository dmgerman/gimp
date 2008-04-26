begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*     flame - cosmic recursive fractal flames     Copyright (C) 1992  Scott Draves<spot@cs.cmu.edu>      This program is free software; you can redistribute it and/or modify     it under the terms of the GNU General Public License as published by     the Free Software Foundation; either version 2 of the License, or     (at your option) any later version.      This program is distributed in the hope that it will be useful,     but WITHOUT ANY WARRANTY; without even the implied warranty of     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the     GNU General Public License for more details.      You should have received a copy of the GNU General Public License     along with this program; if not, write to the Free Software     Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA. */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|libifs_included
end_ifndef

begin_define
DECL|macro|libifs_included
define|#
directive|define
name|libifs_included
end_define

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<math.h>
end_include

begin_include
include|#
directive|include
file|"cmap.h"
end_include

begin_define
DECL|macro|EPS
define|#
directive|define
name|EPS
value|(1e-10)
end_define

begin_define
DECL|macro|variation_random
define|#
directive|define
name|variation_random
value|(-1)
end_define

begin_define
DECL|macro|NVARS
define|#
directive|define
name|NVARS
value|29
end_define

begin_define
DECL|macro|NXFORMS
define|#
directive|define
name|NXFORMS
value|6
end_define

begin_typedef
DECL|typedef|point
typedef|typedef
name|double
name|point
index|[
literal|3
index|]
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2b73eff60108
typedef|typedef
struct|struct
block|{
DECL|member|var
name|double
name|var
index|[
name|NVARS
index|]
decl_stmt|;
comment|/* normalized interp coefs between variations */
DECL|member|c
name|double
name|c
index|[
literal|3
index|]
index|[
literal|2
index|]
decl_stmt|;
comment|/* the coefs to the affine part of the function */
DECL|member|density
name|double
name|density
decl_stmt|;
comment|/* prob is this function is chosen. 0 - 1 */
DECL|member|color
name|double
name|color
decl_stmt|;
comment|/* color coord for this function. 0 - 1 */
DECL|typedef|xform
block|}
name|xform
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2b73eff60208
typedef|typedef
struct|struct
block|{
DECL|member|xform
name|xform
name|xform
index|[
name|NXFORMS
index|]
decl_stmt|;
DECL|member|cmap
name|clrmap
name|cmap
decl_stmt|;
DECL|member|time
name|double
name|time
decl_stmt|;
DECL|member|cmap_index
name|int
name|cmap_index
decl_stmt|;
DECL|member|brightness
name|double
name|brightness
decl_stmt|;
comment|/* 1.0 = normal */
DECL|member|contrast
name|double
name|contrast
decl_stmt|;
comment|/* 1.0 = normal */
DECL|member|gamma
name|double
name|gamma
decl_stmt|;
DECL|member|width
DECL|member|height
name|int
name|width
decl_stmt|,
name|height
decl_stmt|;
comment|/* of the final image */
DECL|member|spatial_oversample
name|int
name|spatial_oversample
decl_stmt|;
DECL|member|center
name|double
name|center
index|[
literal|2
index|]
decl_stmt|;
comment|/* camera center */
DECL|member|zoom
name|double
name|zoom
decl_stmt|;
comment|/* effects ppu and sample density */
DECL|member|pixels_per_unit
name|double
name|pixels_per_unit
decl_stmt|;
comment|/* and scale */
DECL|member|spatial_filter_radius
name|double
name|spatial_filter_radius
decl_stmt|;
comment|/* variance of gaussian */
DECL|member|sample_density
name|double
name|sample_density
decl_stmt|;
comment|/* samples per pixel (not bucket) */
comment|/* in order to motion blur more accurately we compute the logs of the       sample density many times and average the results.  we interplate       only this many times. */
DECL|member|nbatches
name|int
name|nbatches
decl_stmt|;
comment|/* this much color resolution.  but making it too high induces clipping */
DECL|member|white_level
name|int
name|white_level
decl_stmt|;
DECL|member|cmap_inter
name|int
name|cmap_inter
decl_stmt|;
comment|/* if this is true, then color map interpolates one entry 		      at a time with a bright edge */
DECL|member|pulse
name|double
name|pulse
index|[
literal|2
index|]
index|[
literal|2
index|]
decl_stmt|;
comment|/* [i][0]=magnitute [i][1]=frequency */
DECL|member|wiggle
name|double
name|wiggle
index|[
literal|2
index|]
index|[
literal|2
index|]
decl_stmt|;
comment|/* frequency is /minute, assuming 30 frames/s */
DECL|typedef|control_point
block|}
name|control_point
typedef|;
end_typedef

begin_function_decl
specifier|extern
name|void
name|iterate
parameter_list|(
name|control_point
modifier|*
name|cp
parameter_list|,
name|int
name|n
parameter_list|,
name|int
name|fuse
parameter_list|,
name|point
name|points
index|[]
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|interpolate
parameter_list|(
name|control_point
name|cps
index|[]
parameter_list|,
name|int
name|ncps
parameter_list|,
name|double
name|time
parameter_list|,
name|control_point
modifier|*
name|result
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|tokenize
parameter_list|(
name|char
modifier|*
modifier|*
name|ss
parameter_list|,
name|char
modifier|*
name|argv
index|[]
parameter_list|,
name|int
modifier|*
name|argc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|print_control_point
parameter_list|(
name|FILE
modifier|*
name|f
parameter_list|,
name|control_point
modifier|*
name|cp
parameter_list|,
name|int
name|quote
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|random_control_point
parameter_list|(
name|control_point
modifier|*
name|cp
parameter_list|,
name|int
name|ivar
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|parse_control_point
parameter_list|(
name|char
modifier|*
modifier|*
name|ss
parameter_list|,
name|control_point
modifier|*
name|cp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|estimate_bounding_box
parameter_list|(
name|control_point
modifier|*
name|cp
parameter_list|,
name|double
name|eps
parameter_list|,
name|double
modifier|*
name|bmin
parameter_list|,
name|double
modifier|*
name|bmax
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|sort_control_points
parameter_list|(
name|control_point
modifier|*
name|cps
parameter_list|,
name|int
name|ncps
parameter_list|,
name|double
function_decl|(
modifier|*
name|metric
function_decl|)
parameter_list|()
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|double
name|standard_metric
parameter_list|(
name|control_point
modifier|*
name|cp1
parameter_list|,
name|control_point
modifier|*
name|cp2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|double
name|random_uniform01
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|double
name|random_uniform11
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|double
name|random_gaussian
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|mult_matrix
parameter_list|(
name|double
name|s1
index|[
literal|2
index|]
index|[
literal|2
index|]
parameter_list|,
name|double
name|s2
index|[
literal|2
index|]
index|[
literal|2
index|]
parameter_list|,
name|double
name|d
index|[
literal|2
index|]
index|[
literal|2
index|]
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|copy_variation
parameter_list|(
name|control_point
modifier|*
name|cp0
parameter_list|,
name|control_point
modifier|*
name|cp1
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit

