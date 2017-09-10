begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimp-gegl-loops-sse2.h  * Copyright (C) 2012 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_GEGL_LOOPS_SSE2_H__
end_ifndef

begin_define
DECL|macro|__GIMP_GEGL_LOOPS_SSE2_H__
define|#
directive|define
name|__GIMP_GEGL_LOOPS_SSE2_H__
end_define

begin_if
if|#
directive|if
name|COMPILE_SSE2_INTRINISICS
end_if

begin_function_decl
name|void
name|gimp_gegl_smudge_with_paint_process_sse2
parameter_list|(
name|gfloat
modifier|*
name|accum
parameter_list|,
specifier|const
name|gfloat
modifier|*
name|canvas
parameter_list|,
name|gfloat
modifier|*
name|paint
parameter_list|,
name|gint
name|count
parameter_list|,
specifier|const
name|gfloat
modifier|*
name|brush_color
parameter_list|,
name|gfloat
name|brush_a
parameter_list|,
name|gboolean
name|no_erasing
parameter_list|,
name|gfloat
name|flow
parameter_list|,
name|gfloat
name|rate
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* COMPILE_SSE2_INTRINISICS */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_GEGL_LOOPS_SSE2_H__ */
end_comment

end_unit
