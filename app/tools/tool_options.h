begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__TOOL_OPTIONS_H__
end_ifndef

begin_define
DECL|macro|__TOOL_OPTIONS_H__
define|#
directive|define
name|__TOOL_OPTIONS_H__
end_define

begin_comment
comment|/*  tool options function declarations  */
end_comment

begin_typedef
DECL|typedef|ToolOptionsResetFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|ToolOptionsResetFunc
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_typedef

begin_comment
comment|/*  the tool options structures  */
end_comment

begin_typedef
DECL|typedef|ToolOptions
typedef|typedef
name|struct
name|_ToolOptions
name|ToolOptions
typedef|;
end_typedef

begin_struct
DECL|struct|_ToolOptions
struct|struct
name|_ToolOptions
block|{
DECL|member|main_vbox
name|GtkWidget
modifier|*
name|main_vbox
decl_stmt|;
DECL|member|title
name|gchar
modifier|*
name|title
decl_stmt|;
DECL|member|reset_func
name|ToolOptionsResetFunc
name|reset_func
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  create a dummy tool options structure  *  (to be used by tools without options)  */
end_comment

begin_function_decl
name|ToolOptions
modifier|*
name|tool_options_new
parameter_list|(
name|gchar
modifier|*
name|title
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  initialize an already allocated ToolOptions structure  *  (to be used by derived tool options only)  */
end_comment

begin_function_decl
name|void
name|tool_options_init
parameter_list|(
name|ToolOptions
modifier|*
name|options
parameter_list|,
name|gchar
modifier|*
name|title
parameter_list|,
name|ToolOptionsResetFunc
name|reset_func
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __TOOL_OPTIONS_H__  */
end_comment

end_unit

