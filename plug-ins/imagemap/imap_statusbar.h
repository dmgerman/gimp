begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for the GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-1999 Maurits Rijk  lpeek.mrijk@consunet.nl  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_IMAP_STATUSBAR_H
end_ifndef

begin_define
DECL|macro|_IMAP_STATUSBAR_H
define|#
directive|define
name|_IMAP_STATUSBAR_H
end_define

begin_include
include|#
directive|include
file|"gtk/gtk.h"
end_include

begin_typedef
DECL|struct|__anon29b5a25d0108
typedef|typedef
struct|struct
block|{
DECL|member|status
name|GtkWidget
modifier|*
name|status
decl_stmt|;
DECL|member|xy
name|GtkWidget
modifier|*
name|xy
decl_stmt|;
DECL|member|dimension
name|GtkWidget
modifier|*
name|dimension
decl_stmt|;
DECL|member|zoom
name|GtkWidget
modifier|*
name|zoom
decl_stmt|;
DECL|member|status_id
name|gint
name|status_id
decl_stmt|;
DECL|member|message_id
name|gint
name|message_id
decl_stmt|;
DECL|member|zoom_id
name|gint
name|zoom_id
decl_stmt|;
DECL|typedef|StatusBar_t
block|}
name|StatusBar_t
typedef|;
end_typedef

begin_function_decl
name|StatusBar_t
modifier|*
name|make_statusbar
parameter_list|(
name|GtkWidget
modifier|*
name|main_vbox
parameter_list|,
name|GtkWidget
modifier|*
name|window
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|statusbar_set_status
parameter_list|(
name|StatusBar_t
modifier|*
name|statusbar
parameter_list|,
specifier|const
name|gchar
modifier|*
name|format
parameter_list|,
modifier|...
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|statusbar_clear_status
parameter_list|(
name|StatusBar_t
modifier|*
name|statusbar
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|statusbar_set_xy
parameter_list|(
name|StatusBar_t
modifier|*
name|statusbar
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|statusbar_clear_xy
parameter_list|(
name|StatusBar_t
modifier|*
name|statusbar
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|statusbar_set_dimension
parameter_list|(
name|StatusBar_t
modifier|*
name|statusbar
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|statusbar_clear_dimension
parameter_list|(
name|StatusBar_t
modifier|*
name|statusbar
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|statusbar_set_zoom
parameter_list|(
name|StatusBar_t
modifier|*
name|statusbar
parameter_list|,
name|gint
name|factor
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _IMAP_STATUSBAR_H */
end_comment

end_unit

