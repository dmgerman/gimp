begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__INTERFACE_H__
end_ifndef

begin_define
DECL|macro|__INTERFACE_H__
define|#
directive|define
name|__INTERFACE_H__
end_define

begin_include
include|#
directive|include
file|"toolsF.h"
end_include

begin_include
include|#
directive|include
file|"gdisplayF.h"
end_include

begin_comment
comment|/* typedefs */
end_comment

begin_typedef
DECL|typedef|QueryFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|QueryFunc
function_decl|)
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|gpointer
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_typedef

begin_comment
comment|/* externed variables  */
end_comment

begin_decl_stmt
specifier|extern
name|GtkWidget
modifier|*
name|tool_widgets
index|[]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GtkWidget
modifier|*
name|popup_shell
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GtkTooltips
modifier|*
name|tool_tips
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* function declarations */
end_comment

begin_function_decl
name|GtkWidget
modifier|*
name|create_pixmap_widget
parameter_list|(
name|GdkWindow
modifier|*
parameter_list|,
name|char
modifier|*
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GdkPixmap
modifier|*
name|create_tool_pixmap
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|ToolType
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|create_toolbox
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|toolbox_free
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|toolbox_raise_callback
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|create_display_shell
parameter_list|(
name|GDisplay
modifier|*
parameter_list|,
name|int
parameter_list|,
name|int
parameter_list|,
name|char
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|position_dialog
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|gpointer
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|center_dialog
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|gpointer
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|query_string_box
parameter_list|(
name|char
modifier|*
parameter_list|,
name|char
modifier|*
parameter_list|,
name|char
modifier|*
parameter_list|,
name|QueryFunc
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|message_box
parameter_list|(
name|char
modifier|*
parameter_list|,
name|GtkCallback
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tools_push_label
parameter_list|(
name|char
modifier|*
name|label
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tools_pop_label
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|progress_start
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|progress_update
parameter_list|(
name|float
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|progress_step
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|progress_end
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* INTERFACE_H */
end_comment

end_unit

