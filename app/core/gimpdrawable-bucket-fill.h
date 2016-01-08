begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DRAWABLE_BUCKET_FILL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DRAWABLE_BUCKET_FILL_H__
define|#
directive|define
name|__GIMP_DRAWABLE_BUCKET_FILL_H__
end_define

begin_function_decl
name|gboolean
name|gimp_drawable_bucket_fill
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpFillType
name|fill_type
parameter_list|,
name|gint
name|paint_mode
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|gboolean
name|fill_transparent
parameter_list|,
name|GimpSelectCriterion
name|fill_criterion
parameter_list|,
name|gdouble
name|threshold
parameter_list|,
name|gboolean
name|sample_merged
parameter_list|,
name|gboolean
name|diagonal_neighbors
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_DRAWABLE_BUCKET_FILL_H__  */
end_comment

end_unit

