begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* fit.h: convert the pixel representation to splines.  Copyright (C) 1992 Free Software Foundation, Inc.  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|FIT_H
end_ifndef

begin_define
DECL|macro|FIT_H
define|#
directive|define
name|FIT_H
end_define

begin_include
include|#
directive|include
file|"pxl-outline.h"
end_include

begin_include
include|#
directive|include
file|"spline.h"
end_include

begin_comment
comment|/* See fit.c for descriptions of these variables, all of which can be    set using options.  */
end_comment

begin_decl_stmt
specifier|extern
name|real
name|align_threshold
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|real
name|corner_always_threshold
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|unsigned
name|corner_surround
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|real
name|corner_threshold
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|real
name|error_threshold
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|unsigned
name|filter_alternative_surround
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|real
name|filter_epsilon
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|unsigned
name|filter_iteration_count
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|real
name|filter_percent
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|unsigned
name|filter_surround
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|boolean
name|keep_knees
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|real
name|line_reversion_threshold
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|real
name|line_threshold
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|real
name|reparameterize_improvement
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|real
name|reparameterize_threshold
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|real
name|subdivide_search
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|unsigned
name|subdivide_surround
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|real
name|subdivide_threshold
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|unsigned
name|tangent_surround
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* Fit splines and lines to LIST.  */
end_comment

begin_function_decl
specifier|extern
name|spline_list_array_type
name|fitted_splines
parameter_list|(
name|pixel_outline_list_type
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|fit_set_params
parameter_list|(
name|SELVALS
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|fit_set_default_params
parameter_list|(
name|SELVALS
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* not FIT_H */
end_comment

end_unit

