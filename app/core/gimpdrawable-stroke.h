begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdrawable-stroke.h  * Copyright (C) 2003 Simon Budig<simon@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DRAWABLE_STROKE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DRAWABLE_STROKE_H__
define|#
directive|define
name|__GIMP_DRAWABLE_STROKE_H__
end_define

begin_function_decl
name|void
name|gimp_drawable_stroke_boundary
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpStrokeOptions
modifier|*
name|options
parameter_list|,
specifier|const
name|GimpBoundSeg
modifier|*
name|bound_segs
parameter_list|,
name|gint
name|n_bound_segs
parameter_list|,
name|gint
name|offset_x
parameter_list|,
name|gint
name|offset_y
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_stroke_vectors
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpStrokeOptions
modifier|*
name|options
parameter_list|,
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
name|gboolean
name|push_undo
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_stroke_scan_convert
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpStrokeOptions
modifier|*
name|options
parameter_list|,
name|GimpScanConvert
modifier|*
name|scan_convert
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_DRAWABLE_STROKE_H__  */
end_comment

end_unit

