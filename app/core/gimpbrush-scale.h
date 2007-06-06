begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpbrush-scale.h  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_BRUSH_SCALE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_BRUSH_SCALE_H__
define|#
directive|define
name|__GIMP_BRUSH_SCALE_H__
end_define

begin_comment
comment|/*  virtual functions of GimpBrush, don't call directly  */
end_comment

begin_function_decl
name|void
name|gimp_brush_real_scale_size
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|gdouble
name|scale
parameter_list|,
name|gint
modifier|*
name|scaled_width
parameter_list|,
name|gint
modifier|*
name|scaled_height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TempBuf
modifier|*
name|gimp_brush_real_scale_mask
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|gdouble
name|scale
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TempBuf
modifier|*
name|gimp_brush_real_scale_pixmap
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|gdouble
name|scale
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_BRUSH_SCALE_H__  */
end_comment

end_unit

