begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__TOOL_OPTIONS_UI_H__
end_ifndef

begin_define
DECL|macro|__TOOL_OPTIONS_UI_H__
define|#
directive|define
name|__TOOL_OPTIONS_UI_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_comment
comment|/*  a toggle button callback which sets the sensitive state of an attached  *  list of widgets  */
end_comment

begin_function_decl
name|void
name|tool_options_toggle_update
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  a unit menu callback which sets the digits of an attached  *  list of spinbuttons  */
end_comment

begin_function_decl
name|void
name|tool_options_unitmenu_update
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  integer and float adjustment callbacks  */
end_comment

begin_function_decl
name|void
name|tool_options_int_adjustment_update
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tool_options_double_adjustment_update
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __TOOL_OPTIONS_UI_H__ */
end_comment

end_unit

