begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for the GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-1999 Maurits Rijk  lpeek.mrijk@consunet.nl  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_IMAP_TOOLS_H
end_ifndef

begin_define
DECL|macro|_IMAP_TOOLS_H
define|#
directive|define
name|_IMAP_TOOLS_H
end_define

begin_include
include|#
directive|include
file|"imap_command.h"
end_include

begin_typedef
DECL|struct|__anon2b310dc00108
typedef|typedef
struct|struct
block|{
DECL|member|container
name|GtkWidget
modifier|*
name|container
decl_stmt|;
DECL|member|arrow
name|GtkWidget
modifier|*
name|arrow
decl_stmt|;
DECL|member|rectangle
name|GtkWidget
modifier|*
name|rectangle
decl_stmt|;
DECL|member|circle
name|GtkWidget
modifier|*
name|circle
decl_stmt|;
DECL|member|polygon
name|GtkWidget
modifier|*
name|polygon
decl_stmt|;
DECL|member|edit
name|GtkWidget
modifier|*
name|edit
decl_stmt|;
DECL|member|delete
name|GtkWidget
modifier|*
name|delete
decl_stmt|;
DECL|member|cmd_delete
name|CommandFactory_t
name|cmd_delete
decl_stmt|;
DECL|member|cmd_edit
name|CommandFactory_t
name|cmd_edit
decl_stmt|;
DECL|typedef|Tools_t
block|}
name|Tools_t
typedef|;
end_typedef

begin_function_decl
name|Tools_t
modifier|*
name|make_tools
parameter_list|(
name|GtkWidget
modifier|*
name|window
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tools_select_arrow
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tools_select_rectangle
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tools_select_circle
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tools_select_polygon
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tools_set_sensitive
parameter_list|(
name|gboolean
name|sensitive
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|arrow_on_button_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|tools_set_delete_command (tools,command)
define|#
directive|define
name|tools_set_delete_command
parameter_list|(
name|tools
parameter_list|,
name|command
parameter_list|)
define|\
value|((tools)->cmd_delete = (command))
end_define

begin_define
DECL|macro|tools_set_edit_command (tools,command)
define|#
directive|define
name|tools_set_edit_command
parameter_list|(
name|tools
parameter_list|,
name|command
parameter_list|)
define|\
value|((tools)->cmd_edit = (command))
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _IMAP_TOOLS_H */
end_comment

end_unit

