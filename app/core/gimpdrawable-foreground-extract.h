begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DRAWABLE_FOREGROUND_EXTRACT_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DRAWABLE_FOREGROUND_EXTRACT_H__
define|#
directive|define
name|__GIMP_DRAWABLE_FOREGROUND_EXTRACT_H__
end_define

begin_function_decl
name|void
name|gimp_drawable_foreground_extract
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpForegroundExtractMode
name|mode
parameter_list|,
name|GimpDrawable
modifier|*
name|mask
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  variant for SIOX that gives more control over the segmentation  */
end_comment

begin_function_decl
name|void
name|gimp_drawable_foreground_extract_siox
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpDrawable
modifier|*
name|mask
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|smoothness
parameter_list|,
specifier|const
name|gdouble
name|sensitivity
index|[
literal|3
index|]
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_DRAWABLE_FOREGROUND_EXTRACT_H__  */
end_comment

end_unit

