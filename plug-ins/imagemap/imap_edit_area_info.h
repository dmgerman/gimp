begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for the GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-1999 Maurits Rijk  lpeek.mrijk@consunet.nl  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_IMAP_EDIT_AREA_INFO_H
end_ifndef

begin_define
DECL|macro|_IMAP_EDIT_AREA_INFO_H
define|#
directive|define
name|_IMAP_EDIT_AREA_INFO_H
end_define

begin_typedef
DECL|typedef|AreaInfoDialog_t
typedef|typedef
name|struct
name|AreaInfoDialog_t
name|AreaInfoDialog_t
typedef|;
end_typedef

begin_include
include|#
directive|include
file|"gtk/gtk.h"
end_include

begin_include
include|#
directive|include
file|"imap_default_dialog.h"
end_include

begin_include
include|#
directive|include
file|"imap_object.h"
end_include

begin_struct
DECL|struct|AreaInfoDialog_t
struct|struct
name|AreaInfoDialog_t
block|{
DECL|member|dialog
name|DefaultDialog_t
modifier|*
name|dialog
decl_stmt|;
DECL|member|obj
name|Object_t
modifier|*
name|obj
decl_stmt|;
DECL|member|add
name|gboolean
name|add
decl_stmt|;
DECL|member|notebook
name|GtkWidget
modifier|*
name|notebook
decl_stmt|;
DECL|member|web_site
name|GtkWidget
modifier|*
name|web_site
decl_stmt|;
DECL|member|ftp_site
name|GtkWidget
modifier|*
name|ftp_site
decl_stmt|;
DECL|member|gopher
name|GtkWidget
modifier|*
name|gopher
decl_stmt|;
DECL|member|other
name|GtkWidget
modifier|*
name|other
decl_stmt|;
DECL|member|file
name|GtkWidget
modifier|*
name|file
decl_stmt|;
DECL|member|wais
name|GtkWidget
modifier|*
name|wais
decl_stmt|;
DECL|member|telnet
name|GtkWidget
modifier|*
name|telnet
decl_stmt|;
DECL|member|email
name|GtkWidget
modifier|*
name|email
decl_stmt|;
DECL|member|url
name|GtkWidget
modifier|*
name|url
decl_stmt|;
DECL|member|relative_link
name|GtkWidget
modifier|*
name|relative_link
decl_stmt|;
DECL|member|target
name|GtkWidget
modifier|*
name|target
decl_stmt|;
DECL|member|comment
name|GtkWidget
modifier|*
name|comment
decl_stmt|;
DECL|member|mouse_over
name|GtkWidget
modifier|*
name|mouse_over
decl_stmt|;
DECL|member|mouse_out
name|GtkWidget
modifier|*
name|mouse_out
decl_stmt|;
DECL|member|focus
name|GtkWidget
modifier|*
name|focus
decl_stmt|;
DECL|member|blur
name|GtkWidget
modifier|*
name|blur
decl_stmt|;
DECL|member|browse
name|GtkWidget
modifier|*
name|browse
decl_stmt|;
DECL|member|infotab
name|gpointer
name|infotab
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|AreaInfoDialog_t
modifier|*
name|create_edit_area_info_dialog
parameter_list|(
name|Object_t
modifier|*
name|obj
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|edit_area_info_dialog_show
parameter_list|(
name|AreaInfoDialog_t
modifier|*
name|dialog
parameter_list|,
name|Object_t
modifier|*
name|obj
parameter_list|,
name|gboolean
name|add
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _IMAP_EDIT_AREA_INFO_H */
end_comment

end_unit

