begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for the GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-1999 Maurits Rijk  lpeek.mrijk@consunet.nl  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_IMAP_GRID_H
end_ifndef

begin_define
DECL|macro|_IMAP_GRID_H
define|#
directive|define
name|_IMAP_GRID_H
end_define

begin_include
include|#
directive|include
file|"imap_default_dialog.h"
end_include

begin_typedef
DECL|struct|__anon2c03e3a90108
typedef|typedef
struct|struct
block|{
DECL|member|dialog
name|DefaultDialog_t
modifier|*
name|dialog
decl_stmt|;
DECL|member|type_frame
name|GtkWidget
modifier|*
name|type_frame
decl_stmt|;
DECL|member|granularity_frame
name|GtkWidget
modifier|*
name|granularity_frame
decl_stmt|;
DECL|member|offset_frame
name|GtkWidget
modifier|*
name|offset_frame
decl_stmt|;
DECL|member|snap
name|GtkWidget
modifier|*
name|snap
decl_stmt|;
DECL|member|width
name|GtkWidget
modifier|*
name|width
decl_stmt|;
DECL|member|height
name|GtkWidget
modifier|*
name|height
decl_stmt|;
DECL|member|left
name|GtkWidget
modifier|*
name|left
decl_stmt|;
DECL|member|top
name|GtkWidget
modifier|*
name|top
decl_stmt|;
DECL|member|hidden
name|GtkWidget
modifier|*
name|hidden
decl_stmt|;
DECL|member|lines
name|GtkWidget
modifier|*
name|lines
decl_stmt|;
DECL|member|crosses
name|GtkWidget
modifier|*
name|crosses
decl_stmt|;
DECL|typedef|GridDialog_t
block|}
name|GridDialog_t
typedef|;
end_typedef

begin_function_decl
name|void
name|do_grid_settings_dialog
parameter_list|()
function_decl|;
end_function_decl

begin_function_decl
name|void
name|draw_grid
parameter_list|(
name|GtkWidget
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|toggle_grid
parameter_list|()
function_decl|;
end_function_decl

begin_function_decl
name|void
name|round_to_grid
parameter_list|(
name|gint
modifier|*
name|x
parameter_list|,
name|gint
modifier|*
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _IMAP_GRID_H */
end_comment

end_unit

