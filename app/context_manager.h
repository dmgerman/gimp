begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__CONTEXT_MANAGER_H__
end_ifndef

begin_define
DECL|macro|__CONTEXT_MANAGER_H__
define|#
directive|define
name|__CONTEXT_MANAGER_H__
end_define

begin_comment
comment|/*  *  the list of all images  */
end_comment

begin_decl_stmt
specifier|extern
name|GimpContainer
modifier|*
name|image_context
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  *  the global data factories which contain the global data lists  */
end_comment

begin_decl_stmt
specifier|extern
name|GimpDataFactory
modifier|*
name|global_brush_factory
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GimpDataFactory
modifier|*
name|global_pattern_factory
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GimpDataFactory
modifier|*
name|global_gradient_factory
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GimpDataFactory
modifier|*
name|global_palette_factory
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  *  the global tool context  */
end_comment

begin_decl_stmt
specifier|extern
name|GimpContext
modifier|*
name|global_tool_context
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|context_manager_init
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|context_manager_free
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|context_manager_set_global_paint_options
parameter_list|(
name|gboolean
name|global
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __CONTEXT_MANAGER_H__ */
end_comment

end_unit

