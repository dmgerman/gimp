begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for the GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-1999 Maurits Rijk  lpeek.mrijk@consunet.nl  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_IMAP_PREVIEW_H
end_ifndef

begin_define
DECL|macro|_IMAP_PREVIEW_H
define|#
directive|define
name|_IMAP_PREVIEW_H
end_define

begin_include
include|#
directive|include
file|"libgimp/gimp.h"
end_include

begin_include
include|#
directive|include
file|"gtk/gtk.h"
end_include

begin_typedef
DECL|struct|__anon296494580108
typedef|typedef
struct|struct
block|{
DECL|member|drawable
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
DECL|member|window
name|GtkWidget
modifier|*
name|window
decl_stmt|;
DECL|member|frame
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
DECL|member|preview
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
DECL|member|hruler
name|GtkWidget
modifier|*
name|hruler
decl_stmt|;
DECL|member|vruler
name|GtkWidget
modifier|*
name|vruler
decl_stmt|;
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|height
name|gint
name|height
decl_stmt|;
DECL|member|exp_id
name|gint
name|exp_id
decl_stmt|;
DECL|member|src_rgn
name|GimpPixelRgn
name|src_rgn
decl_stmt|;
DECL|member|cursor
name|GdkCursorType
name|cursor
decl_stmt|;
DECL|typedef|Preview_t
block|}
name|Preview_t
typedef|;
end_typedef

begin_function_decl
name|Preview_t
modifier|*
name|make_preview
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|preview_redraw
parameter_list|(
name|Preview_t
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|add_preview_motion_event
parameter_list|(
name|Preview_t
modifier|*
name|preview
parameter_list|,
name|GtkSignalFunc
name|func
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|add_enter_notify_event
parameter_list|(
name|Preview_t
modifier|*
name|preview
parameter_list|,
name|GtkSignalFunc
name|func
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|add_leave_notify_event
parameter_list|(
name|Preview_t
modifier|*
name|preview
parameter_list|,
name|GtkSignalFunc
name|func
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|add_preview_button_press_event
parameter_list|(
name|Preview_t
modifier|*
name|preview
parameter_list|,
name|GtkSignalFunc
name|func
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|preview_get_width
parameter_list|(
name|GtkWidget
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|preview_get_height
parameter_list|(
name|GtkWidget
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|preview_zoom
parameter_list|(
name|Preview_t
modifier|*
name|preview
parameter_list|,
name|gint
name|zoom_factor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GdkCursorType
name|preview_set_cursor
parameter_list|(
name|Preview_t
modifier|*
name|preview
parameter_list|,
name|GdkCursorType
name|cursor_type
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _IMAP_PREVIEW_H */
end_comment

end_unit

