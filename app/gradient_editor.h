begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Gradient editor module copyight (C) 1996-1997 Federico Mena Quintero  * federico@nuclecu.unam.mx  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_GRADIENT_H_
end_ifndef

begin_define
DECL|macro|_GRADIENT_H_
define|#
directive|define
name|_GRADIENT_H_
end_define

begin_include
include|#
directive|include
file|"procedural_db.h"
end_include

begin_comment
comment|/***** Functions *****/
end_comment

begin_function_decl
name|void
name|gradients_init
parameter_list|(
name|int
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
name|void
name|grad_get_color_at
parameter_list|(
name|double
name|pos
parameter_list|,
name|double
modifier|*
name|r
parameter_list|,
name|double
modifier|*
name|g
parameter_list|,
name|double
modifier|*
name|b
parameter_list|,
name|double
modifier|*
name|a
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|grad_create_gradient_editor
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|grad_free_gradient_editor
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/***** Procedural database exports *****/
end_comment

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gradients_get_list_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gradients_get_active_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gradients_set_active_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gradients_sample_uniform_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ProcRecord
name|gradients_sample_custom_proc
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

end_unit

