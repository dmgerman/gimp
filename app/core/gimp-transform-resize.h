begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-2001 Spencer Kimball, Peter Mattis, and others  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TRANSFORM_RESIZE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TRANSFORM_RESIZE_H__
define|#
directive|define
name|__GIMP_TRANSFORM_RESIZE_H__
end_define

begin_function_decl
name|void
name|gimp_transform_resize_boundary
parameter_list|(
specifier|const
name|GimpMatrix3
modifier|*
name|inv
parameter_list|,
name|GimpTransformResize
name|resize
parameter_list|,
name|gint
name|u1
parameter_list|,
name|gint
name|v1
parameter_list|,
name|gint
name|u2
parameter_list|,
name|gint
name|v2
parameter_list|,
name|gint
modifier|*
name|x1
parameter_list|,
name|gint
modifier|*
name|y1
parameter_list|,
name|gint
modifier|*
name|x2
parameter_list|,
name|gint
modifier|*
name|y2
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_TRANSFORM_RESIZE_H__  */
end_comment

end_unit

