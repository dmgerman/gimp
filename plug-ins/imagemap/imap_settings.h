begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for the GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-1999 Maurits Rijk  lpeek.mrijk@consunet.nl  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_IMAP_SETTINGS_H
end_ifndef

begin_define
DECL|macro|_IMAP_SETTINGS_H
define|#
directive|define
name|_IMAP_SETTINGS_H
end_define

begin_include
include|#
directive|include
file|"imap_browse.h"
end_include

begin_include
include|#
directive|include
file|"imap_default_dialog.h"
end_include

begin_typedef
DECL|struct|__anon2bce75050108
typedef|typedef
struct|struct
block|{
DECL|member|dialog
name|DefaultDialog_t
modifier|*
name|dialog
decl_stmt|;
DECL|member|imagename
name|BrowseWidget_t
modifier|*
name|imagename
decl_stmt|;
DECL|member|filename
name|GtkWidget
modifier|*
name|filename
decl_stmt|;
DECL|member|title
name|GtkWidget
modifier|*
name|title
decl_stmt|;
DECL|member|author
name|GtkWidget
modifier|*
name|author
decl_stmt|;
DECL|member|default_url
name|GtkWidget
modifier|*
name|default_url
decl_stmt|;
DECL|member|description
name|GtkWidget
modifier|*
name|description
decl_stmt|;
DECL|member|ncsa
name|GtkWidget
modifier|*
name|ncsa
decl_stmt|;
DECL|member|cern
name|GtkWidget
modifier|*
name|cern
decl_stmt|;
DECL|member|csim
name|GtkWidget
modifier|*
name|csim
decl_stmt|;
DECL|typedef|SettingsDialog_t
block|}
name|SettingsDialog_t
typedef|;
end_typedef

begin_function_decl
name|void
name|do_settings_dialog
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
comment|/* _IMAP_SETTINGS_H */
end_comment

end_unit

