begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for the GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-1999 Maurits Rijk  lpeek.mrijk@consunet.nl  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_IMAP_BROWSE_H
end_ifndef

begin_define
DECL|macro|_IMAP_BROWSE_H
define|#
directive|define
name|_IMAP_BROWSE_H
end_define

begin_include
include|#
directive|include
file|"gtk/gtk.h"
end_include

begin_typedef
DECL|typedef|BrowseFilter_t
typedef|typedef
specifier|const
name|gchar
modifier|*
function_decl|(
modifier|*
name|BrowseFilter_t
function_decl|)
parameter_list|(
specifier|const
name|gchar
modifier|*
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|struct|__anon2a2149f20108
typedef|typedef
struct|struct
block|{
DECL|member|name
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|filter
name|BrowseFilter_t
name|filter
decl_stmt|;
DECL|member|filter_data
name|gpointer
name|filter_data
decl_stmt|;
DECL|member|hbox
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
DECL|member|file
name|GtkWidget
modifier|*
name|file
decl_stmt|;
DECL|member|button
name|GtkWidget
modifier|*
name|button
decl_stmt|;
DECL|member|file_selection
name|GtkWidget
modifier|*
name|file_selection
decl_stmt|;
DECL|typedef|BrowseWidget_t
block|}
name|BrowseWidget_t
typedef|;
end_typedef

begin_function_decl
name|BrowseWidget_t
modifier|*
name|browse_widget_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|browse_widget_set_filename
parameter_list|(
name|BrowseWidget_t
modifier|*
name|browse
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|browse_widget_set_filter
parameter_list|(
name|BrowseWidget_t
modifier|*
name|browse
parameter_list|,
name|BrowseFilter_t
name|filter
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
comment|/* _IMAP_BROWSE_H */
end_comment

end_unit

