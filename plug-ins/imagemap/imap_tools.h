begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for the GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-2004 Maurits Rijk  m.rijk@chello.nl  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
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
DECL|struct|__anon2aabbda00108
typedef|typedef
struct|struct
block|{
DECL|member|container
name|GtkWidget
modifier|*
name|container
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
name|gboolean
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _IMAP_TOOLS_H */
end_comment

end_unit

