begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Gradient editor module copyight (C) 1996-1997 Federico Mena Quintero  * federico@nuclecu.unam.mx  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GRADIENT_EDITOR_H__
end_ifndef

begin_define
DECL|macro|__GRADIENT_EDITOR_H__
define|#
directive|define
name|__GRADIENT_EDITOR_H__
end_define

begin_typedef
DECL|typedef|GradientEditor
typedef|typedef
name|struct
name|_GradientEditor
name|GradientEditor
typedef|;
end_typedef

begin_function_decl
name|GradientEditor
modifier|*
name|gradient_editor_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gradient_editor_set_gradient
parameter_list|(
name|GradientEditor
modifier|*
name|gradient_editor
parameter_list|,
name|GimpGradient
modifier|*
name|gradient
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gradient_editor_free
parameter_list|(
name|GradientEditor
modifier|*
name|gradient_editor
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GRADIENT_EDITOR_H__ */
end_comment

end_unit

