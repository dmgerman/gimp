begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Gradient editor module copyight (C) 1996-1997 Federico Mena Quintero  * federico@nuclecu.unam.mx  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GRADIENT_H__
end_ifndef

begin_define
DECL|macro|__GRADIENT_H__
define|#
directive|define
name|__GRADIENT_H__
end_define

begin_typedef
DECL|typedef|gradient_t
typedef|typedef
name|struct
name|_gradient_t
name|gradient_t
typedef|;
end_typedef

begin_comment
comment|/*  global variables  */
end_comment

begin_decl_stmt
specifier|extern
name|GSList
modifier|*
name|gradients_list
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gint
name|num_gradients
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gradients_init
parameter_list|(
name|gint
name|no_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gradients_free
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gradient_t
modifier|*
name|gradients_get_standard_gradient
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gradient_t
modifier|*
name|gradient_list_get_gradient
parameter_list|(
name|GSList
modifier|*
name|list
parameter_list|,
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gradient_list_get_gradient_index
parameter_list|(
name|GSList
modifier|*
name|list
parameter_list|,
name|gradient_t
modifier|*
name|gradient
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gradient_get_color_at
parameter_list|(
name|gradient_t
modifier|*
name|gradient
parameter_list|,
name|gdouble
name|pos
parameter_list|,
name|gdouble
modifier|*
name|r
parameter_list|,
name|gdouble
modifier|*
name|g
parameter_list|,
name|gdouble
modifier|*
name|b
parameter_list|,
name|gdouble
modifier|*
name|a
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GRADIENT_H__ */
end_comment

end_unit

