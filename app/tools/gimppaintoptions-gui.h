begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PAINT_OPTIONS_H__
end_ifndef

begin_define
DECL|macro|__PAINT_OPTIONS_H__
define|#
directive|define
name|__PAINT_OPTIONS_H__
end_define

begin_include
include|#
directive|include
file|"buildmenu.h"
end_include

begin_include
include|#
directive|include
file|"tools.h"
end_include

begin_include
include|#
directive|include
file|"tool_options.h"
end_include

begin_comment
comment|/*  the paint options structures  */
end_comment

begin_typedef
DECL|typedef|PaintOptions
typedef|typedef
name|struct
name|_PaintOptions
name|PaintOptions
typedef|;
end_typedef

begin_struct
DECL|struct|_PaintOptions
struct|struct
name|_PaintOptions
block|{
DECL|member|tool_options
name|ToolOptions
name|tool_options
decl_stmt|;
comment|/*  vbox for the common paint options  */
DECL|member|paint_vbox
name|GtkWidget
modifier|*
name|paint_vbox
decl_stmt|;
comment|/*  a widget to be shown if we are in global mode  */
DECL|member|global
name|GtkWidget
modifier|*
name|global
decl_stmt|;
comment|/*  options used by all paint tools  */
DECL|member|opacity_w
name|GtkObject
modifier|*
name|opacity_w
decl_stmt|;
DECL|member|paint_mode_w
name|GtkWidget
modifier|*
name|paint_mode_w
decl_stmt|;
comment|/*  the incremental toggle  */
DECL|member|incremental
name|gboolean
name|incremental
decl_stmt|;
DECL|member|incremental_d
name|gboolean
name|incremental_d
decl_stmt|;
DECL|member|incremental_w
name|GtkWidget
modifier|*
name|incremental_w
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  paint tool options functions  */
end_comment

begin_function_decl
name|PaintOptions
modifier|*
name|paint_options_new
parameter_list|(
name|ToolType
name|tool_type
parameter_list|,
name|ToolOptionsResetFunc
name|reset_func
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|paint_options_reset
parameter_list|(
name|PaintOptions
modifier|*
name|options
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  to be used by "derived" paint options only  */
end_comment

begin_function_decl
name|void
name|paint_options_init
parameter_list|(
name|PaintOptions
modifier|*
name|options
parameter_list|,
name|ToolType
name|tool_type
parameter_list|,
name|ToolOptionsResetFunc
name|reset_func
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  functions for the global paint options  */
end_comment

begin_comment
comment|/*  switch between global and per-tool paint options  */
end_comment

begin_function_decl
name|void
name|paint_options_set_global
parameter_list|(
name|gboolean
name|global
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  a utility function which returns a paint mode menu  */
end_comment

begin_function_decl
name|GtkWidget
modifier|*
name|paint_mode_menu_new
parameter_list|(
name|MenuItemCallback
name|callback
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __PAINT_OPTIONS_H__  */
end_comment

end_unit

