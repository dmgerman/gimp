begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for the GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-1999 Maurits Rijk  lpeek.mrijk@consunet.nl  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_IMAP_OBJECT_POPUP_H
end_ifndef

begin_define
DECL|macro|_IMAP_OBJECT_POPUP_H
define|#
directive|define
name|_IMAP_OBJECT_POPUP_H
end_define

begin_include
include|#
directive|include
file|"imap_object.h"
end_include

begin_typedef
DECL|struct|__anon2b2f856a0108
typedef|typedef
struct|struct
block|{
DECL|member|menu
name|GtkWidget
modifier|*
name|menu
decl_stmt|;
DECL|member|up
name|GtkWidget
modifier|*
name|up
decl_stmt|;
DECL|member|down
name|GtkWidget
modifier|*
name|down
decl_stmt|;
DECL|member|obj
name|Object_t
modifier|*
name|obj
decl_stmt|;
DECL|typedef|ObjectPopup_t
block|}
name|ObjectPopup_t
typedef|;
end_typedef

begin_function_decl
name|ObjectPopup_t
modifier|*
name|make_object_popup
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|object_popup_prepend_menu
parameter_list|(
name|ObjectPopup_t
modifier|*
name|popup
parameter_list|,
name|gchar
modifier|*
name|label
parameter_list|,
name|MenuCallback
name|activate
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_handle_popup
parameter_list|(
name|ObjectPopup_t
modifier|*
name|popup
parameter_list|,
name|Object_t
modifier|*
name|obj
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|object_do_popup
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Object_t
modifier|*
name|get_popup_object
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
comment|/* _IMAP_OBJECT_POPUP_H */
end_comment

end_unit

