begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DRAWABLE_BLEND_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DRAWABLE_BLEND_H__
define|#
directive|define
name|__GIMP_DRAWABLE_BLEND_H__
end_define

begin_function_decl
name|void
name|gimp_drawable_blend
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpBlendMode
name|blend_mode
parameter_list|,
name|GimpLayerModeEffects
name|paint_mode
parameter_list|,
name|GimpGradientType
name|gradient_type
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|gdouble
name|offset
parameter_list|,
name|GimpRepeatMode
name|repeat
parameter_list|,
name|gboolean
name|reverse
parameter_list|,
name|gboolean
name|supersample
parameter_list|,
name|gint
name|max_depth
parameter_list|,
name|gdouble
name|threshold
parameter_list|,
name|gboolean
name|dither
parameter_list|,
name|gdouble
name|startx
parameter_list|,
name|gdouble
name|starty
parameter_list|,
name|gdouble
name|endx
parameter_list|,
name|gdouble
name|endy
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
comment|/* __GIMP_DRAWABLE_BLEND_H__ */
end_comment

end_unit

